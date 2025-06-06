#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseClient.h>

#include "time.h"
#include "keys.h"

long lastUnixTime = 0;
long lastUnixTimeOffset = millis();
long currentHour = 0;
int lastSent = millis();
const int sendDelay = 30;

void asyncCB(AsyncResult &aResult);
void processData(AsyncResult &aResult);

UserAuth user_auth(API_KEY, USER_EMAIL, USER_PASSWORD);
FirebaseApp app;
WiFiClientSecure ssl_client1;
using AsyncClient = AsyncClientClass;
AsyncClient async_client(ssl_client1);

RealtimeDatabase Database;

bool onetimeTest = false;
AsyncResult dbResult;

void storeTempData()
{
  // TODO
}

void reconnectWifi()
{
  int startTime = millis();
  Serial.println("\nreconnecting");
  WiFi.disconnect();
  WiFi.reconnect();

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);

    // after 10 seconds dont connect
    if (millis() - startTime > 10 * 1000)
    {
      Serial.println("Failed to connect to WiFi");
      return;
    }
  }
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

long getTime(PlantState &state, bool verbose = false)
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    if (verbose)
      Serial.println("Failed to obtain time");

    reconnectWifi();
    return (lastUnixTime * 1000) + (millis() - lastUnixTimeOffset);
  }

  time(&lastUnixTime);
  // incase of internet loss store the last time
  lastUnixTimeOffset = millis();

  // get the current hour
  state.currentHour = timeinfo.tm_hour;

  if (verbose)
    Serial.print("time   ");
  if (verbose)
    Serial.println(lastUnixTime);

  return lastUnixTime;
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

    // after 10 seconds dont connect
    if (millis() - startTime > 10 * 1000)
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
  ssl_client1.setInsecure();

  initializeApp(async_client, app, getAuth(user_auth), processData, "🔐 authTask");

  app.getApp<RealtimeDatabase>(Database);

  Database.url(DATABASE_URL);
}

bool sendData(String path, double data, bool verbose = false)
{
  if (verbose)
  {
    Serial.print("Sending data to: ");
    Serial.print(path);
    Serial.print("Data: ");
    Serial.println(data);
  }

  bool status = Database.set<double>(async_client, path, data);
  if (!status)
    Serial.printf("Error, msg: %s, code: %d\n", async_client.lastError().message().c_str(), async_client.lastError().code());

  return status;
}

bool writeToFirebase(PlantState &state, bool verbose = false)
{
  app.loop();
  String path = "/data/" + String(lastUnixTime);

  if (!app.ready())
  {
    if (verbose)
      Serial.println("App not ready");
    return false;
  }

  if (!sendData(path + "/co2", state.co2.getAvg(), verbose))
    return false;
  if (!sendData(path + "/lux", state.lux.getAvg(), verbose))
    return false;
  if (!sendData(path + "/moisture1", state.moisture1.getAvg(), verbose))
    return false;
  if (!sendData(path + "/moisture2", state.moisture2.getAvg(), verbose))
    return false;
  if (!sendData(path + "/moisture3", state.moisture3.getAvg(), verbose))
    return false;
  if (!sendData(path + "/tvoc", state.tvoc.getAvg(), verbose))
    return false;
  if (!sendData(path + "/temp", state.temp.getAvg(), verbose))
    return false;
  if (!sendData(path + "/humid", state.humid.getAvg(), verbose))
    return false;
  if (!sendData(path + "/timeStamp", lastUnixTime, verbose))
    return false;

  return true;
}

void processData(AsyncResult &aResult)
{
  if (!aResult.isResult())
    return;

  if (aResult.isEvent())
    Serial.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.eventLog().message().c_str(), aResult.eventLog().code());

  if (aResult.isDebug())
    Serial.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());

  if (aResult.isError())
    Serial.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());

  if (aResult.available())
    Serial.printf("task: %s, payload: %s\n", aResult.uid().c_str(), aResult.c_str());
}

void interWebsLoop(PlantState &state, bool verbose = false)
{
  if (WiFi.status() != WL_CONNECTED)
    reconnectWifi();

  int currentTime = getTime(state, verbose);

  if (currentTime - lastSent < sendDelay)
    return;

  bool writeSuccess = writeToFirebase(state, verbose);

  Serial.write("Write Success: ");
  Serial.println(writeSuccess);

  if (writeSuccess)
    lastSent = currentTime;
}
