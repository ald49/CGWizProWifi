#pragma once
#include <Arduino.h>
#include <HX711_ADC.h>
#include <ArduinoJson.h>
#include <msg.h>
#include <saveMem.h>
#include <Command.h>


void update(JsonDocument jaondata);
boolean setscaletar();
boolean setscaletar(int id);
boolean setCalibrationscalet(int id, JsonDocument jsono);
extern float LoadValue[];
extern float LoadCellcalibrationValue[];
extern long long int  LoadCellId[];
extern int NumberOfLoadcells;
float CalcCG();
extern JsonDocument docmsg;
JsonDocument getscaledata();
