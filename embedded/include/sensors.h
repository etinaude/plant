#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_CCS811.h"

#include <DHT.h>
#include <DHT_U.h>
#include "pins.h"

DHT_Unified dht(DHT_PIN, DHT22);
Adafruit_CCS811 ccs;

float readTempHumData(PlantState &state)
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    float tempRaw = event.temperature;
    if (!isnan(tempRaw))
        state.temp.reading(tempRaw);
    delay(50);

    dht.humidity().getEvent(&event);
    float humidityRaw = event.relative_humidity;
    if (!isnan(humidityRaw))
        state.humid.reading(humidityRaw);

    return humidityRaw;
}

float readLightData(PlantState &state)
{
    int LDR1 = analogRead(LDR_1_PIN);
    int LDR2 = analogRead(LDR_2_PIN);

    float luxRaw = (LDR1 + LDR2) / 2;

    state.lux.reading(luxRaw);

    return luxRaw;
}

int readMoistureData(PlantState &state)
{

    float rawMoisture1 = analogRead(SOIL_1_PIN);
    float rawMoisture2 = analogRead(SOIL_2_PIN);
    float rawMoisture3 = analogRead(SOIL_3_PIN);

    // convert to %
    float processed = (7500 - rawMoisture1) / 46;
    state.moisture1.reading(processed);

    processed = (7500 - rawMoisture2) / 46;
    state.moisture2.reading(processed);

    processed = (7500 - rawMoisture3) / 46;
    state.moisture3.reading(processed);

    float average = (rawMoisture1 + rawMoisture2 + rawMoisture3) / 3;
    state.moistureAve = state.moisture1.getAvg() + state.moisture2.getAvg() + state.moisture3.getAvg();

    Serial.println(rawMoisture1);
    Serial.println(rawMoisture2);
    Serial.println(rawMoisture3);

    return average;
}

int readCCS(PlantState &state)
{
    if (!ccs.available())
    {
        return -1;
    }
    float temp = ccs.calculateTemperature();
    ccs.setTempOffset(temp - 25.0);

    float co2Raw = ccs.geteCO2();
    float tvocRaw = ccs.getTVOC();

    state.co2.reading(co2Raw);
    state.tvoc.reading(tvocRaw);

    return co2Raw;
}

void setupSensors()
{
    pinMode(LDR_1_PIN, INPUT);
    pinMode(LDR_2_PIN, INPUT);

    pinMode(DHT_PIN, INPUT);
    pinMode(SOIL_1_PIN, INPUT);
    pinMode(SOIL_2_PIN, INPUT);
    pinMode(SOIL_3_PIN, INPUT);

    dht.begin();

    // ccs.begin();

    // use I2C_SDA and I2C_SCL for the CCS811
    Wire.begin(I2C_SDA, I2C_SCL);
    if (!ccs.begin())
        Serial.println("Failed to start CCS811 sensor! Please check your wiring.");
}

void readAllData(PlantState &state, bool verbose = false)
{
    int rawCCS = readCCS(state);
    float rawHumid = readTempHumData(state);
    int rawMoist = readMoistureData(state);
    float rawLux = readLightData(state);

    if (verbose)
    {
        Serial.println("~~~ RAW ~~~");

        Serial.print("CCS: ");
        Serial.println(rawCCS);
        Serial.print("Temp: ");
        Serial.println(rawHumid);
        Serial.print("Humid: ");
        Serial.println(rawHumid);
        Serial.print("Moist: ");
        Serial.println(rawMoist);
        Serial.print("Lux: ");
        Serial.println(rawLux);

        Serial.println("~~~~~~~~~\n");
    }
}
