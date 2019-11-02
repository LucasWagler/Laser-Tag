#include <WiFiNINA.h>

char ssid[] = "Blue1";
char pw[] = "BlueTeam1";

IPAddress ip(192,168,1,1);
WiFiServer server(80);
int status = WL_IDLE_STATUS;

void printWiFiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){};
  Serial.println("Access Point Testing");

  if(WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication Failed");
  }

  WiFi.config(ip);

  Serial.println("Access Point is: " + String(ssid));
  status = WiFi.beginAP(ssid, pw);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // start the web server on port 80
  server.begin();

  printWiFiStatus();
}

void loop()
{
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  Serial.println(client.status());
  if(client)
  {
    Serial.println("Client Found");
  }
}
