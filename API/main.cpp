#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ledheader.h>

String LEDstate;
int RGB[3];
int R;
int G;
int B;
void setup() {
  pinMode(D1, OUTPUT); //LED
  pinMode(D5, OUTPUT); //R
  pinMode(D6, OUTPUT); //G
  pinMode(D7, OUTPUT); //B
const char* ssid     = "Erick's iPhone"; 
const char* password = "Ramirez510";
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
     connectionDetails();
}

void loop() {
  Serial.println("loop start");
delay(5000);

LEDstate = getdata("https://josephwalkup.net/api/tp.txt");
changeled(LEDstate);

int* rgbvalues = getrgb("https://josephwalkup.net/api/tp2.txt");

if (rgbvalues != NULL) {
        for (int i = 0; i < 3; i++) {
            RGB[i] = rgbvalues[i];
        }}

R = RGB[0];
G = RGB[2];
B=  RGB[1];
changeled(R,G,B);
Serial.println("loop end");

}
