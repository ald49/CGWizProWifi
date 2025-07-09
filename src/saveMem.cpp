#include <saveMem.h>

String STATION_SSID;
String STATION_PASSWORD;

// to store Preferences
Preferences preferences;

//  Prototypes
void readDataWifi();
void saveDataWifi();

void initpreferences()
{
    preferences.begin("Config", false);
    readDataWifi();
}

void readDataWifi()
{
    STATION_SSID = preferences.getString("STATION_SSID");
    STATION_PASSWORD = preferences.getString("STATION_PASW");
}

void saveDataWifi()
{
    preferences.putString("STATION_SSID", STATION_SSID);
    preferences.putString("STATION_PASW", STATION_PASSWORD);
}

void saveDataScale()
{
    int lcc = NumberOfLoadcells;
    for (int i = 0; i < lcc; i++)
    {
        String ps = "LCellcal" + String(i);
        preferences.putFloat(ps.c_str(), LoadCellcalibrationValue[i]);
    }
}

void readDataScale()
{
     int lcc = NumberOfLoadcells;
     for (int i = 0; i < lcc; i++)
    {
        String ps = "LCellcal" + String(i);
        LoadCellcalibrationValue[i] = preferences.getFloat(ps.c_str(),100);
    }
}

void saveDistanceScale()
{

    preferences.putFloat("NrLC", NumberOfLoadcells);
preferences.putFloat("selectedtAirp", selectedtypeOfAirplane);
    
    int lcc = 3;
    for (int i = 0; i < lcc; i++)
    {
        String ps = "Distance" + String(i);
        preferences.putFloat(ps.c_str(), distance[i]);
    }
}

void readDistanceScale()
{
    NumberOfLoadcells = preferences.getFloat("NrLC",3);
    selectedtypeOfAirplane = preferences.getFloat("selectedtAirp",0);

     int lcc = 3;
     for (int i = 0; i < lcc; i++)
    {
        String ps = "Distance" + String(i);
        distance[i] = preferences.getFloat(ps.c_str(),0);
    }
}
