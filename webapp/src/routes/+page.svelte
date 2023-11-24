<script lang="ts">
	import './styles.scss';
	import { db, generateChartData, filterData, initAnalytics } from './firebase.ts';
	import type { ChartData, DataFilter, PlantData } from './types.ts';
	import Graph from './graph.svelte';
	import { ref, onValue, DataSnapshot, get } from 'firebase/database';
	import { onMount } from 'svelte';

	let chartList: ChartData[] = [];
	let rawData: PlantData[] = [];
	let filteredData: PlantData[] = [];
	let lastUpdated = new Date();

	let filter: DataFilter = {
		endDate: '2020-01-01',
		timeSpan: 86400, // 1 day default scale
		dataPointCount: 50
	};

	async function getFirebaseData() {
		onValue(ref(db, 'esp32'), (snapshot) => {
			if (new Date().getTime() - lastUpdated.getTime() < 5000) return;
			lastUpdated = new Date();

			processFirebaseData(snapshot);
		});
	}

	function processFirebaseData(snapshot: DataSnapshot) {
		rawData = [];
		snapshot.forEach((item) => {
			const temp = item.val() as PlantData;
			temp.timeStamp = temp.timeStamp * 1000;
			rawData.push(temp);
		});

		filterAndDisplay();
	}

	function filterAndDisplay() {
		chartList = [];

		// force a re-render
		setTimeout(() => {
			filteredData = filterData(rawData, filter);
			chartList = generateChartData(filteredData);
		}, 10);
	}

	onMount(async () => {
		get(ref(db, 'esp32')).then((snapshot: DataSnapshot) => {
			processFirebaseData(snapshot);
		});

		// set time for 5 min in the future
		const today = new Date();
		today.setTime(today.getTime() + 1000 * 60 * 5);
		filter.endDate = today.toISOString().slice(0, 16);

		getFirebaseData();
		initAnalytics();
	});
</script>

<svelte:head>
	<title>🌱 Plant 🪴</title>
	<meta name="description" content="Plant Dashboard" />
</svelte:head>

<h1>🌱 Plant Dashboard 🪴</h1>

<div class="filter-row">
	<div class="filter">
		<div class="filter-title">End Date</div>
		<input type="datetime-local" bind:value={filter.endDate} on:change={filterAndDisplay} />
	</div>

	<div class="filter">
		<div class="filter-title">Time Scale</div>
		<select bind:value={filter.timeSpan} on:change={filterAndDisplay}>
			<option value={1800}>Half hour</option>
			<option value={3600}>1 hour</option>
			<option value={36000}>10 hours</option>
			<option value={86400}>1 day</option>
			<option value={604800}>1 week</option>
			<option value={2592000}>1 month</option>
			<option value={7776000}>3 months</option>
			<option value={15552000}>6 months</option>
			<option value={31536000}>1 year</option>
		</select>
	</div>

	<div class="filter">
		<div class="filter-title">Data points</div>
		<input type="number" bind:value={filter.dataPointCount} on:change={filterAndDisplay} />
	</div>

	<div class="filter">
		<div class="filter-title">&nbsp;</div>
		<button on:click={filterAndDisplay}> GO >> </button>
	</div>
</div>

<div class="chart-list">
	{#each chartList as data}
		<Graph dataIn={data} />
	{/each}
</div>

<footer>
	<h2>
		Check out some of my other projects:

		<a href="https://etinaude.dev">https://etinaude.dev</a>
	</h2>
</footer>
