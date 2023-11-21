#include "imports.h"

Firebase firebase(REFERENCE_URL);

long lastUnixTime = 0;
long lastUnixTimeOffset = millis();
long currentHour = 0;

void storeTempData() {
  // TODO
}

void timeSetup() {
  const char* ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 0;
  const int daylightOffset_sec = 3600;

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if (verbose) Serial.println("Time setup");
}

long getTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    if (verbose) Serial.println("Failed to obtain time");
    return (lastUnixTime * 1000) + (millis() - lastUnixTimeOffset);
  }

  time(&lastUnixTime);
  // incase of internet loss store the last time
  lastUnixTimeOffset = millis();

  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  currentHour = atoi(timeHour);

  if (verbose) Serial.print("time   ");
  if (verbose) Serial.println(lastUnixTime);

  return lastUnixTime;
}

void writeToFirebase() {
  if (verbose) Serial.println("Writing to firebase...");

  long currentTime = getTime();

  if (WiFi.status() != WL_CONNECTED) {
    if (verbose) Serial.println("WIFI not connected");
    storeTempData();
    return;
  } else {
    if (verbose) Serial.println("connected");
  }

  String baseUrl = "esp32/" + String(currentTime);

  // Examples of setting String, integer and float values.
  firebase.setFloat(baseUrl + "/co2", co2.output);
  firebase.setFloat(baseUrl + "/humidity", humid.output);
  firebase.setFloat(baseUrl + "/light", lux.output);
  firebase.setFloat(baseUrl + "/moisture1", moisture.output);
  firebase.setFloat(baseUrl + "/moisture2", moisture.output + 0.2);
  firebase.setFloat(baseUrl + "/moisture3", moisture.output + 0.4);

  firebase.setFloat(baseUrl + "/temperature", temp.output);
  firebase.setFloat(baseUrl + "/timeStamp", currentTime);
  firebase.setFloat(baseUrl + "/vocs", tvoc.output);

  if (verbose) Serial.println("Write Complete");
}

void connectWifi() {
  int startTime = millis();
  WiFi.begin(SSID, PASSWORD);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);

    // after 20 seconds dont connect
    if (millis() - startTime > 2 * 1000) {
      Serial.println("Failed to connect to WiFi");
      return;
    }
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
}
