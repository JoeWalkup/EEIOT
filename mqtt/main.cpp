
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include<PubSubClient.h>
#include <string>

const char* ssid = "SEJW";  // Enter your WiFi name
const char* password = "bob12345";  // Enter WiFi password
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* publishTopic = "testtopic/temp/outTopic/666";   // outTopic
const char* subscribeTopic = "testtopic/temp/inTopic/666";  // inTopic
#define publishTimeInterval 15000 // in seconds 

// Definitions 
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
int ledStatus = 0;
int sent = 0;
int buttonState = 0;

float potValue;
int adcValue;

WiFiClient espClient;
PubSubClient client(espClient); // define MQTTClient 


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
  //------------------------------------------

void callback(char* topic, byte* payload, int length) {
  Serial.print("Message arrived ["); // Received the incoming message
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);  // the received value is in (char)payload[i]
  }
  // Switch on the LED if an 1 was received as first character
  String load = String((char*)payload);
  int num = payload[0] - '0';
  //int num = load.toInt();
  if (num == 1){
    digitalWrite(D2, HIGH);
  } else if (num == 0){
    digitalWrite(D2, LOW);
  }
  // add your code here

}
  //------------------------------------------

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe(subscribeTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 //------------------------------------------

void setup() {
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, OUTPUT);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
//------------------------------------------
void loop() {

  if (!client.connected()) {
    reconnect(); // check for the latest value in inTopic 
  }
  client.loop();

// Publish to outTopic 
  unsigned long now = millis(); 
  if (now - lastMsg > publishTimeInterval) {
    lastMsg = now;
    int potValue = analogRead(A0);
    float voltage = potValue * (3.3 / 1024); // Convert to voltage
    char potMessage[MSG_BUFFER_SIZE];
    snprintf(potMessage, MSG_BUFFER_SIZE, "Pot Value: %f", voltage);
    Serial.print("Publish potentiometer value: ");
    Serial.println(potMessage);
    client.publish(publishTopic, potMessage);

    buttonState = digitalRead(D1);
    Serial.println(buttonState);
    if (buttonState == LOW) {
      sent = 1;
      snprintf (msg, MSG_BUFFER_SIZE, "%d", sent);
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish(publishTopic, msg);
          delay (5000);
          sent = 0;
          snprintf (msg, MSG_BUFFER_SIZE, "%d", sent);
          Serial.print("Publish message: ");
          Serial.println(msg);
          client.publish(publishTopic, msg);
        
        delay (400);
      
    }
  }
}
