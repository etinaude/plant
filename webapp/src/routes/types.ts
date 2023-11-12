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

    lineTension: 0.5;
    pointBorderWidth: 5;
    pointRadius: 1;
    pointHitRadius: 5;

    constructor(plantData: PlantData[], field: keyof PlantData, colour: string) {
        this.field = field;
        this.borderColor = colour;
        this.pointBorderColor = colour;

        this.lineTension = 0.5;
        this.pointBorderWidth = 5;
        this.pointRadius = 1;
        this.pointHitRadius = 5;

        this.data = [];
        this.labels = [];

        plantData.forEach((item => {
            this.data.push(item[field]);
            this.labels.push(new Date(item.timeStamp).toLocaleTimeString())

        }))
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
}