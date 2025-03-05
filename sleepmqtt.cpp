#include <WiFi.h>
#include <PubSubClient.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "ssuclock";
const char* password = "";

// Add your MQTT Broker IP address, example:
// const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "130.157.110.196";

int TIME_TO_SLEEP = 30;                        // Time ESP32 will go to sleep (in seconds)
unsigned long long uS_TO_S_FACTOR = 1000000;  // Conversion factor for microseconds to seconds
RTC_DATA_ATTR int bootCount = 0;    

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi();
void reconnect();

          // Number of reboots
void setup() {
  /****  Do your stuff here! ****/
  Serial.begin(115200);                                 // Start serial communication at 115200 baud rate
  ++bootCount;                                // Add 1 to the current value of bootCount
  Serial.println("Boot number: " + String(bootCount));  // print the value of bootCount on the serial monitor
  Serial.println("Going to sleep now");                 // Print when the ESP is about to go into deep sleep mode
  /* Now we wrap up for Deep Sleep - I hope you did everything you needed to... */
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);  // Set up timer as the wake up source and set sleep duration to 5 seconds
  esp_deep_sleep_start();   
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

      // Button was just pressed
    Serial.println("mqtt!");

    // Publish a message to the MQTT broker when the button is pressed
    client.publish("esp32/button", "sleep mode");
                                // Start the deep sleep mode
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
  // This is not going to be called
  Serial.println("somethin smells");
  delay(500);
}
