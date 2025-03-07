#include <Arduino.h>
#include "rollingAve.h"

const float lowLightCutOff = 0.2;
const float highLightCutOff = 0.9;
const float moistureCutOff = 12;
const int morningCutOff = 10; // 10 am
const int nightCutOff = 20;   // 8 pm
const float windowSize = 20;

class PlantState
{
public:
    bool pumps;
    bool statusLED;
    bool lights;
    bool fan;
    bool LDR;
    int currentHour;
    long lastUnixTime;
    long lastUnixTimeOffset;

    long co2;
    long lux;
    long moisture;
    long tvoc;
    long temp;
    long humid;

    PlantState()
    {
        pumps = false;
        statusLED = false;
        lights = false;
        fan = false;
        LDR = false;
        currentHour = 0;
        lastUnixTime = 0;
        lastUnixTimeOffset = 0;

        Serial.println("Plant State Initialized");
    }

    void printOutputs()
    {
        Serial.println("~~~State~~~");

        Serial.print("Pumps: ");
        Serial.println(pumps);

        Serial.print("Status: ");
        Serial.println(statusLED);

        Serial.print("Lights: ");
        Serial.println(lights);

        Serial.print("Fan - ");
        Serial.println(fan);
        Serial.print("~~~~~~~~~\n");
    }

    void printData()
    {
        Serial.println("~~~DATA~~~");
        Serial.print("LDR: ");
        Serial.println(lux);

        Serial.print("Moisture: ");
        Serial.println(moisture);

        Serial.print("CO2: ");
        Serial.println(co2);

        Serial.print("tVOC - ");
        Serial.println(tvoc);

        Serial.print("temp - ");
        Serial.println(temp);

        Serial.print("humidity - ");
        Serial.println(humid);

        Serial.print("~~~~~~~~~~\n");
    }
};