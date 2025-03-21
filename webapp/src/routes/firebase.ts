import { initializeApp } from 'firebase/app';
import { getAnalytics } from 'firebase/analytics';

import { getDatabase, ref, set } from 'firebase/database';
import * as keys from './../keys.json';

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

export async function initAnalytics() {
	getAnalytics(app);
}

export async function populateTestData() {
	for (let i = 0; i < 10; i++) {
		const time = Math.round(Math.random() * 100000000000 + 1600000000000);

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
