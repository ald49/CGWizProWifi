#include <tcpserver.h>

const char *ssid = "ESP32-AP";
const uint16_t portNumber = 50000;
WiFiServer server(portNumber);
WiFiClient client;
WiFiClient lc0;
WiFiClient lc1;
WiFiClient lc2;
bool connected = false;
int clientid = 0;

WiFiClient Clients[] = {};

void initTcpServer()
{
    Serial.print("Setting AP (Access Point)…");
    WiFi.softAP(ssid);
    IPAddress IP = WiFi.softAPIP();
    Serial.print(" -> IP address: ");
    Serial.println(IP);
    server.begin();
    server.setTimeout(100);
}

void aliveCheckClient()
{
    for (int i = 0; i < clientid; i++)
    {
        int test = Clients[i].write(1);
        Serial.print(test);
        if (test == 0)
        {
            Clients[i].stop();
            Serial.print(" stop ");
        }
        if (!Clients[i].connected())
        {
            Serial.println("Client is gone");
            Clients[i].stop();
            clientid = clientid - 1;
        }
    }
    //Serial.print(clientid);
}

void newConnetionCheck()
{
    WiFiClient client_local;
    client_local.setTimeout(100);
    client_local.setConnectionTimeout(100);
    client_local = server.accept();

    if (client_local)
    {
        Serial.println("Got a client !");
        if (client_local.connected())
        {
            Serial.println("and it's connected!");
            Clients[clientid] = client_local;
            clientid = clientid + 1;
        }
        else
        {
            Serial.println("but it's not connected!");
            client_local.stop();
        }
    }
}

void updateTcpServer()
{
    for (int i = 0; i < clientid; i++)
    {
        if (Clients[i].available())
        {
            String data = Clients[i].readStringUntil('\n');
            Serial.println(data);
        }
    }

    // newConnetionCheck();
    //  client.setTimeout(100);
    //  client.setConnectionTimeout(100);
    //   Serial.println(client.connected());
    //  if (!connected)
    //  {
    //      delay(1000);
    //      client = server.accept();

    //   if (client)
    //  {
    //    Serial.println("Got a client !");
    //    if (client.connected())
    //    {
    //       Serial.println("and it's connected!");
    //       Clients[0] = client;
    //       connected = true;
    //   }
    //   else
    //   {
    //       Serial.println("but it's not connected!");
    //       client.stop();
    //   }
    // }
    // }
    // else
    // {
    // aliveCheckClient();
    //}
}