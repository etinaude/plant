#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_CCS811.h"

#include <DHT.h>
#include <DHT_U.h>
#include <Ewma.h>

#define LDR_1_PIN 37
#define DHT_PIN 39

#define I2C_SDA 18
#define I2C_SCL 33

#define SOIL_1_PIN 16
#define SOIL_2_PIN 23
#define SOIL_3_PIN 23

DHT_Unified dht(DHT_PIN, DHT22);
Adafruit_CCS811 ccs;

const float smoothingFactor = 0.7;

Ewma co2(smoothingFactor);
Ewma tvoc(smoothingFactor);
Ewma moisture(smoothingFactor);
Ewma lux(smoothingFactor);
Ewma temp(smoothingFactor);
Ewma humid(smoothingFactor);

void readTempHumData()
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    float tempRaw = event.temperature;
    delay(50);

    dht.humidity().getEvent(&event);
    float humidityRaw = event.relative_humidity;

    temp.filter(tempRaw);
    humid.filter(humidityRaw);
}

int readLightData(PlantState state)
{
    lux.filter(state.LDR);
    return !digitalRead(LDR_1_PIN);
}

void readMoistureData()
{
    float rawMoisture = analogRead(SOIL_1_PIN);
    // convert to %
    float processed = (7500 - rawMoisture) / 46;

    moisture.filter(processed);
}

void readCCS()
{
    if (!ccs.available())
    {
        return;
    }
    float temp = ccs.calculateTemperature();
    ccs.setTempOffset(temp - 25.0);

    float co2Raw = ccs.geteCO2();
    float tvocRaw = ccs.getTVOC();

    co2.filter(co2Raw);
    tvoc.filter(tvocRaw);
}

void setupSensors()
{

    pinMode(LDR_1_PIN, INPUT);
    pinMode(DHT_PIN, INPUT);
    pinMode(SOIL_1_PIN, INPUT);
    pinMode(SOIL_2_PIN, INPUT);
    pinMode(SOIL_3_PIN, INPUT);

    dht.begin();
    ccs.begin();
    pinMode(LDR_1_PIN, INPUT);
    pinMode(SOIL_1_PIN, INPUT);
}

void readAllData(PlantState state)
{
    readCCS();
    readTempHumData();
    readMoistureData();
    readLightData(state);
}

void printData()
{
    Serial.print("DATA");
    Serial.print("\t LDR: ");
    Serial.print(lux.output);

    Serial.print("\t Moisture: ");
    Serial.print(moisture.output);

    Serial.print("\t CO2: ");
    Serial.print(co2.output);

    Serial.print("\t tVOC - ");
    Serial.print(tvoc.output);

    Serial.print("\t temp - ");
    Serial.print(temp.output);

    Serial.print("\t humidity - ");
    Serial.println(humid.output);
}