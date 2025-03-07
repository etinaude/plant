#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "./../lib/actuate.h"
#include "./../lib/sensors.h"
#include "./../lib/interwebs.h"

int lastSent = millis();
PlantState state = PlantState();

const bool VERBOSE = true;
const bool ENABLE_WIFI = false;

const int sendDelay = 30;
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
  actuate(state);

  if (!ENABLE_WIFI)
    return;

  int currentTime = getTime();

  Serial.print("state.lux.output");
  Serial.println(state.lux);

  // send data
  if (currentTime - lastSent > sendDelay)
  {

    bool writeSuccess = writeToFirebase(state, VERBOSE);

    Serial.write("Write Success: ");
    Serial.println(writeSuccess);

    if (writeSuccess)
      lastSent = currentTime;
  }
}