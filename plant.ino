#include "CCS811-SOLDERED.h"
#include "Wire.h"
#include <DHT11.h>
#include <WiFi.h>
#include <Ewma.h>
#include "ThingSpeak.h"

// ~~~ INPUT PINS ~~~
#define LDR_1_PIN 21
#define LDR_2_PIN 22
#define LDR_3_PIN 23

#define DHT11_PIN 24

#define I2C_SDA 33
#define I2C_SCL 35

#define SOIL_1_PIN 25
#define SOIL_2_PIN 26
#define SOIL_3_PIN 27

// ~~~ OUTPUT PINS ~~~
#define PUMP_1_PIN 10
#define PUMP_2_PIN 11
#define PUMP_3_PIN 12

#define FAN_PIN 9
#define LED_PIN 10

// ~~~ ~~~ ~~~ ~~~


const char* ssid = "LAN Down Under";
const char* password = "NewZealand";

WiFiClient client;
CCS_811 ccs811;
// DHT11 dht11(34);

const int sendDelay = 1000 * 20;
const int readDelay = 1000 * 1;
const float smoothingFactor = 0.1;
const int lowLightCuttOff = 0;
const int highLightCuttOff = 0;
const int moistureCuttOff = 0;

int count = 0;
int lastSent = millis();


Ewma co2(smoothingFactor);
Ewma tvoc(smoothingFactor);
Ewma moisture(smoothingFactor);
Ewma lux(smoothingFactor);
Ewma temp(smoothingFactor);
Ewma humid(smoothingFactor);

void setup() {
  Wire.begin(33, 35);
  Serial.begin(115200);
  ccs811.begin();
  ThingSpeak.begin(client);
  setupPins();

  Serial.println("~~~ START ~~~");

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

void setupPins() {
  pinMode(LDR_1_PIN, INPUT);
  pinMode(LDR_2_PIN, INPUT);
  pinMode(LDR_3_PIN, INPUT);
  pinMode(DHT11_PIN, INPUT);
  pinMode(SOIL_1_PIN, INPUT);
  pinMode(SOIL_2_PIN, INPUT);
  pinMode(SOIL_3_PIN, INPUT);

  pinMode(PUMP_1_PIN, OUTPUT);
  pinMode(PUMP_2_PIN, OUTPUT);
  pinMode(PUMP_3_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
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

void connectWifi() {
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
}

void writeToThingSpeak() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI not connected");
    return;
  }

  Serial.println("Sending to Thing Speak...");

  ThingSpeak.setField(1, int(humid.output));
  ThingSpeak.setField(2, int(moisture.output));
  ThingSpeak.setField(3, int(co2.output));
  ThingSpeak.setField(4, int(tvoc.output));
  ThingSpeak.setField(5, int(temp.output));
  ThingSpeak.setField(6, int(lux.output));
  int httpResCode = ThingSpeak.writeFields(2333205, "KV9AW731W96C2DTE");

  printResponse(httpResCode);
}

void printResponse(int httpResCode) {
  if (httpResCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResCode);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResCode);
  }
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

void acutate() {

  // TODO get time of day
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
