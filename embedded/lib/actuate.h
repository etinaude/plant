#include "plantState.h"

#define PUMP_1_PIN 5
#define PUMP_2_PIN 3
#define PUMP_3_PIN 24

#define FAN_PIN 24
#define LED_PIN 11
#define STATUS_LED_PIN 24

void setLights(bool lightsState)
{
    digitalWrite(LED_PIN, lightsState);
}

void setPumps(bool pumpsState)
{
    if (pumpsState == true)
    {
        digitalWrite(PUMP_1_PIN, pumpsState);
        digitalWrite(PUMP_2_PIN, pumpsState);
        digitalWrite(PUMP_3_PIN, pumpsState);
        int timeDelay = 5 * 1000;
        delay(timeDelay);
        pumpsState = false;
    }

    digitalWrite(PUMP_1_PIN, pumpsState);
    digitalWrite(PUMP_2_PIN, pumpsState);
    digitalWrite(PUMP_3_PIN, pumpsState);
}

void setFans(bool fanState)
{
    digitalWrite(FAN_PIN, fanState);
}

void setStatusLed(bool state)
{
    digitalWrite(STATUS_LED_PIN, state);
}

void actuate(PlantState state)
{
    setLights(state.lights);
    setPumps(state.pumps);
    setFans(state.fan);
    setStatusLed(state.statusLED);
}

void setupOutputs()
{
    pinMode(PUMP_1_PIN, OUTPUT);
    pinMode(PUMP_2_PIN, OUTPUT);
    pinMode(PUMP_3_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}