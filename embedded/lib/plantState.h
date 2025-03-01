#include <Arduino.h>
#include <Ewma.h>

const float lowLightCutOff = 0.2;
const float highLightCutOff = 0.9;
const float moistureCutOff = 12;
const int morningCutOff = 10; // 10 am
const int nightCutOff = 20;   // 8 pm

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

    void print()
    {
        Serial.print("State");

        Serial.print("\t Pumps: ");
        Serial.print(pumps);

        Serial.print("\t Status: ");
        Serial.print(statusLED);

        Serial.print("\t Lights: ");
        Serial.print(lights);

        Serial.print("\t LDR - ");
        Serial.print(LDR);

        Serial.print("\t Fan - ");
        Serial.println(fan);
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