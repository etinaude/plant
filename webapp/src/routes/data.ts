import { DataSnapshot, update } from 'firebase/database';
import { ChartData, DataSet, type DataFilter, type PlantData } from './types.ts';

let rawData: PlantData[] = [];

export function updateData(snapshot: DataSnapshot) {
	// snapshot.forEach((item) => {
	// 	const temp = item.val() as PlantData;
	// 	// temp.timeStamp = temp.timeStamp * 1000;
	// 	rawData.push(temp);
	// });

	rawData = Object.values(snapshot.val());
}

export function filterData(filter: DataFilter): PlantData[] {
	let data: PlantData[] = [];
	const fiveMin = 5 * 60 * 1000;
	let endTimeStamp = new Date().getTime();
	let startTimeStamp = endTimeStamp - filter.timeSpan * 1000;
	let dataPointCount = filter.dataPointCount;

	endTimeStamp += fiveMin;
	startTimeStamp -= fiveMin;

	rawData.forEach((item) => {
		if (!item.timeStamp) return;
		if (item.timeStamp * 1000 < startTimeStamp) return;
		if (item.timeStamp * 1000 > endTimeStamp) return;

		const processed = processData({ ...item });
		data.push(processed);
	});

	// if we have too much data, we need to reduce it
	if (data.length > dataPointCount) {
		const dataPoints = Math.floor(data.length / dataPointCount);
		const newData: PlantData[] = [];

		for (let i = 0; i < data.length; i += dataPoints) {
			newData.push(data[i]);
		}

		data = newData;
	}

	data.sort((a, b) => {
		if (!a.timeStamp || !b.timeStamp) return 0;
		return a.timeStamp - b.timeStamp;
	});

	return data;
}

function processData(data: PlantData) {
	data.timeStamp = data.timeStamp * 1000;
	if (data.moisture1 < 0) data.moisture1 = NaN;
	if (data.moisture2 < 0) data.moisture2 = NaN;
	if (data.moisture3 < 0) data.moisture3 = NaN;

	return data;
}

export function generateChartData(data: PlantData[]) {
	const moisture1Dataset = new DataSet(data, 'moisture1', '#24aaed');
	const moisture2Dataset = new DataSet(data, 'moisture2', '#247bed');
	const moisture3Dataset = new DataSet(data, 'moisture3', '#2442ed');
	const tempDataset = new DataSet(data, 'temp', '#ed9624');
	const vocsDataset = new DataSet(data, 'tvoc', '#888');
	const co2Dataset = new DataSet(data, 'co2', '#bbb');
	const humidityDataset = new DataSet(data, 'humid', '#24edbe');
	// const lightDataset = new DataSet(data, 'light', '#ede324');

	let chartList = [];

	chartList.push(new ChartData(moisture1Dataset, 'Moisture 💧', '%', { min: 10, max: 25 }));
	chartList.push(new ChartData(humidityDataset, 'Humidity 💦', '%', { min: 0, max: 60 }));
	chartList.push(new ChartData(tempDataset, 'Temperature 🌡️', '°C', { min: 10, max: 40 }));
	chartList.push(new ChartData(vocsDataset, 'CO2 & VOCs ☁️', 'PPM', { min: -10, max: 1200 }));
	// chartList.push(new ChartData(lightDataset, 'Light 💡', 'on/off', { min: -1, max: 2 }));

	chartList[0].appendDataSet(moisture2Dataset);
	chartList[0].appendDataSet(moisture3Dataset);

	chartList[3].appendDataSet(co2Dataset);

	return chartList;
}
