#include <Arduino.h>
#include <Ewma.h>

const float lowLightCutOff = 0.2;
const float highLightCutOff = 0.9;
const float moistureCutOff = 12;
const int morningCutOff = 10; // 10 am
const int nightCutOff = 20;   // 8 pm
const float smoothingFactor = 0.7;

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

    Ewma co2 = Ewma(smoothingFactor);
    Ewma lux = Ewma(smoothingFactor);
    Ewma moisture = Ewma(smoothingFactor);
    Ewma tvoc = Ewma(smoothingFactor);
    Ewma temp = Ewma(smoothingFactor);
    Ewma humid = Ewma(smoothingFactor);

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
    }

    void printOutputs()
    {
        Serial.print("~~~State~~~");

        Serial.print("Pumps: ");
        Serial.println(pumps);

        Serial.print("Status: ");
        Serial.println(statusLED);

        Serial.print("Lights: ");
        Serial.println(lights);

        Serial.print("\t Fan - ");
        Serial.println(fan);
        Serial.print("~~~~~~~~~\n");
    }

    void printData()
    {
        Serial.println("~~~DATA~~~");
        Serial.print("LDR: ");
        Serial.println(lux.output);

        Serial.print("Moisture: ");
        Serial.println(moisture.output);

        Serial.print("CO2: ");
        Serial.println(co2.output);

        Serial.print("tVOC - ");
        Serial.println(tvoc.output);

        Serial.print("temp - ");
        Serial.println(temp.output);

        Serial.print("humidity - ");
        Serial.println(humid.output);

        Serial.print("~~~~~~~~~~\n");
    }

    void set(Ewma moisture, Ewma lux)
    {
        // TODO get time of day from server or show red light
        // if night turn all off and return
        if (currentHour < morningCutOff || currentHour > nightCutOff)
        {
            pumps = false;
            lights = false;
            fan = false;
            return;
        }

        pumps = moisture.output < moistureCutOff;
        fan = true;

        if (lux.output < lowLightCutOff)
        {
            lights = true;
        }

        if (lux.output > highLightCutOff)
        {
            lights = false;
        }
    }
};