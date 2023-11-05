#include "ThingSpeak.h"
#include "vals.h"
#include <WiFi.h>

WiFiClient client;
CCS_811 ccs811;

const char* ssid = "LAN Down Under";
const char* password = "NewZealand";

void printResponse(int httpResCode) {
  if (httpResCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResCode);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResCode);
  }
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

