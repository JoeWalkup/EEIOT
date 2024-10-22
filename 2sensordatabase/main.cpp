
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <sendrequest.h> // required header file
//#include <WiFiClientSecure.h> // not needed

const char* ssid     = "SEJW"; // must be exactly as it apears - case sensitive
const char* password = "bob12345";
int i;
String url     = "https://josephwalkup.net/createdatabase/add.php";
String data1   = "?node_name=node-1&time_received=2022-10-01%2011:00:00&temperature=70&humidity=70"; // currently empty

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
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;

    // For testing only

    String fullUrl = url + data1; // preparing the full URL
    Serial.println("Requesting: --> " + fullUrl);
    i = 0;
    while (i == 0) {
    if (https.begin(client, fullUrl)) { // start the connection 1=started / 0=failed

      int httpCode = https.GET(); // choose GET or POST method
      //int httpCode = https.POST(fullUrl); // need to include URL
      
      Serial.println("Response code <--: " + String(httpCode)); // print response code: e.g.,:200
      if (httpCode == 200) {
        //Serial.println(https.getString()); // this is the content of the get request received
      i = 1;
      }
    else {
        Serial.printf("[HTTPS] Unable to connect\n");
    }}
          https.end(); // end of request
  }
  delay(5000); // delay between each REQUEST to the server

}}

