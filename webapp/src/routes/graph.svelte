<script lang="ts">
	import Chart from 'chart.js/auto';
	import type { ChartData } from './types';
	import { onMount } from 'svelte';
	import 'chartjs-adapter-date-fns';

	export let dataIn!: ChartData;
	let ctx: HTMLCanvasElement;
	let chart: Chart;

	const dataSets = dataIn.datasets.map((dataSet) => {
		return {
			label: dataSet.label,
			data: dataSet.data,
			backgroundColor: dataSet.color,
			borderColor: dataSet.color,
			pointBorderWidth: 6,
			pointHitRadius: 6,
			pointRadius: 0,
			tension: 0.4
		};
	});

	onMount(() => {
		updateChart();
	});

	export function updateChart() {
		chart = new Chart(ctx, {
			type: 'line',
			data: {
				datasets: dataSets
			},
			options: {
				responsive: true,
				plugins: {
					legend: {
						display: false
					}
				},
				interaction: {
					mode: 'index',
					intersect: false
				},
				scales: {
					x: {
						type: 'time',

						time: {
							unit: 'minute',
							displayFormats: {
								minute: 'dd MMM HH:mm'
							}
						},
						ticks: {
							maxTicksLimit: 10
						},
						grid: {
							color: '#333'
						}
					},
					y: {
						display: true,
						title: {
							display: true,
							text: dataIn.unit
						},
						grid: {
							color: '#333'
						},
						suggestedMin: dataIn.range.min,
						suggestedMax: dataIn.range.max
					}
				}
			}
		});
	}
</script>

<div class="grid-item">
	<h2>{dataIn.title}</h2>

	<canvas bind:this={ctx} />
</div>

<style lang="scss">
	.grid-item {
		width: min(500px, 90vw);
		height: 350px;

		h2 {
			text-align: center;
			width: 100%;
			margin-top: 20px;
			margin-bottom: 10px;
			user-select: none;
		}
	}
</style>
