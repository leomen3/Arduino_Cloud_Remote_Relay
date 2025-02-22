// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "f9101639-2c88-40fd-b044-74978f68c2ab";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onHARPiSupplySWChange();
//void onS2RelayChange();
void onS3RelayChange();
//void onS5RelayChange();

CloudSwitch hA_RPi_Supply_SW;
CloudSwitch s3_Relay;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(hA_RPi_Supply_SW, READWRITE, ON_CHANGE, onHARPiSupplySWChange);
//  ArduinoCloud.addProperty(s2_Relay, READWRITE, ON_CHANGE, onS2RelayChange);
  ArduinoCloud.addProperty(s3_Relay, READWRITE, ON_CHANGE, onS3RelayChange);
//  ArduinoCloud.addProperty(s5_Relay, READWRITE, ON_CHANGE, onS5RelayChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
