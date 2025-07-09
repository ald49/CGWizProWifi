#include <ExternalOta.h>

void OTAUpdate(String firmwareUrl);

String getGitHubVersion()
{
     if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient httpclient;
        String serverPath = "https://api.github.com/repos/ald49/CGWizFirmeware/releases";
        httpclient.begin(serverPath.c_str());
        //JsonDocument doc;
        //doc["Unit"] = ESP.getEfuseMac();
        //String json;
        //serializeJson(doc, json);

        httpclient.addHeader("Content-Type", "application/json");
        // Send HTTP GET request
        int httpResponseCode = httpclient.GET();

        if (httpResponseCode > 0)
        {
            // Serial.print("HTTP Response code: ");
            // Serial.println(httpResponseCode);
            String payload = httpclient.getString();
            if (payload != "null")
            {
                //Serial.println(payload);
                JsonDocument localdoc;
                localdoc = convertToJsonObj(payload);
                String githubversiom =(localdoc[0]["tag_name"]);
                githubversiom = githubversiom.substring(1,githubversiom.length());
                Serial.println(githubversiom);
                if(float(version) < githubversiom.toFloat())
                {
                    String githubversiomurl =(localdoc[0]["assets"][0]["browser_download_url"]);
                    Serial.println(githubversiomurl);
                    OTAUpdate(githubversiomurl);
                }

            }
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        //  Free resources
        httpclient.end();
    }
    return "stest";
}


void OTAUpdate(String firmwareUrl)
{

    Serial.println("perform Start");

    // Create an HTTP client object
    HTTPClient http;
    http.setUserAgent("CGWizPro");
    http.setRedirectLimit(1);
    http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
    const char *headers[] = {"Location"};
    Serial.println("Start request bin");
    //const char *firmwareUrl = "https://github.com/ald49/CGWizFirmeware/releases/download/V0.1/firmware.bin";
    // Begin the HTTP request
    http.begin(firmwareUrl);
    //http.collectHeaders(headers, 1);
    //String redir = http.header("Location");
    //http.end();

    //Serial.println(redir);
    //http.begin(redir);

    //  http.setTimeout(1000*60*20);

    // Start the download and check for errors
    int httpCode = http.GET();
    Serial.println("End request ");

    // drawOTAText("OTA : Request binary : request completed");

    Serial.print("Response request : ");
    Serial.println(httpCode);

        if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            // Process the response and start the update
            int contentLength = http.getSize();
            bool isValidContent = contentLength > 0;

            if (isValidContent) {
               // Start the update process
               Update.begin(contentLength, U_FLASH); // U_FLASH for updating flash
               // Stream the data into the update process
               WiFiClient * stream = http.getStreamPtr();
               size_t written = Update.writeStream(*stream);
               if (written == contentLength){
                   if(Update.end()){
                       // Successful update, reboot the device
                       Serial.println("Update successful. Rebooting...");
                       ESP.restart();
                   } else {
                       Serial.println("Update failed: " + String(Update.getError()));
                   }
               } else {
                   Serial.println("Error streaming data");
               }
            } else {
               Serial.println("Error: Invalid content length");
            }
         } else {
              Serial.println("Error on HTTP request: " + String(httpCode));
         }
    } else {
        Serial.println("Error on HTTP connection: " + String(http.errorToString(httpCode).c_str()));
    }

}
