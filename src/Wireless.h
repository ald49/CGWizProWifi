#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

void setupWireless();
void createsoftAP();
bool testWifi(String STATION_SSID, String STATION_PASSWORD);
