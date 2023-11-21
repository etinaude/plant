<script lang="ts">
	import './styles.scss';
	import { db, generateChartData, filterData } from './firebase.ts';
	import type { ChartData, DataFilter, PlantData } from './types.ts';
	import Graph from './graph.svelte';
	import { ref, onValue, DataSnapshot, get } from 'firebase/database';
	import { onMount } from 'svelte';

	let chartList: ChartData[] = [];
	let rawData: PlantData[] = [];
	let filteredData: PlantData[] = [];
	let lastUpdated = new Date();

	let filter: DataFilter = {
		startDate: '2020-01-01',
		endDate: '2023-12-12',
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
		filteredData = filterData(rawData, filter);
		chartList = generateChartData(filteredData);
	}

	onMount(async () => {
		get(ref(db, 'esp32')).then((snapshot: DataSnapshot) => {
			processFirebaseData(snapshot);
		});

		const today = new Date();
		today.setDate(today.getDate() - 1);
		filter.startDate = today.toISOString().slice(0, 16);

		const tomorrow = new Date();
		tomorrow.setDate(tomorrow.getDate() + 1);
		filter.endDate = tomorrow.toISOString().slice(0, 16);

		getFirebaseData();
	});




</script>

<svelte:head>
	<title>🌱 Plant 🪴</title>
	<meta name="description" content="Plant Dashboard" />
</svelte:head>

<h1>🌱 Plant Dashboard 🪴</h1>

<div class="filter-row">
	<div class="filter">
		<div class="filter-title">Start Date</div>
		<input type="datetime-local" bind:value={filter.startDate} on:change={filterAndDisplay} />
	</div>

	<div class="filter">
		<div class="filter-title">End Date</div>
		<input type="datetime-local" bind:value={filter.endDate} on:change={filterAndDisplay} />
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
