import type { Point } from 'chart.js';

export type PlantData = {
	co2: number;
	light: number;
	moisture1: number;
	moisture2: number;
	moisture3: number;
	humid: number;
	temp: number;
	tvoc: number;
	timeStamp: number;
};

export class DataSet {
	color: string;
	data: Point[];
	label: string;

	constructor(plantData: PlantData[], field: keyof PlantData, colour: string) {
		this.color = colour;
		this.data = [];
		this.label = field;

		plantData.forEach((item) => {
			const dataPoint: Point = { x: item.timeStamp, y: item[field] };
			this.data.push(dataPoint);
		});
	}
}

export class ChartData {
	title: string;
	datasets: DataSet[];
	unit: string;
	range: { min: number; max: number };

	constructor(data: DataSet, title: string, unit: string, range?: { min: number; max: number }) {
		this.title = title;
		this.datasets = [data];
		this.unit = unit;
		this.range = range || { min: -10, max: 110 };
	}

	appendDataSet(data: DataSet) {
		this.datasets.push(data);
	}
}

export type DataFilter = {
	timeSpan: number;
	dataPointCount: number;
};
