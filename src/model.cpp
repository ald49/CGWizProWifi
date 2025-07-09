#include <model.h>

#define ModelDB "/model.json"
JsonDocument doc;

int ModelDBSize = 10;

//  Prototypes
void loadConfiguration();
void saveConfiguration();

void InitModelDB()
{
    loadConfiguration();
}

JsonDocument getModels()
{
    File file = SPIFFS.open(ModelDB);
    // Serial.println(file.available());
    DeserializationError error = deserializeJson(doc, file);
    return doc;
}

void loadConfiguration()
{
    SPIFFS.remove(ModelDB);
    // Open file for reading
    File file = SPIFFS.open(ModelDB);

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error)
    {
        Serial.println(F("Failed to read file, using default configuration"));
        // Open file for writing
        File file = SPIFFS.open(ModelDB, FILE_WRITE);
        if (!file)
        {
            Serial.println(F("Failed to create file"));
            return;
        }
        // Create empty file.
        JsonArray models = doc["models"].to<JsonArray>();
        for (int i = 0; i <= ModelDBSize; i++)
        {
            JsonObject model = models.add<JsonObject>();
            model["id"] = i;
            model["modelname"] = "";
            model["CG"] = 0;
            model["CGMin"] = 0;
            model["CGMax"] = 0;
            model["weight"] = 0;
        }
        // Serialize JSON to file
        if (serializeJson(doc, file) == 0)
        {
            Serial.println(F("Failed to write to file"));
        }
        file.flush();
    }
    file.close();
}

// Saves the configuration to a file
void saveConfiguration()
{
    // Delete existing file, otherwise the configuration is appended to the file
    SPIFFS.remove(ModelDB);

    // Open file for writing
    File file = SPIFFS.open(ModelDB, FILE_WRITE);
    if (!file)
    {
        Serial.println(F("Failed to create file"));
        return;
    }

    // Serialize JSON to file
    if (serializeJson(doc, file) == 0)
    {
        Serial.println(F("Failed to write to file"));
    }

    // Close the file
    file.close();
}

void addModel(JsonDocument jsono)
{
    JsonArray models = doc["models"];
    JsonObject d = models[models.size() - 1];
    int maxid = (d["id"].as<int>()) + 1;

    JsonObject model = models.add<JsonObject>();
    model["id"] = maxid;
    model["modelname"] = jsono["modelname"];
    model["CG"] = jsono["CG"];
    model["CGMin"] = jsono["CGMin"];
    model["CGMax"] = jsono["CGMax"];
    model["weight"] = jsono["weight"];
    saveConfiguration();
}

JsonObject getModel(int id)
{
    JsonArray models = doc["models"];
    JsonObject model;
    for (JsonArray::iterator it = models.begin(); it != models.end(); ++it)
    {
        if ((*it)["id"] == id)
        {

            model = (*it);
            break;
        }
    }
    return model;
}

void updateModel(JsonDocument jsono)
{
    JsonArray models = doc["models"];
    JsonObject model;
    for (JsonArray::iterator it = models.begin(); it != models.end(); ++it)
    {
        if ((*it)["id"] == jsono["id"])
        {
            model = (*it);
            break;
        }
    }
    model["modelname"] = jsono["modelname"];
    model["CG"] = jsono["CG"];
    model["CGMin"] = jsono["CGMin"];
    model["CGMax"] = jsono["CGMax"];
    model["weight"] = jsono["Weight"];
    saveConfiguration();
}

void deleteModel(int id)
{

    JsonArray models = doc["models"];

    for (JsonArray::iterator it = models.begin(); it != models.end(); ++it)
    {
        if ((*it)["id"] == id)
        {
            models.remove(it);
        }
    }
    saveConfiguration();
}
