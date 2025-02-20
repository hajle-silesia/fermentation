#include "Temperature.h"
#include "IotClient.h"


DeviceManager deviceManager;
IotClient iotClient("hajle-silesia.online", 1883);

void setup() {
  Serial.begin(9600);

  deviceManager.begin();
  iotClient.begin();
}

void loop()
{
  if (!iotClient.connected()) {
    iotClient.reconnect();
  }
  iotClient.loop();

  deviceManager.processTemperatures();

  for (uint8_t i = 0; i < deviceManager.deviceCount; i++) {
    Serial.println("Device:");
    Serial.print("address: ");
    Serial.println(deviceManager.devices[i].address);
    Serial.print("temperature: ");
    Serial.println(deviceManager.devices[i].temperature);

    iotClient.publish(
      "temperature/" + deviceManager.devices[i].address,
      deviceManager.devices[i].temperature
    );
  }
}
