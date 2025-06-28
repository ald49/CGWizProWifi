#include <Wireless.h>

JsonDocument WifiAvaliable;

//  Prototypes
void receivedCallback(const uint32_t &from, const String &msg);
void newConnectionCallback(uint32_t nodeId);
void changedConnectionCallback();
void nodeTimeAdjustedCallback(int32_t offset);
void onNodeDelayReceived(uint32_t nodeId, int32_t delay);
IPAddress getlocalIP();


void createsoftAP()
{
  const char *ssid = "CGWiz";            // Your desired SSID
  const char *password = "testpassword"; // Your desired password (minimum 8 characters for WPA2)
  IPAddress local_ip(1, 1, 1, 1);
  IPAddress gateway(1, 1, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  WiFi.mode(WIFI_AP);          // Set the WiFi module to Access Point mode
  WiFi.softAP(ssid, password); // Start the SoftAP with the defined SSID and password

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
}
