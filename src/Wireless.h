#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <saveMem.h>

void setupWireless();
void createsoftAP();
bool testWifi(String STATION_SSID, String STATION_PASSWORD);
void ScanWifiNet();
void getrefreshWifi();
bool setWifi(JsonDocument doc);
void createsoftAP();
JsonDocument getWifi();
