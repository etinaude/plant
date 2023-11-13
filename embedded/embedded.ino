#include "CCS811-SOLDERED.h"
#include "Wire.h"
#include "DHT.h"

#include <Ewma.h>
#include "firebase.h"
#include "parameters.h"
#include "state.h"

CCS_811 ccs811;
int count = 0;
int lastSent = millis();

void setup()
{
  setupPins();
  ccs811.begin();
  dht.begin();

  Serial.begin(115200);
  Serial.println("~~~ START ~~~");

  delay(500);
  connectWifi();
}

void loop()
{
  readAllData();

  setState();
  actuate();

  printData();
  printState();

  delay(readDelay);
  count++;

  // send data
  if (millis() - lastSent < sendDelay)
    return;
  lastSent = millis();
  count = 0;

  writeToFirebase();
}

void readAllData()
{
  readCCS();
  // readTempHumData();
  readMoistureData();
  readLightData();
}

void readTempHumData()
{
  float humidityRaw = dht.readHumidity();
  delay(50);
  float tempRaw = dht.readTemperature();

  temp.filter(tempRaw);
  humid.filter(humidityRaw);
}

void readLightData()
{
  LDRState = !digitalRead(LDR_1_PIN);

  lux.filter(LDRState);
}

void readMoistureData()
{
  float rawMoisture = analogRead(SOIL_1_PIN);
  moisture.filter(rawMoisture);
}

void readCCS()
{
  if (!ccs811.dataAvailable())
  {
    return;
  }
  ccs811.readAlgorithmResults();

  int co2Raw = ccs811.getCO2();
  int tvocRaw = ccs811.getTVOC();
  co2.filter(co2Raw);
  tvoc.filter(tvocRaw);
}

void printData()
{
  Serial.print("Data:");
  Serial.print("\t count: ");
  Serial.print(count);

  Serial.print("\t LDR: ");
  Serial.print(lux.output);

  Serial.print("\t Moisture: ");
  Serial.print(moisture.output);

  Serial.print("\t CO2: ");
  Serial.print(co2.output);

  Serial.print("\t tVOC - ");
  Serial.print(tvoc.output);

  Serial.print("\t temp - ");
  Serial.print(temp.output);

  Serial.print("\t humidity - ");
  Serial.println(humid.output);
}

void printState()
{
  Serial.print("State");

  Serial.print("\t Pumps: ");
  Serial.print(pumpsState);

  Serial.print("\t Status: ");
  Serial.print(statusState);

  Serial.print("\t Lights: ");
  Serial.print(lightsState);

  Serial.print("\t LDR - ");
  Serial.print(LDRState);

  Serial.print("\t Fan - ");
  Serial.println(fanState);
}

void setLights()
{
  digitalWrite(LED_PIN, lightsState);
}

void setPumps()
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

void setFans()
{
  digitalWrite(FAN_PIN, fanState);
}

void setStatusLed()
{
  // TODO
}

void actuate()
{
  setFans();
  setPumps();
  setLights();
  setStatusLed();
}

void setState()
{
  // TODO get time of day from server or show red light
  // if night turn all off and return
  if (false)
  {
    pumpsState = false;
    lightsState = false;
    fanState = false;
    return;
  }

  fanState = true;

  if (moisture.output < moistureCutOff)
  {
    pumpsState = true;
    setPumps();

    int timeDelay = 5 * 1000;
    delay(timeDelay);
    pumpsState = false;
    setPumps();
  }

  if (lux.output < lowLightCutOff)
  {
    lightsState = true;
  }

  if (lux.output > highLightCutOff)
  {
    lightsState = false;
  }
}
