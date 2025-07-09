#pragma once
#include <Arduino.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include <WebHelper.h>
#include <Command.h>
#include <Arduino.h>
#include <model.h>
#include <Wireless.h>
#include <scale.h>
#include <scale_model.h>

void InitWeb();