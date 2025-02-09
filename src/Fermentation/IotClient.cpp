#include "IotClient.h"


EthernetClient ethClient;
PubSubClient client(ethClient);

IotClient::IotClient(const char* server, uint16_t port)
: server(server),
port(port)
{
}

void IotClient::begin() {
  byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

  client.setServer(server, port);

  if (Ethernet.begin(mac) == 0) {
     Serial.println("Failed to configure Ethernet using DHCP");
     if (Ethernet.hardwareStatus() == EthernetNoHardware) {
       Serial.println("Ethernet shield not found.");
       while (true) {
         delay(1); // do nothing, no point running without Ethernet hardware
       }
     }
     if (Ethernet.linkStatus() == LinkOFF) {
       Serial.println("Ethernet cable not connected.");
     }
   }
   else {
     Serial.print("DHCP assigned IP ");
     Serial.println(Ethernet.localIP());
   }  
}

boolean IotClient::connected() {
  return client.connected();
}

void IotClient::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(server);
    Serial.print(":");
    Serial.print(port);
    Serial.print("...");
    if (client.connect("fermentationController")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}

void IotClient::loop() {
  client.loop();
}

boolean IotClient::publish(String topic, String payload) {
  return client.publish(topic.c_str(), payload.c_str());
}
