export type PlantData = {
	co2: number;
	light: number;
	moisture1: number;
	moisture2: number;
	moisture3: number;
	humidity: number;
	temperature: number;
	vocs: number;
	timeStamp: number;
};

export class DataSet {
	field: string;
	borderColor: string;
	pointBorderColor: string;
	data: number[];
	labels: string[];

	lineTension: number;
	pointBorderWidth: number;
	pointRadius: number;
	pointHitRadius: number;

	constructor(plantData: PlantData[], field: keyof PlantData, colour: string) {
		this.field = field;
		this.borderColor = colour;
		this.pointBorderColor = colour;

		this.lineTension = 0.5;
		this.pointBorderWidth = 6;
		this.pointRadius = 0;
		this.pointHitRadius = 5;

		this.data = [];
		this.labels = [];

		plantData.forEach((item) => {
			this.data.push(item[field]);
			let label = new Date(item.timeStamp).toUTCString();
			label = label.substring(5, 11) + label.substring(16, 22);
			this.labels.push(label);
		});
	}
}

export class ChartData {
	title: string;
	labels: string[];
	datasets: DataSet[];

	constructor(data: DataSet, title: string) {
		this.title = title;
		this.datasets = [data];

		this.labels = data.labels;
	}

	appendDataSet(data: DataSet) {
		this.datasets.push(data);
	}
}

export type DataFilter = {
	startDate: string;
	endDate: string;
	dataPointCount: number;
};
