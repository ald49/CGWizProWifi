#pragma once
#include <Arduino.h>
#include <WiFi.h>

void initTcpServer();
void updateTcpServer();
void aliveCheckClient();
void newConnetionCheck();