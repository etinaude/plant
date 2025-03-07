#include "./../lib/actuate.h"
#include "./../lib/sensors.h"
#include "./../lib/interwebs.h"

int lastSent = millis();
PlantState state;

const bool VERBOSE = true;
const bool ENABLE_WIFI = false;

const int sendDelay = 1000 * 60;
const int readDelay = 1000 * 1;

void setup()
{
  Serial.begin(115200);
  setupSensors();
  setupOutputs();

  Serial.println("~~~ START ~~~");

  if (ENABLE_WIFI)
  {
    connectWifi();
    firebaseSetup();
    timeSetup(ENABLE_WIFI);
  }
}

void loop()
{

  readAllData(state, VERBOSE);

  if (VERBOSE)
  {
    state.printData();
    state.printOutputs();
  }

  delay(readDelay);

  return; // remove to actually do stuff
  actuate(state);

  // send data
  if (millis() - lastSent < sendDelay)
    return;

  lastSent = millis();
  // writeToFirebase();
}