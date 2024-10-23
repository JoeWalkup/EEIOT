/*
 * ----------------------------------------------
 * Project/Program Name : <2sensordatabase>
 * File Name            : <sendrequest.h>
 * Author               : <Joseph Walkup>
 * Date                 : <23/10/24>
 * Version              : <2>
 * 
 * Purpose:
 *    <Functions for sending data to database>
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
 *    <Arduino, ESP8266WiFi, ESP8266HTTPClient>
 * 
 * 
 * ---------------------------------------------------------------------------
 */
#ifndef SENDREQUEST_H
#define SENDREQUEST_H
#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
void connectionDetails()
{
  // Details of the connection
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
  Serial.print("Channel:\t");
  Serial.println(WiFi.channel());          
  Serial.print("RSSI:\t");
  Serial.println(WiFi.RSSI());   
  Serial.print("DNS IP:\t");
  Serial.println(WiFi.dnsIP(1));            // get the DNS IP Address    
  Serial.print("Gateway IP:\t");
  Serial.println(WiFi.gatewayIP()); 
  Serial.println("---------------------");    
}

void transmitdata(float temp, float humid, const String& timestamp){
  WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure(); // Bypass SSL certificate validation

    // Encode timestamp
    String encodedtime = timestamp;
    encodedtime.replace(" ", "%20");
    encodedtime.replace(":", "%3A");

    // Construct the URL
    String url = "https://josephwalkup.net/createdatabase/add.php?node_name=node-1&time_received=";
    url += encodedtime;
    url += "&temperature=" + String(temp);
    url  += "&humidity=" + String(humid);

    // GET request
    http.begin(client, url);
    int httpResponseCode = http.GET();

    Serial.println("Response code <-- " + String(httpResponseCode));
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("Server response: ");
        Serial.println(response);
        Serial.println("___");
    } 
    else {
        Serial.println("Unable to connect");
    }
    http.end(); 



}

#endif
