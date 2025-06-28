#include <Arduino.h>
#include <Wireless.h>
#include <status_led.h>
#include <web.h>

void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.println("test");
  createsoftAP();
  InitWeb();
  Serial.println("test2");

}

void loop()
{
//Serial.println("test2");
}
