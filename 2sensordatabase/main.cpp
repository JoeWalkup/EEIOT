/*
 * ----------------------------------------------
 * Project/Program Name : <2sensordatabase>
 * File Name            : <main.ccp>
 * Author               : <Joseph Walkup>
 * Date                 : <23/10/24>
 * Version              : <2>
 * 
 * Purpose:
 *    <Send temp and humidity data from sensors to database>
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
 *    <Arduino, ESP8266WiFi, ESP8266HTTPClient, Adafruit Sensor DHT library, ArduinoJson>
 * 
 * 
 * ---------------------------------------------------------------------------
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <sendrequest.h> 
#include <sensortime.h>
#include <DHT.h> 
#include <Adafruit_Sensor.h>
//#include <WiFiClientSecure.h> // not needed

const char* ssid     = "SEJW"; // must be exactly as it apears - case sensitive
const char* password = "bob12345";

const char* timeZones[] = {
  "America/New_York",   // Eastern
  "America/Chicago",    // Central
  "America/Denver",     // Mountain
  "America/Los_Angeles",// Pacific
  "America/Anchorage",  // Alaska
  "Pacific/Honolulu",   // Hawaii-Aleutian
  "America/Puerto_Rico" // Atlantic
};
String timeZone = "America/Los_Angeles";

void setup () {
  Serial.begin(9600);
  delay(10); // just a short delay
  Serial.println("");
  
  // (A) Start connecting to the WiFI
  Serial.println("Connecting to WiFi"); 
  WiFi.begin(ssid, password); // Connection to WiFi Starts until status()=WL_CONNECTED
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("."); // waiting to get connected
  }
  // Details of the connection
   connectionDetails();
     dht.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
   Serial.println("Select Your Time Zone (The default time is PT):");
  Serial.println("1- Eastern Time Zone (ET) - New York City, NY");
  Serial.println("2- Central Time Zone (CT) - Chicago, IL");
  Serial.println("3- Mountain Time Zone (MT) - Denver, CO");
  Serial.println("4- Pacific Time Zone (PT) - Los Angeles, CA");
  Serial.println("5- Alaska Time Zone (AKT) - Anchorage, AK");
  Serial.println("6- Hawaii-Aleutian Time Zone (HAT) - Honolulu, HI");
  Serial.println("7- Atlantic Time Zone (AT) - San Juan, PR");
  Serial.print("Enter a number between 1-7 to select your time zone: ");

  while (!Serial.available()) {
    delay(200);
  }

  // Read the input
  int selection = Serial.parseInt();
  // Display the input
  Serial.println(selection);

  // Check if input is valid
  if (selection >= 1 && selection <= 7) {
    // Set timeZone based on user input 
    timeZone = timeZones[selection - 1];
    Serial.print("Time zone set to: ");
    Serial.println(timeZone);
  } else {
    // Set timezone to default if input is invalid
    Serial.println("Invalid selection. Using default time zone (Pacific Time).");
  }

}
void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("button pressed");
    delay(150);

    float temp = readtemperature();
    float humid = readhumidity();
  if (isnan(temp) || isnan(humid)) {
      Serial.println("sensor error");
    } 
    else {
      String currenttime = getCurrentTime(timeZone);
      transmitdata(temp, humid,currenttime);
      Serial.println();
    }
    while (digitalRead(BUTTON_PIN) == LOW) {
      yield();}
    
    
    }
delay(200);
}
