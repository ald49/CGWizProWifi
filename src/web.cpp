#include <Web.h>

AsyncWebServer server(80);
AsyncCorsMiddleware cors;

//  Prototypes
void notFound(AsyncWebServerRequest *request);

void InitWsWeb();
// all api for model
void GetModel_api();

void InitWeb()
{
  InitWsWeb();
  server.onNotFound(notFound);
  cors.setOrigin("*");
  cors.setMethods("POST, GET,PATCH, OPTIONS, DELETE");
  cors.setHeaders("X-Custom-Header");
  cors.setAllowCredentials(false);
  cors.setMaxAge(600);
  server.addMiddleware(&cors);
  server.begin();
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
  Serial.println("no");
  Serial.println(request->url());
}

void InitWsWeb()
{
  GetModel_api();
}

void GetModel_api()
{
  server.on("/getmodels", HTTP_GET, [](AsyncWebServerRequest *request)
            {    
    JsonDocument data;
    //data = getModels();
    String json = "okay";
    Serial.println("yes");
    //serializeJson(data, json);
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
    request->send(response); });

  server.on("/getmodel", HTTP_GET, [](AsyncWebServerRequest *request)
            {   
    int urlParm = getUrlVarable(request->url()).toInt();
    JsonDocument data;
    //data = getModel(urlParm);
    String json;
    serializeJson(data, json);
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
    request->send(response); });

  server.on(
      "/addmodel",
      HTTP_POST,
      [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        String json = ((char *)data);
        Serial.println(json);
        // JsonDocument doc;
        // DeserializationError error = deserializeJson(doc, json);
        // addModel(doc);

        AsyncWebServerResponse *response = request->beginResponse(200, "application/json");
        request->send(response);
      });

  server.on(
      "/updatemodel",
      HTTP_PATCH,
      [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        String json = ((char *)data);
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, json);
        // updateModel(doc);
        request->send(200);
      });

  server.on("/deletemodel", HTTP_DELETE, [](AsyncWebServerRequest *request)
            {   
    int urlParm = getUrlVarable(request->url()).toInt();
    //deleteModel(urlParm);
    request->send(200); });
}

void GetScale_api()
{
  server.on("/setscaletar", HTTP_POST, [](AsyncWebServerRequest *request)
            {    
    //setscaletar();
    request->send(200); });

  server.on("/setscalecelltar", HTTP_POST, [](AsyncWebServerRequest *request)
            {    
    int urlParm = getUrlVarable(request->url()).toInt();
    //setscaletar(urlParm);
    request->send(200); });

  server.on(
      "/setcalibrationscalet",
      HTTP_POST,
      [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        int urlParm = getUrlVarable(request->url()).toInt();
        String json = ((char *)data);
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, json);
        // setCalibrationscalet(urlParm, doc);
        request->send(200);
      });

  server.on("/getscalevalues", HTTP_GET, [](AsyncWebServerRequest *request)
            {    
    JsonDocument data;
    //data = getscaledata();
    String json;
    serializeJson(data, json);
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
    request->send(response); });
}
