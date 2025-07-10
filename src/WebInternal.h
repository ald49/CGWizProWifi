#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include <WebHelper.h>
#include <msg.h>
#include <Command.h>
#include <scale.h>
#include "SPIFFS.h"

void setupinternalCommunicationApi();