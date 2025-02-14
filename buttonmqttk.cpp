#include <WiFi.h>
#include <PubSubClient.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "";
const char* password = "";

// Add your MQTT Broker IP address, example:
// const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "192.168.50.35";

// Setup button pin
const int buttonPin = 2; // Change this to the GPIO pin where your button is connected

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int buttonState = 0;
int lastButtonState = 0;

void setup_wifi();

void setup() {
  Serial.begin(115200);

  // Set up the button pin as input
pinMode(buttonPin, INPUT_PULLUP);

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
  buttonState = digitalRead(buttonPin);

  // Check if the button has been pressed
  if (buttonState == LOW) {
    // Button was just pressed
    Serial.println("Button pressed!");

    // Publish a message to the MQTT broker when the button is pressed
    client.publish("esp32/button", "pressed");

    // Debounce the button (delay to avoid multiple reads)
    delay(500);
  }

  lastButtonState = buttonState;
}
