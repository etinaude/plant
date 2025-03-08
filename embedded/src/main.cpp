#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "actuate.h"
#include "sensors.h"
#include "interwebs.h"

PlantState state = PlantState();

const bool VERBOSE = true;
const bool ENABLE_WIFI = true;

const int readDelay = 1000 * 1;

void setup()
{
  delay(1000);
  Serial.begin(115200);
  setupSensors();
  setupOutputs();

  Serial.println("~~~ START ~~~");

  if (ENABLE_WIFI)
  {
    connectWifi();
    timeSetup(VERBOSE);
    firebaseSetup();
  }
}

void loop()
{
  delay(readDelay);
  if (VERBOSE)
  {
    Serial.println("~~~ LOOP ~~~");
    state.printData();
    state.printOutputs();
  }

  readAllData(state, VERBOSE);
  actuate(state, VERBOSE);

  if (!ENABLE_WIFI)
    return;

  // send data
  interWebsLoop(state, VERBOSE);
}