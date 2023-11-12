<script lang="ts">
	import './styles.scss';
	import { Line } from 'svelte-chartjs';
	import { db, generateChartData } from './firebase.ts';
	import type { ChartData } from './firebase.ts';

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

	import { ref, onValue } from 'firebase/database';
	import { onMount } from 'svelte';

	let chartList: ChartData[] = [];
	const firebaseData: any[] = [];

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
		onValue(ref(db, 'plant'), (snapshot) => {
			firebaseData.length = 0;
			snapshot.forEach((item) => {
				firebaseData.push(item.val());
			});

			chartList = generateChartData(firebaseData);
		});
	}

	onMount(async () => {
		await getFirebaseData();
	});
</script>

<svelte:head>
	<title>🌱 Plant 🪴</title>
	<meta name="description" content="Plant Dashboard" />
</svelte:head>

<h1>🌱 Plant Dashboard 🪴</h1>

<div class="grid">
	{#each chartList as chart}
		<div class="grid-item">
			<h2>{chart.title}</h2>
			<Line data={chart} {options} />
		</div>
	{/each}
</div>
