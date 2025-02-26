#include <WiFi.h>
#include <PubSubClient.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "ssuclock";
const char* password = "";

// Add your MQTT Broker IP address, example:
// const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "130.157.111.115";

// Setup button pin
const int buttonPin1 = 1;
const int buttonPin2 = 2; // Change this to the GPIO pin where your button is connected
const int buttonPin3 = 3;
const int buttonPin4 = 4;

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int b1 = 0;
int lb1 = 0;
int b2 = 0;
int lb2 = 0;
int b3 = 0;
int lb3 = 0;
int b4 = 0;
int lb4 = 0;

void setup_wifi();

void setup() {
  Serial.begin(115200);

  // Set up the button pin as input
pinMode(buttonPin1, INPUT_PULLUP);
pinMode(buttonPin2, INPUT_PULLUP);
pinMode(buttonPin3, INPUT_PULLUP);
pinMode(buttonPin4, INPUT_PULLUP);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  // This is where you can handle incoming messages if needed.
  // For now, this is left empty.
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe to topics if needed
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read the button state
  b1 = digitalRead(buttonPin1);
  b2 = digitalRead(buttonPin2);
  b3 = digitalRead(buttonPin3);
  b4 = digitalRead(buttonPin4);

  // Check if the button has been pressed
  if (b1 == LOW && lb1 == HIGH) {
    // Button was just pressed
    Serial.println("b1 pressed!");

    // Publish a message to the MQTT broker when the button is pressed
    client.publish("esp32/button", "b1 pressed");

    // Debounce the button (delay to avoid multiple reads)
    delay(500);
  }
  if (b2 == LOW && lb2 == HIGH) {
    // Button was just pressed
    Serial.println("b2 pressed!");

    // Publish a message to the MQTT broker when the button is pressed
    client.publish("esp32/button", "b2 pressed");

    // Debounce the button (delay to avoid multiple reads)
    delay(500);
  }
  if (b3 == LOW && lb3 == HIGH) {
    // Button was just pressed
    Serial.println("b3 pressed!");

    // Publish a message to the MQTT broker when the button is pressed
    client.publish("esp32/button", "b3 pressed");

    // Debounce the button (delay to avoid multiple reads)
    delay(500);
  }
  if (b4 == LOW && lb4 == HIGH) {
    // Button was just pressed
    Serial.println("b4 pressed!");

    // Publish a message to the MQTT broker when the button is pressed
    client.publish("esp32/button", "b4 pressed");

    // Debounce the button (delay to avoid multiple reads)
    delay(500);
  }

  lb1 = b1;
  lb2 = b2;
  lb3 = b3;
  lb4 = b4;
}
