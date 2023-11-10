import { initializeApp } from "firebase/app";
import { getFirestore } from "firebase/firestore";
import * as keys from "./../keys.json"
import { collection, getDocs, addDoc } from "firebase/firestore";


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
}

export class DataSet {
    label: string;
    borderColor: string;
    pointBorderColor: string;
    data: number[];

    lineTension: 0.5;
    pointBorderWidth: 5;
    pointRadius: 1;
    pointHitRadius: 5;

    constructor(plantData: PlantData[], field: keyof (PlantData), colour: string) {
        this.label = field;
        this.borderColor = colour;
        this.pointBorderColor = colour;
        this.data = plantData.map((item) => {
            return item[field];
        })

        this.lineTension = 0.5;
        this.pointBorderWidth = 5;
        this.pointRadius = 1;
        this.pointHitRadius = 5;
    }
}

export class ChartData {
    title: string;
    labels: string[];
    datasets: DataSet[];

    constructor(data: DataSet, title: string) {
        this.title = title;
        this.datasets = [data];

        this.labels = firebaseData.map((item) => {
            const date = new Date(item.timeStamp);
            return `${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`;
        });
    }

    appendDataSet(data: DataSet) {
        this.datasets.push(data)
    }
}

const firebaseConfig = {
    apiKey: keys.apiKey,
    authDomain: keys.authDomain,
    projectId: keys.projectId,
    storageBucket: keys.storageBucket,
    messagingSenderId: keys.messagingSenderId,
    appId: keys.appId,
    measurementId: keys.measurementId
};

const app = initializeApp(firebaseConfig);
const db = getFirestore(app);
const firebaseData: PlantData[] = [];
export let lightData: ChartData;
export let moistureData: ChartData;
export let humidityData: ChartData;
export let co2Data: ChartData;
export let temperatureData: ChartData;
export let vocsData: ChartData;
export let allData: ChartData;

async function getFirebaseData() {
    const querySnapshot = await getDocs(collection(db, "plant"));
    querySnapshot.forEach((doc) => {
        firebaseData.push(doc.data() as PlantData);
    });
}

async function setChartData() {
    const lightDataset = new DataSet(firebaseData, "light", "#ede324");
    const moisture1Dataset = new DataSet(firebaseData, "moisture1", "#24aaed");
    const moisture2Dataset = new DataSet(firebaseData, "moisture2", "#2442ed");
    const moisture3Dataset = new DataSet(firebaseData, "moisture3", "#247bed");
    const tempDataset = new DataSet(firebaseData, "temperature", "#ed9624");
    const vocsDataset = new DataSet(firebaseData, "vocs", "#444");
    const co2Dataset = new DataSet(firebaseData, "co2", "#777");
    const humidityDataset = new DataSet(firebaseData, "humidity", "#24edbe");


    lightData = new ChartData(lightDataset, "Light 💡");
    moistureData = new ChartData(moisture1Dataset, "Moisture 💧");
    humidityData = new ChartData(humidityDataset, "Humidity 💦");
    temperatureData = new ChartData(tempDataset, "Temperature 🌡️");
    vocsData = new ChartData(vocsDataset, "VOCs 🌫️");
    co2Data = new ChartData(co2Dataset, "CO2 ☁️");

    moistureData.appendDataSet(moisture2Dataset);
    moistureData.appendDataSet(moisture3Dataset);
}


async function populateFakeData() {
    for (let i = 0; i < 500; i++) {
        const tempData: PlantData = {
            co2: Math.random() * 1000,
            light: Math.random() * 100,
            moisture1: Math.random() * 100,
            moisture2: Math.random() * 100,
            moisture3: Math.random() * 100,
            temperature: Math.random() * 60,
            humidity: Math.random() * 100,
            vocs: Math.random() * 20,
            timeStamp: (Math.random() * 100000000000) + 1600000000000
        }

        await addDoc(collection(db, "plant"), tempData);
    }
}


async function getData() {
    await getFirebaseData();
    setChartData();
}

getData();

// populateFakeData();