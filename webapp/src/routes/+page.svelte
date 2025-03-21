<script lang="ts">
	import './styles.scss';
	import type { ChartData, DataFilter } from './types.ts';
	import Graph from './graph.svelte';
	import { onMount } from 'svelte';
	import { filterData, updateData, generateChartData } from './data.ts';
	import { db, initAnalytics } from './firebase.ts';
	import { onValue, ref } from 'firebase/database';

	let lastUpdated = new Date(0);
	let filter: DataFilter = {
		timeSpan: 86400, // 1 day default scale
		dataPointCount: 200
	};

	let chartList: ChartData[] = [];

	onMount(async () => {
		initAnalytics();
		onValue(ref(db, 'data'), (snapshot) => {
			if (new Date().getTime() - lastUpdated.getTime() < 5000) return;
			lastUpdated = new Date();

			updateData(snapshot);

			updateDisplay();
		});
	});

	function updateDisplay() {
		chartList = [];
		setTimeout(() => {
			let filteredData = filterData(filter);
			chartList = generateChartData(filteredData);
		}, 10);
	}
</script>

<svelte:head>
	<title>🌱 Plant 🪴</title>
	<meta name="description" content="Plant Dashboard" />
</svelte:head>

<div class="container">
	<div class="left-column">
		<h1>🌱 Plant Dashboard 🪴</h1>

		<div class="filter-row">
			<div class="filter">
				<div class="filter-title">Time Scale</div>
				<select bind:value={filter.timeSpan} on:change={updateDisplay}>
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
				<input type="number" bind:value={filter.dataPointCount} on:change={updateDisplay} />
			</div>
		</div>
	</div>

	<div class="chart-list">
		{#each chartList as data}
			<Graph dataIn={data} />
		{/each}
	</div>
</div>

<footer>
	<h2>
		Check out some of my other projects:

		<a href="https://etinaude.dev">https://etinaude.dev</a>
	</h2>
</footer>
