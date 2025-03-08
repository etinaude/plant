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
    bool pumps = false;
    bool statusLED = false;
    bool lights = false;
    bool fan = false;
    bool LDR = false;
    int currentHour = 0;
    long lastUnixTime = 0;
    long lastUnixTimeOffset = 0;

    RollingAve co2 = RollingAve();
    RollingAve lux = RollingAve();
    RollingAve moisture = RollingAve();
    RollingAve tvoc = RollingAve();
    RollingAve temp = RollingAve();
    RollingAve humid = RollingAve();

    PlantState()
    {
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
        Serial.println(lux.getAvg());

        Serial.print("Moisture: ");
        Serial.println(moisture.getAvg());

        Serial.print("CO2: ");
        Serial.println(co2.getAvg());

        Serial.print("tVOC - ");
        Serial.println(tvoc.getAvg());

        Serial.print("temp - ");
        Serial.println(temp.getAvg());

        Serial.print("humidity - ");
        Serial.println(humid.getAvg());

        Serial.print("~~~~~~~~~~\n");
    }
};