#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <saveMem.h>
#include <scale.h>


JsonDocument getTypeOfAirplane();
extern int selectedtypeOfAirplane;
extern float distance[];
boolean setScaleType(int id, JsonDocument jsono);
JsonDocument getScaleType();