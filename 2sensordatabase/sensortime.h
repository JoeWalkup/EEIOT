/*
 * ----------------------------------------------
 * Project/Program Name : <2sensordatabase>
 * File Name            : <main.ccp>
 * Author               : <Joseph Walkup>
 * Date                 : <23/10/24>
 * Version              : <2>
 * 
 * Purpose:
 *    <Retreive sensor data and current time data>
 * 
 * Inputs:
 *    <Timezone
 *    Temperature
 *    Humidity>
 * 
 * Outputs:
 *    <"Serial Outputs">
 * 
 * Example Application:
 *    <When button is pressed the current time, temperature, and humididty is sent to a database>
 * 
 * Dependencies:
 *    <Arduino, ESP8266WiFi, ESP8266HTTPClient, ArduinoJson>
 * 
 * 
 * ---------------------------------------------------------------------------
 */

#ifndef SENSORTIME_H
#define SENSORTIME_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h> 
// #include <Adafruit_Sensor.h>


#define BUTTON_PIN D1
#define SENSOR_PIN D2
#define DHTTYPE DHT11
extern DHT dht;

DHT dht(SENSOR_PIN, DHTTYPE); 
float readtemperature() {
    float temp = dht.readTemperature(); // Get temperature in Celsius
    if (isnan(temp)) {
        Serial.println("Failed to read temperature");
        return temp;
    }
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" C°");
    return temp;
}

float readhumidity() {
    float humid = dht.readHumidity(); // Get humidity
    if (isnan(humid)) {
        Serial.println("Failed to read humidity");
        return humid;
    }
    Serial.print("Humidity: ");
    Serial.print(humid);
    Serial.println(" %");
    return humid;
}



String getCurrentTime(const String& timeZone) {
    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure(); // Bypass SSL certificate validation
    String url = "https://timeapi.io/api/Time/current/zone?timeZone=" + timeZone;
    http.begin(client, url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
        String payload = http.getString();

        // Parse the JSON response
        DynamicJsonDocument jsonDoc(400);
        DeserializationError error = deserializeJson(jsonDoc, payload); // Handle error
        if (error) {
            Serial.print("JSON parsing error: ");
            Serial.println(error.c_str());
            return "";
        }
        String dateTime = jsonDoc["dateTime"];
        dateTime.replace("T", " ");
        int dotIndex = dateTime.indexOf('.');
        if (dotIndex != -1) {
            dateTime = dateTime.substring(0, dotIndex);  
        }
        Serial.println("Current Time: " + dateTime);
        return dateTime;
    } else {
        Serial.print("Error getting time"); 
        return "";
    }
    http.end();
}
#endif
