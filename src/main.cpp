#include <Arduino.h>
#include <netMesh.h>

// AsyncWebServer server(80);

void Connect_Loop(void *parameter)
{

  while (1)
  {

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void setup()
{
  Serial.begin(115200);

  setupNetMesh();
}

void loop()
{
  loopNetMesh();
}
