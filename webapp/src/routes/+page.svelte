<script>
	import './styles.scss';
	import { Line } from 'svelte-chartjs';
	import {
		lightData,
		moistureData,
		humidityData,
		temperatureData,
		co2Data,
		vocsData
	} from './firebase.ts';

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

	ChartJS.register(Title, Tooltip, Legend, LineElement, LinearScale, PointElement, CategoryScale);

	const options = {
		responsive: true,
		title: {
			display: true,
			text: 'Plant Data'
		},
		datasets: {}
	};
</script>

<svelte:head>
	<title>🌱 Plant 🪴</title>
	<meta name="description" content="Plant Dashboard" />
</svelte:head>

<h1>🌱 Plant Dashboard 🪴</h1>

<div class="grid">
	<div class="grid-item">
		<h2>{lightData.title}</h2>
		<Line data={lightData} {options} />
	</div>
	<div class="grid-item">
		<h2>{moistureData.title}</h2>
		<Line data={moistureData} {options} />
	</div>
	<div class="grid-item">
		<h2>{humidityData.title}</h2>
		<Line data={humidityData} {options} />
	</div>
	<div class="grid-item">
		<h2>{temperatureData.title}</h2>
		<Line data={temperatureData} {options} />
	</div>
	<div class="grid-item">
		<h2>{vocsData.title}</h2>
		<Line data={vocsData} {options} />
	</div>
	<div class="grid-item">
		<h2>{co2Data.title}</h2>
		<Line data={co2Data} {options} />
	</div>
</div>
