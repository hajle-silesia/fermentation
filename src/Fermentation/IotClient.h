#ifndef IOT_CLIENT_H
#define IOT_CLIENT_H

#include <Ethernet.h>
#include <SPI.h>
#include <PubSubClient.h>


class IotClient {
private:
  const char* server;
  uint16_t port;
public:
  IotClient(const char*, uint16_t);
  void begin();
  boolean connected();
  void reconnect();
  void loop();
  boolean publish(String, String);
};

#endif // IOT_CLIENT_H
