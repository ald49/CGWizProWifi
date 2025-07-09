#pragma once
#include <Arduino.h>
#include "SPIFFS.h"
#include <ArduinoJson.h>


void InitModelDB();

JsonDocument getModels();
JsonObject getModel(int id);
void addModel(JsonDocument jsono);
void updateModel(JsonDocument jsono);
void deleteModel(int id);