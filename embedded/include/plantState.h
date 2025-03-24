#include <Arduino.h>
#include "rollingAve.h"

const float lowLightCutOff = 0.2;
const float highLightCutOff = 0.9;
const float moistureCutOff = 12;
const int morningCutOff = 8; // 8 am
const int nightCutOff = 21;  // 9 pm
const float windowSize = 20;

class PlantState
{
public:
    bool pump1 = false;
    bool pump2 = false;
    bool pump3 = false;

    bool statusLED = false;
    bool lights = false;
    bool fan = false;
    bool LDR = false;
    int currentHour = 0;

    RollingAve co2 = RollingAve();
    RollingAve lux = RollingAve();
    long moistureAve = 0;
    RollingAve moisture1 = RollingAve();
    RollingAve moisture2 = RollingAve();
    RollingAve moisture3 = RollingAve();
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
        Serial.println(pump1);
        Serial.println(pump2);
        Serial.println(pump3);

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
        Serial.println(moistureAve);

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