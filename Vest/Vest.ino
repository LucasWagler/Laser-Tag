#include <WiFiNINA.h>

char ssid[] = "Blue2";
char pw[] = "BlueTeam";

IPAddress ip(192,168,1,1);
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.config(ip);
  WiFi.beginAP(ssid, pw);

  server.begin();
  Serial.println("IP Address: " + WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(client)
  {
    Serial.println("Client Found");
  }
}
