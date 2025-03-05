#include <WiFi.h>
#include "time.h"
#include "keys.h"

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

long lastUnixTime = 0;
long lastUnixTimeOffset = millis();
long currentHour = 0;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

void storeTempData()
{
  // TODO
}

void timeSetup(bool verbose)
{
  const char *ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 0;
  const int daylightOffset_sec = 3600;

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if (verbose)
    Serial.println("Time setup");
}

long getTime(bool verbose)
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    if (verbose)
      Serial.println("Failed to obtain time");
    return (lastUnixTime * 1000) + (millis() - lastUnixTimeOffset);
  }

  time(&lastUnixTime);
  // incase of internet loss store the last time
  lastUnixTimeOffset = millis();

  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  currentHour = atoi(timeHour);

  if (verbose)
    Serial.print("time   ");
  if (verbose)
    Serial.println(lastUnixTime);

  return lastUnixTime;
}

void writeToFirebase()
{
  //  TODO
}

void connectWifi()
{
  int startTime = millis();
  WiFi.begin(SSID, PASSWORD);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);

    // after 20 seconds dont connect
    if (millis() - startTime > 2 * 1000)
    {
      Serial.println("Failed to connect to WiFi");
      return;
    }
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
}

void firebaseSetup()
{
  Serial.print("FIREBASE START");

  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  fbdo.setBSSLBufferSize(4096, 1024);
  Firebase.reconnectNetwork(true);
  fbdo.setResponseSize(4096);
  Firebase.begin(&config, &auth);

  Serial.print("FIREBASE SETUP");
}

void sendFirebaseData()
{
  //  TODO
  Serial.print("HERE");
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    Serial.printf("Set bool... %s\n", Firebase.setBool(fbdo, F("/test/bool"), count % 2 == 0) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get bool... %s\n", Firebase.getBool(fbdo, FPSTR("/test/bool")) ? fbdo.to<bool>() ? "true" : "false" : fbdo.errorReason().c_str());
    bool bVal;
    Serial.printf("Get bool ref... %s\n", Firebase.getBool(fbdo, F("/test/bool"), &bVal) ? bVal ? "true" : "false" : fbdo.errorReason().c_str());
    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, F("/test/int"), count) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get int... %s\n", Firebase.getInt(fbdo, F("/test/int")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    int iVal = 0;
    Serial.printf("Get int ref... %s\n", Firebase.getInt(fbdo, F("/test/int"), &iVal) ? String(iVal).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Set float... %s\n", Firebase.setFloat(fbdo, F("/test/float"), count + 10.2) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get float... %s\n", Firebase.getFloat(fbdo, F("/test/float")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Set double... %s\n", Firebase.setDouble(fbdo, F("/test/double"), count + 35.517549723765) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get double... %s\n", Firebase.getDouble(fbdo, F("/test/double")) ? String(fbdo.to<double>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Set string... %s\n", Firebase.setString(fbdo, F("/test/string"), "Hello World!") ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get string... %s\n", Firebase.getString(fbdo, F("/test/string")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());

    // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create_Edit_Parse.ino
    FirebaseJson json;

    Serial.println();
    count++;
  }
}
