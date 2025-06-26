#include <tcpserver.h>

const char *ssid = "ESP32-AP";
const uint16_t portNumber = 50000;
WiFiServer server(portNumber);
WiFiClient client;
WiFiClient lc0;
WiFiClient lc1;
WiFiClient lc2;
bool connected = false;

WiFiClient Clients[] = {lc0,lc1,lc2} ;

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

void updateTcpServer()
{
    client.setTimeout(100);
    client.setConnectionTimeout(100);
    //Serial.println(client.connected());
    if (!connected)
    {
        delay(1000);
        client = server.accept();

        if (client)
        {
            Serial.println("Got a client !");
            if (client.connected())
            {
                Serial.println("and it's connected!");
                Clients[0]=client;
                connected = true;
            }
            else
            {
                Serial.println("but it's not connected!");
                client.stop();
            }
        }
    }
    else
    {

        if (client.connected())
        {
            while (client.available())
                Serial.write(client.read());
        }
        else
        {
            Serial.println("Client is gone");
            client.stop();
            connected = false;
        }
        int test = client.write(1);

        if (test == 0)
        {
            client.stop();
        }
    }
}