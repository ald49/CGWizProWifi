#include <Web.h>

AsyncWebServer server(80);
AsyncCorsMiddleware cors;

//  Prototypes
void notFound(AsyncWebServerRequest *request);

void InitStaticWeb();
void InitWsWeb();
// all api for model
void GetModel_api();
// All api for wifi
void GetWifi_api();
// all api for scale
void GetScale_api();
// all api for scale
void GetScaleModel_api();
// all api for msg
void GetMsgs_api();

void InitWeb()
{

  InitStaticWeb();
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
}

void InitStaticWeb()
{
  server.serveStatic("/", SPIFFS, "/");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->redirect("/index.html"); });
}

void InitWsWeb()
{
  GetModel_api();
  GetWifi_api();
  GetScale_api();
  GetScaleModel_api();
  GetMsgs_api();
}

void GetScale_api()
{
  server.on("/setscaletar", HTTP_POST, [](AsyncWebServerRequest *request)
            {    

    setscaletar();
    request->send(200); });

  server.on("/setscalecelltar", HTTP_POST, [](AsyncWebServerRequest *request)
            {    
    int urlParm = getUrlVarable(request->url()).toInt();
    setscaletar(urlParm);
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
        setCalibrationscalet(urlParm, doc);
        request->send(200);
      });

  server.on("/getscalevalues", HTTP_GET, [](AsyncWebServerRequest *request)
            {    
    JsonDocument data;
    data = getscaledata();
    String json;
    serializeJson(data, json);
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
    request->send(response); });
}

void GetModel_api()
{
  server.on("/getmodels", HTTP_GET, [](AsyncWebServerRequest *request)
            {    
    JsonDocument data;
    data = getModels();
    String json;
    serializeJson(data, json);
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
    request->send(response); });

  server.on("/getmodel", HTTP_GET, [](AsyncWebServerRequest *request)
            {   
    int urlParm = getUrlVarable(request->url()).toInt();
    JsonDocument data;
    data = getModel(urlParm);
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
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, json);
        addModel(doc);
        request->send(200);
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
        updateModel(doc);
        request->send(200);
      });

  server.on("/deletemodel", HTTP_DELETE, [](AsyncWebServerRequest *request)
            {   
    int urlParm = getUrlVarable(request->url()).toInt();
    deleteModel(urlParm);
    request->send(200); });
}

void GetWifi_api()
{
  server.on("/getwifis", HTTP_GET, [](AsyncWebServerRequest *request)
            {    
    JsonDocument data;
    data = getWifi();
    String json;
    serializeJson(data, json);
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
    request->send(response); });

  server.on("/refreshWifi", HTTP_GET, [](AsyncWebServerRequest *request)
            {    
    getrefreshWifi();
    request->send(200); });

  server.on(
      "/setwifi",
      HTTP_POST,
      [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        String json = ((char *)data);
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, json);
        bool retunval = setWifi(doc);
        json = '{\"message\":\"' + retunval + '\"}';
        request->send(200, "application/json", json);
      });
}

void GetMsgs_api()
{
  server.on("/getmsgs", HTTP_GET, [](AsyncWebServerRequest *request)
            {  
    String json;
    serializeJson(docmsg, json);
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
    request->send(response); });

  server.on("/deletemsg", HTTP_DELETE, [](AsyncWebServerRequest *request)
            {   
    int urlParm = getUrlVarable(request->url()).toInt();
    deleteMsg(urlParm);
    request->send(200); });
}

void GetScaleModel_api()
{
  server.on("/gettypeofairplane", HTTP_GET, [](AsyncWebServerRequest *request)
            {    
    JsonDocument data;
    data = getTypeOfAirplane();
    String json;
    serializeJson(data, json);
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
    request->send(response); });

  server.on(
      "/setscaletype",
      HTTP_POST,
      [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        int urlParm = getUrlVarable(request->url()).toInt();
        String json = ((char *)data);
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, json);
        setScaleType(urlParm, doc);
        request->send(200);
      });

  server.on("/getscaletype", HTTP_GET, [](AsyncWebServerRequest *request)
            {    
    JsonDocument data;
    data = getScaleType();
    String json;
    serializeJson(data, json);
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
    request->send(response); });
}
