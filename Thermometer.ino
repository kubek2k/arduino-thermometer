
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <time.h>

// PIN number 5
DHT dht(DHT_PORT, DHT11);
WiFiClient wifiClient;
PubSubClient pubsub(MQTT_DOMAIN, MQTT_PORT, wifiClient);
String payload;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(STASSID);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for time..");
  while (!time(nullptr)) {
      Serial.print(".");
      delay(1000);
  }
}

void sendToMqtt(String message) {
    while (!pubsub.connected()) {
        if (pubsub.connect(LOCATION, MQTT_USERNAME, MQTT_PASSWORD)) {
            Serial.println("Connected to MQTT");
        } else {
            Serial.print("Failed to connect to MQTT: ");
            Serial.print(pubsub.state());
            Serial.println(". Reconnecting in 5s..");
            delay(5000);
        }
    }
    pubsub.publish("temperatures", message.c_str());
    Serial.print("Published: ");
    Serial.println(message);
    pubsub.disconnect();
}

time_t getNow() {
    return time(nullptr);
}

void loop() {
    Serial.println("Looping");

    float temperature = NAN;
    while (isnan(temperature)) {
        delay(READ_DELAY);
        temperature = dht.readTemperature();
    }
    Serial.print(temperature);
    Serial.print("C ");
    float humidity = dht.readHumidity();
    Serial.print(humidity);
    Serial.println("% ");
    
    payload.reserve(100);
    payload = "";
    payload += LOCATION;
    payload += getNow();
    payload += ";h=";
    payload += humidity;
    payload += ";t=";
    payload += temperature;
    
    sendToMqtt(payload);

    delay(READ_DELAY);
}
