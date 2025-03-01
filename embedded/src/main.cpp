#include "./../lib/actuate.h"
#include "./../lib/sensors.h"
#include "./../lib/interwebs.h"

int lastSent = millis();
PlantState state;
const bool verbose = true;

const int sendDelay = 1000 * 60;
const int readDelay = 1000 * 1;

void setup()
{
  setupSensors();

  Serial.begin(115200);
  if (verbose)
    Serial.println("~~~ START ~~~");

  delay(500);

  // connectWifi();
  // timeSetup();
}

void loop()
{
  readAllData(state);
  state.set(moisture, lux);
  actuate(state);

  if (verbose)
    state.print();
  // if (verbose) printState();

  delay(readDelay);

  // send data
  if (millis() - lastSent < sendDelay)
    return;
  lastSent = millis();
  // writeToFirebase();
}