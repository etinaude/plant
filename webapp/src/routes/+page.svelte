<script lang="ts">
	import './styles.scss';
	import { Line } from 'svelte-chartjs';
	import { db, generateChartData, filterData } from './firebase.ts';
	import type { ChartData, DataFilter, PlantData } from './types.ts';

	import {
		Chart as ChartJS,
		Title,
		Tooltip,
		Legend,
		LineElement,
		LinearScale,
		PointElement,
		CategoryScale
	} from 'chart.js';

	import { ref, onValue, DataSnapshot, child, get } from 'firebase/database';
	import { onMount } from 'svelte';

	let chartList: ChartData[] = [];
	let rawData: PlantData[] = [];
	let filteredData: PlantData[] = [];
	let filter: DataFilter = {
		startDate: '2020-01-01',
		endDate: '2023-12-12',
		dataPointCount: 10
	};

	let lastUpdated = new Date();

	ChartJS.register(Title, Tooltip, LineElement, LinearScale, PointElement, CategoryScale);

	const options = {
		responsive: true,
		title: {
			display: true,
			text: 'Plant Data'
		},
		datasets: {}
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

	function getInitalFirebaseData() {}

	function filterAndDisplay() {
		filteredData = filterData(rawData, filter);
		chartList = generateChartData(filteredData);
	}

	onMount(async () => {
		get(ref(db, 'esp32')).then((snapshot: DataSnapshot) => {
			processFirebaseData(snapshot);
		});
	});
</script>

<svelte:head>
	<title>🌱 Plant 🪴</title>
	<meta name="description" content="Plant Dashboard" />
</svelte:head>

<div class="filter-row">
	<div class="filter">
		<div class="filter-title">Start Date</div>
		<input type="date" bind:value={filter.startDate} />
	</div>

	<div class="filter">
		<div class="filter-title">End Date</div>
		<input type="date" bind:value={filter.endDate} />
	</div>

	<div class="filter">
		<div class="filter-title">Data points</div>
		<input type="number" bind:value={filter.dataPointCount} />
	</div>

	<div class="filter">
		<div class="filter-title">&nbsp;</div>
		<button on:click={filterAndDisplay}> GO >> </button>
	</div>
</div>

<h1>🌱 Plant Dashboard 🪴</h1>

<div class="grid">
	{#each chartList as chart}
		<div class="grid-item">
			<h2>{chart.title}</h2>
			<Line data={chart} {options} />
		</div>
	{/each}
</div>
