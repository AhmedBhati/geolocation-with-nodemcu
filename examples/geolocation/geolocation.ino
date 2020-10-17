#include <geoloc.h>
const char* ssid = "thisone1";
const char* password = "12345678";
geoloc coords = geoloc();
void setup()
{
  Serial.begin(9600);
  coords.begin(ssid,password);
  String myip=coords.publicIP();
  Serial.println(myip);
}

void loop()
{
  String k=coords.geocordinates();
  Serial.println(k);
  delay(10000);
}
