#include <Arduino.h>
#include <Wireless.h>
#include <StatusLed.h>
#include <Web.h>
#include <WebInternal.h>

void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.println("test");
  setupWireless();
  
  testWifi("Iotfisk", "jessie4at");
  createsoftAP();
  InitWeb();
  Serial.println("test2");
  setupinternalCommunicationApi();

}

void loop()
{
//Serial.println("test2");
}
