#include "CCS811-SOLDERED.h"
#include "Wire.h"
#include <DHT11.h>

#include <Ewma.h>
#include "thingSpeak.h"

int count = 0;
int lastSent = millis();

void setup() {
  Wire.begin(33, 35);
  ccs811.begin();

  setupPins();
  Serial.begin(115200);

  Serial.println("~~~ START ~~~");

  ThingSpeak.begin(client);
  delay(1000);
  connectWifi();
}

void loop() {
  readAllData();
  printData();

  delay(readDelay);
  count++;

  // send data
  if (millis() - lastSent < sendDelay) return;
  lastSent = millis();
  count = 0;

  acutate();
  writeToThingSpeak();
}

void readAllData() {
  readMoistureData();
  readlightData();
  readCCS();
}

void readlightData() {
}

void readMoistureData() {
}

void readCCS() {
  if (!ccs811.dataAvailable()) { return; }
  ccs811.readAlgorithmResults();

  int co2Raw = ccs811.getCO2();
  int tvocRaw = ccs811.getTVOC();
  co2.filter(co2Raw);
  tvoc.filter(tvocRaw);
}

void printData() {
  Serial.print(count);

  Serial.print("\tCO2: ");
  Serial.print(co2.output);

  Serial.print("\t tVOC - ");
  Serial.print(tvoc.output);

  Serial.print("\t temp - ");
  Serial.print(temp.output);

  Serial.print("\t humidity - ");
  Serial.println(humid.output);
}

void toggleLights(int val) {
  digitalWrite(LED_PIN, val);
}

void togglePumps(int val) {
  digitalWrite(PUMP_1_PIN, val);
  digitalWrite(PUMP_2_PIN, val);
  digitalWrite(PUMP_3_PIN, val);
}

void toggleFans(int val) {
  digitalWrite(FAN_PIN, val);
}

void setStatusLed(){
  // TODO
}

void acutate() {

  // TODO get time of day from server or show red light
  // if night turn all off and return
  if (false) {
    toggleFans(0);
    togglePumps(0);
    toggleLights(0);

    return;
  }

  toggleFans(1);

  if (moisture.output < moistureCuttOff) {
    togglePumps(1);
    int timeDelay = 5 * 1000;
    delay(timeDelay);
    togglePumps(0);
  }

  if (lux.output < lowLightCuttOff) {
    toggleLights(1);
  }

  if (lux.output > highLightCuttOff) {
    toggleLights(0);
  }
}
