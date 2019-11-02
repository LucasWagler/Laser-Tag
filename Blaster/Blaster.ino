#include <WiFiNINA.h>

char ssid[] = "Blue1";          //  your network SSID (name)
char pw[] = "BlueTeam1";        // your network password

int port = 80;

int status = WL_IDLE_STATUS;
//char servername[]="google.com";  // remote server we will connect to

WiFiClient client;

IPAddress ip;

void setup() 
{
  Serial.begin(9600);
  delay(1000);
  Serial.print("Attempting to connect to: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pw);
  while( status != WL_CONNECTED) 
  {
    Serial.println("Couldn't get a wifi connection");
    delay(500);
     status = WiFi.begin(ssid, pw);
  }
  Serial.println("Connected to wifi");
  ip = WiFi.localIP();
  Serial.println(ip);
}

void loop() 
{

}
