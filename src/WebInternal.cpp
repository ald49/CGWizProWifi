#include <WebInternal.h>

AsyncWebServer internalServer(5000);
AsyncCorsMiddleware corsInternalCommunicationApi;

//  Prototypes
void notFoundinternalCommunicationApi(AsyncWebServerRequest *request);

// all api for internal Communication
void internalCommunicationApi();

void setupinternalCommunicationApi()
{
  internalServer.onNotFound(notFoundinternalCommunicationApi);
  corsInternalCommunicationApi.setOrigin("*");
  corsInternalCommunicationApi.setMethods("POST, GET,PATCH, OPTIONS, DELETE");
  corsInternalCommunicationApi.setHeaders("X-Custom-Header");
  corsInternalCommunicationApi.setAllowCredentials(false);
  corsInternalCommunicationApi.setMaxAge(600);
  internalServer.addMiddleware(&corsInternalCommunicationApi);
  internalCommunicationApi();
  internalServer.begin();
}

void notFoundinternalCommunicationApi(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
  Serial.println("no");
  Serial.println(request->url());
}

void internalCommunicationApi()
{
  internalServer.on(
      "/putdata",
      HTTP_PUT,
      [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        String json = ((char *)data);
        Serial.println(json);
        // JsonDocument doc;
        // DeserializationError error = deserializeJson(doc, json);
        // addModel(doc);

        // AsyncWebServerResponse *response = request->beginResponse(200, "application/json");
        request->send(200);
      });

  internalServer.on(
      "/getcommand",
      HTTP_POST,
      [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        String json = ((char *)data);
        Serial.println(json);

        JsonDocument doc;
        doc = convertToJsonObj(json);
        doc = getCommand(doc);
        String returnJson;
        serializeJson(doc, returnJson);
        deleteCommand(doc["id"]);
        
        AsyncWebServerResponse *response = request->beginResponse(200, "application/json", returnJson);
        request->send(response);
      }
    );

  internalServer.on(
      "/putmsg",
      HTTP_PUT,
      [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        String json = ((char *)data);
        Serial.println(json);
        JsonDocument doc;
        doc = convertToJsonObj(json);
        // DeserializationError error = deserializeJson(doc, json);
        //  addModel(doc);
        addMassage(String(doc["msg"]));
        // AsyncWebServerResponse *response = request->beginResponse(200, "application/json");
        request->send(200);
      });
}