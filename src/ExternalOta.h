#pragma once
#include <Arduino.h>
#include <HTTPClient.h>
#include <Update.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WebHelper.h>

#define version 0.13

String getGitHubVersion();