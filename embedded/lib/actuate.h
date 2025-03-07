#include "plantState.h"
#include "pins.h"

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

void blinkStatus()
{
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(500);
    digitalWrite(STATUS_LED_PIN, LOW);
}

void allOff()
{
    digitalWrite(PUMP_1_PIN, LOW);
    digitalWrite(PUMP_2_PIN, LOW);
    digitalWrite(PUMP_3_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
}

void setupOutputs()
{
    pinMode(PUMP_1_PIN, OUTPUT);
    pinMode(PUMP_2_PIN, OUTPUT);
    pinMode(PUMP_3_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);

    allOff();

    digitalWrite(PUMP_1_PIN, HIGH);
    delay(100);
    digitalWrite(PUMP_2_PIN, HIGH);
    delay(100);
    digitalWrite(PUMP_3_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(FAN_PIN, HIGH);
    delay(200);

    allOff();

    blinkStatus();
}
