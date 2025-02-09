#include "Temperature.h"


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void DeviceManager::begin() {
  sensors.begin();

  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  Serial.print("Parasite power is ");
  if (sensors.isParasitePowerMode()) Serial.print("on");
  else Serial.print("off");
  Serial.println(".");
}

void DeviceManager::processTemperatures() {
  Serial.println("Discovering devices...");
  oneWire.reset_search();
  DeviceAddress thermometerAddress;

  deviceCount = 0;

  while (oneWire.search(thermometerAddress)) {
    if (sensors.setResolution(thermometerAddress, TEMPERATURE_RESOLUTION, true)) {
      if (sensors.requestTemperaturesByAddress(thermometerAddress).result) {
        if (deviceCount < MAX_DEVICES) {
          devices[deviceCount].address = getAddress(thermometerAddress);
          devices[deviceCount].temperature = getTemperature(thermometerAddress);
          deviceCount++;
        }
      }
    }
  }
}

String DeviceManager::getAddress(DeviceAddress deviceAddress) {
  char address[17] = "\0";

  for (uint8_t i = 0; i < 8; i++) {
    char byteStr[3];
    sprintf(byteStr, "%02X", deviceAddress[i]);
    strcat(address, byteStr);
  }
  return address;
}

String DeviceManager::getTemperature(DeviceAddress deviceAddress) {
  char temperature[8] = "\0";

  char floatStr[8];
  strcat (temperature, dtostrf(sensors.getTempC(deviceAddress), 0, 2, floatStr));

  return temperature;
}
