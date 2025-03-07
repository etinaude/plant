#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_CCS811.h"

#include <DHT.h>
#include <DHT_U.h>
#include "pins.h"

DHT_Unified dht(DHT_PIN, DHT22);
Adafruit_CCS811 ccs;

float readTempHumData(PlantState state)
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    float tempRaw = event.temperature;
    if (!isnan(tempRaw))
        state.temp = tempRaw;
    delay(50);

    dht.humidity().getEvent(&event);
    float humidityRaw = event.relative_humidity;
    if (!isnan(humidityRaw))
        state.humid = humidityRaw;

    return tempRaw;
}

float readLightData(PlantState state)
{
    int LDR1 = analogRead(LDR_1_PIN);
    int LDR2 = analogRead(LDR_2_PIN);

    float luxRaw = (LDR1 + LDR2) / 2;

    state.lux = luxRaw;

    return luxRaw;
}

int readMoistureData(PlantState state)
{
    float rawMoisture = analogRead(SOIL_1_PIN);
    // convert to %
    float processed = (7500 - rawMoisture) / 46;

    state.moisture = processed;

    return rawMoisture;
}

int readCCS(PlantState state)
{
    if (!ccs.available())
    {
        return -1;
    }
    float temp = ccs.calculateTemperature();
    ccs.setTempOffset(temp - 25.0);

    float co2Raw = ccs.geteCO2();
    float tvocRaw = ccs.getTVOC();

    state.co2 = co2Raw;
    state.tvoc = tvocRaw;

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
    ccs.begin();
}

void readAllData(PlantState state, bool verbose = false)
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
