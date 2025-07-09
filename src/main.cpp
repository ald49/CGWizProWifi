#include <Arduino.h>
#include <Wireless.h>
#include <StatusLed.h>
#include <Web.h>
#include <WebInternal.h>
#include <ExternalOta.h>

void setup()
{
  Serial.begin(115200);
  delay(2000);
  // Init led and turn it on.
  InitLed();
  onLedRed();
  // init preferences and read wifi
  initpreferences();
  readDataWifi();
  readDistanceScale();

  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  // Init model database.
  InitModelDB();
  Serial.println("test");
  setupWireless();
  testWifi("Iotfisk", "jessie4at");
  String a = getGitHubVersion();
  //OTAUpdate();
  createsoftAP();
  InitWeb();
  Serial.println("test2");
  setupinternalCommunicationApi();
  // turn led off.
  offLed();
}

void loop()
{
  // Serial.println("test2");
}
