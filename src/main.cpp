#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>

#define wifi_ssid "Wifi"
#define wifi_password "Wifi passwd"

#define mqtt_server "ServerIP"
#define mqtt_user "User"
#define mqtt_password "passwd"

#define alert_topic "bouton/alert"

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("error, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}
void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to ");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  client.setServer(mqtt_server, 1883);
  reconnect();
  client.publish(alert_topic, "ON");
  delay(200);
  client.publish(alert_topic, "OFF");
  Serial.print("MQTT msg send");
  delay(100); 
  ESP.deepSleep(0); 
}
void loop() {}