#include <scale_model.h>

String typeOfAirplane[3] = {
    "3 x Load cells Tricycle landing gear (or tricycle gear)",
    "3 x Load cells Taildragger (or conventional gear)",
    "Simple 2 Load Cell setup"};

float distance[3] = {0, 0, 0};

int selectedtypeOfAirplane = 0;

JsonDocument getTypeOfAirplane()
{
    JsonDocument doc;
    JsonArray models = doc["scaletypes"].to<JsonArray>();
    for (int i = 0; i <= sizeof(typeOfAirplane) / sizeof(typeOfAirplane[0]) - 1; i++)
    {
        Serial.println(i);
        JsonObject scalevalue = models.add<JsonObject>();
        scalevalue["id"] = i;
        scalevalue["typeOfAirplane"] = typeOfAirplane[i];
    }
    return doc;
}
boolean setScaleType(int id, JsonDocument jsono)
{

    JsonArray distancejson = jsono["distance"];
    selectedtypeOfAirplane = id;

    for (int i = 0; i < sizeof distance / sizeof distance[0]; i++)
    {   
        distance[i] = distancejson[i]["mm"];
    }
    switch (id)
    {
    case 0:
        NumberOfLoadcells = 3;
        break;
    case 1:
        NumberOfLoadcells = 3;
        break;
    case 2:
        NumberOfLoadcells = 2;
        break;
    }

    saveDistanceScale();
    esp_restart();
    return true;
}

JsonDocument getScaleType()
{
    JsonDocument doc;
    doc["selectedtypeOfAirplane"] = selectedtypeOfAirplane;

    JsonArray distancejson = doc["distance"].to<JsonArray>();
    for (int i = 0; i < sizeof distance / sizeof distance[0]; i++)
    {
        JsonObject value = distancejson.add<JsonObject>();
        if (i == 2)
        {
            if (selectedtypeOfAirplane != 2)
            {
                value["id"] = i;
                value["mm"] = distance[i];
            }
        }
        else
        {
            value["id"] = i;
            value["mm"] = distance[i];
        }
    }
    return doc;
}