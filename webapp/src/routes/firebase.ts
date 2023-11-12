import { initializeApp } from "firebase/app";
import { getDatabase, ref, set } from "firebase/database";
import * as keys from "./../keys.json"
import type { PlantData, DataFilter } from "./types";
import { DataSet, ChartData, } from "./types";

const firebaseConfig = {
    apiKey: keys.apiKey,
    authDomain: keys.authDomain,
    projectId: keys.projectId,
    storageBucket: keys.storageBucket,
    messagingSenderId: keys.messagingSenderId,
    appId: keys.appId,
    measurementId: keys.measurementId,
    databaseURL: keys.databaseURL
};

const app = initializeApp(firebaseConfig);
export const db = getDatabase(app);

export async function populateFakeData() {
    for (let i = 0; i < 10; i++) {
        const time = Math.round((Math.random() * 100000000000) + 1600000000000)

        set(ref(db, 'plant/' + time), {
            co2: Math.random() * 1000,
            light: Math.random() * 100,
            moisture1: Math.random() * 100,
            moisture2: Math.random() * 100,
            moisture3: Math.random() * 100,
            temperature: Math.random() * 60,
            humidity: Math.random() * 100,
            vocs: Math.random() * 20,
            timeStamp: time
        });
    }
}

export function generateChartData(data: PlantData[]) {
    const lightDataset = new DataSet(data, 'light', '#ede324');
    const moisture1Dataset = new DataSet(data, 'moisture1', '#24aaed');
    const moisture2Dataset = new DataSet(data, 'moisture2', '#2442ed');
    const moisture3Dataset = new DataSet(data, 'moisture3', '#247bed');
    const tempDataset = new DataSet(data, 'temperature', '#ed9624');
    const vocsDataset = new DataSet(data, 'vocs', '#444');
    const co2Dataset = new DataSet(data, 'co2', '#777');
    const humidityDataset = new DataSet(data, 'humidity', '#24edbe');

    let chartList = [];

    chartList.push(new ChartData(lightDataset, 'Light 💡'));
    chartList.push(new ChartData(moisture1Dataset, 'Moisture 💧'));
    chartList.push(new ChartData(humidityDataset, 'Humidity 💦'));
    chartList.push(new ChartData(tempDataset, 'Temperature 🌡️'));
    chartList.push(new ChartData(vocsDataset, 'VOCs 🌫️'));
    chartList.push(new ChartData(co2Dataset, 'CO2 ☁️'));

    chartList[1].appendDataSet(moisture2Dataset);
    chartList[1].appendDataSet(moisture3Dataset);

    return chartList;
}


export function filterData(rawData: PlantData[], filter: DataFilter): PlantData[] {

    console.log(filter);
    console.log(rawData);

    const data: PlantData[] = []
    const startDate = filter.startDate;
    const endDate = filter.endDate;
    const dataPointCount = filter.dataPointCount;

    // Filter data by date
    rawData.forEach((item) => {
        if (item.timeStamp < new Date(startDate).getTime()) return;
        if (item.timeStamp > new Date(endDate).getTime()) return;

        data.push(item);
    })

    // TODO: improve this to average data points
    // if we have too much data, we need to reduce it
    if (data.length > dataPointCount) {
        const step = Math.floor(data.length / dataPointCount);
        const filteredData: PlantData[] = [];

        for (let i = 0; i < data.length; i += step) {
            filteredData.push(data[i]);
        }

        return filteredData;
    }

    return data;
}