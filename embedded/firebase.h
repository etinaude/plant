#include <ESP32Firebase.h>
#include "keys.h"
#include "vals.h"
#include <WiFi.h>
#include "time.h"

Firebase firebase(REFERENCE_URL);


const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

long lastUnixTime = 0;
long lastUnixTimeOffset = millis();

void storeTempData()
{
}

long getTime(){

    if (WiFi.status() != WL_CONNECTED)
    {
        return (lastUnixTime * 1000) + (millis() - lastUnixTimeOffset);
    }

    // Get the time from the server
    time_t now;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    struct tm timeinfo;

    time(&lastUnixTime);
    // incase of internet loss store the last time
    lastUnixTimeOffset = millis();

    return lastUnixTime;
}

void writeToFirebase()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WIFI not connected");
        storeTempData();
        return;
    }

    long currentTime = getTime();

    String baseUrl = "esp32/" + String(currentTime);

    Serial.println(baseUrl);

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

    Serial.println("Writing to Firebase...");
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
        if(millis() - startTime > 20*1000)
        {
            Serial.println("Failed to connect to WiFi");
            return;
        }
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
}
