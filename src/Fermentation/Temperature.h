#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 3
#define TEMPERATURE_RESOLUTION 12
#define MAX_DEVICES 10

struct DeviceTemperature {
  String address;
  String temperature;
};


class DeviceManager {
protected:
  String getAddress(DeviceAddress);
  String getTemperature(DeviceAddress);
public:
  DeviceTemperature devices[MAX_DEVICES];
  uint8_t deviceCount = 0;
  void begin();
  void processTemperatures();
};

#endif // DEVICE_MANAGER_H
