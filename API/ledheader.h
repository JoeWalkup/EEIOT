#ifndef LEDHEADER_H
#define LEDHEADER_H

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

String getdata(String url) {
    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure();
    http.begin(client, url);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
        String payload = http.getString();
         Serial.print("PAYLOAD: ");
        Serial.println(payload);
        return payload;
       
    }
    else {
        Serial.println("Error getting payload"); 
        String response = http.getString();
        Serial.print("Server response: ");
        Serial.println(response);
        return "";
    }
}

int* getrgb(String url) {
    static int rgb[3];
    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure();
    http.begin(client, url);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
        String payload = http.getString();
         Serial.print("PAYLOAD: ");
        Serial.println(payload);
        int idx = 0;
        char* token = strtok((char*)payload.c_str(), "-");
        while (token != NULL && idx < 3) {
            rgb[idx++] = atoi(token); // Convert to integer and store in the array
            token = strtok(NULL, "-");
        }
        return rgb;       
    }
    else {
        Serial.println("Error getting payload"); 
        String response = http.getString();
        Serial.print("Server response: ");
        Serial.println(response);
        return 0;
    }
}

void changeled(String state) {
    if (state == "on") {
        digitalWrite(D1, HIGH);
        Serial.println("LED HIGH");
    }
    else if (state == "off") {
        digitalWrite(D1, LOW);
        Serial.println("LED LOW");
    }
}

void changeled(int R, int G, int B) {
    analogWrite(D5, R);
    analogWrite(D6, G);
    analogWrite(D7, B);

}
#endif
