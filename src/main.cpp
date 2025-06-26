#include <Arduino.h>
#include <tcpserver.h>

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
  initTcpServer();

  xTaskCreatePinnedToCore(
      Connect_Loop,
      "Other connect task",
      4096,
      NULL,
      3,
      NULL,
      0);

  // Async webserver
  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send(200, "text/html", "<form>Text to Broadcast<br><input type='text' name='BROADCAST'><br><br><input type='submit' value='Submit'></form>");
  //   if (request->hasArg("BROADCAST")){
  //     String msg = request->arg("BROADCAST");
  //     mesh.sendBroadcast(msg);
  //   }
  // });
  // server.begin();
}

void loop()
{
  aliveCheckClient();
  newConnetionCheck();
  updateTcpServer();
}
