#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

void addCommand(JsonDocument doc);
JsonDocument getCommand(JsonDocument doc);
void deleteCommand(int id);
