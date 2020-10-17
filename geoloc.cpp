#include "ESP8266WiFi.h"
#include "string.h"
#include "geoloc.h"
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino.h>
ESP8266WiFiMulti WiFiMulti;
geoloc::geoloc(void)
{
}
void geoloc::begin(const char* ssid,const char* password)
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
	Serial.println(WiFi.status());
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid,password);
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

String geoloc::publicIP(void)
{
  WiFiClient client; 
  if (client.connect("api.ipify.org", 80)) 
    client.println("GET / HTTP/1.0\r\nHost: api.ipify.org\r\n\r\n");
  else 
    Serial.println("Connection to ipify.org failed");
  String line;
  delay(500);
  while(client.available())
  {
    line = client.readStringUntil('\n');
  }
  return line;
}

String geoloc::geocordinates(void)
{
  String k=publicIP();
  String payload;
  String geolink="http://ip-api.com/json/"+k;
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, geolink))
      {
         Serial.print("[HTTP] GET...\n");
               // start connection and send HTTP header
         int httpCode = http.GET();

              // httpCode will be negative on error
         if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
        
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        // file found at server
        
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          
         payload = http.getString();
         //Serial.println(payload);

        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } 
	
	else {
      Serial.printf("[HTTP] Unable to connect\n");
    }

}
return payload;
}

