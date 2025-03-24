#include "plantState.h"
#include "pins.h"

void setLights(bool lightsState)
{
    digitalWrite(LED_PIN, lightsState);
}

void setPumps(PlantState &state)
{
    if (state.pump1 == true)
    {
        digitalWrite(PUMP_1_PIN, true);
        int timeDelay = 5 * 1000;
        delay(timeDelay);
        state.pump1 = false;
    }
    digitalWrite(PUMP_1_PIN, state.pump1);

    if (state.pump2 == true)
    {
        digitalWrite(PUMP_2_PIN, true);
        int timeDelay = 5 * 1000;
        delay(timeDelay);
        state.pump2 = false;
    }
    digitalWrite(PUMP_2_PIN, state.pump2);

    if (state.pump3 == true)
    {
        digitalWrite(PUMP_3_PIN, true);
        int timeDelay = 5 * 1000;
        delay(timeDelay);
        state.pump3 = false;
    }
    digitalWrite(PUMP_3_PIN, state.pump3);
}

void setFans(bool fanState)
{
    digitalWrite(FAN_PIN, fanState);
}

void setStatusLed(bool state)
{
    digitalWrite(STATUS_LED_PIN, state);
}

void setState(PlantState &state, bool verbose = false)
{
    if (verbose)
        Serial.println("Setting State");
    if (state.lux.getAvg() < lowLightCutOff)
        state.lights = true;
    if (state.lux.getAvg() > highLightCutOff)
        state.lights = false;

    if (state.moisture1.getAvg() < moistureCutOff)
        state.pump1 = true;
    else
        state.pump1 = false;

    if (state.moisture2.getAvg() < moistureCutOff)
        state.pump2 = true;
    else
        state.pump2 = false;

    if (state.moisture3.getAvg() < moistureCutOff)
        state.pump3 = true;
    else
        state.pump3 = false;

    Serial.println("Current Hour: " + String(state.currentHour));
    if (state.currentHour < morningCutOff || state.currentHour > nightCutOff)
    {
        state.lights = false;
        state.fan = false;
    }
    else
    {
        state.lights = true;
        state.fan = true;
    }

    if (verbose)
        state.printOutputs();
    if (verbose)
        Serial.println("Done setting state");
}

void actuate(PlantState &state, bool verbose = false)
{
    if (verbose)
        Serial.println("Actuating");
    setLights(state.lights);
    setFans(state.fan);
    // setPumps(state);
    setStatusLed(state.statusLED);
    if (verbose)
        Serial.println("Done actuating");
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
