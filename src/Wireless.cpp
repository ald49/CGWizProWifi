#include <Wireless.h>

JsonDocument WifiAvaliable;

//  Prototypes
void receivedCallback(const uint32_t &from, const String &msg);
void newConnectionCallback(uint32_t nodeId);
void changedConnectionCallback();
void nodeTimeAdjustedCallback(int32_t offset);
void onNodeDelayReceived(uint32_t nodeId, int32_t delay);
IPAddress getlocalIP();


void setupWireless()
{
  WiFi.setHostname("cgwizpro");
  WiFi.mode(WIFI_AP_STA);          // Set the WiFi module to Access Point mode
}

void createsoftAP()
{
  const char *ssid = "CGWiz";            // Your desired SSID
  const char *password = "testpassword"; // Your desired password (minimum 8 characters for WPA2)
  IPAddress local_ip(1, 1, 1, 1);
  IPAddress gateway(1, 1, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  
  WiFi.softAP(ssid, password); // Start the SoftAP with the defined SSID and password

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println(WiFi.getHostname());
}

bool testWifi(String STATION_SSID, String STATION_PASSWORD)
{
  //WiFi.disconnect();
  //WiFi.mode(WIFI_STA);

  WiFi.begin(STATION_SSID, STATION_PASSWORD);

  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while (c < 10)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println(WiFi.localIP());
      Serial.println(WiFi.status());
      delay(100);
      return true;
    }
    delay(500);
    Serial.println("*");
    c++;
  }
  Serial.println("Connect timed out, opening AP");
  //WiFi.disconnect();
  //delay(500);
  return false;
}
