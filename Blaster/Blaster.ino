#include <WiFiNINA.h>

#define IRLED 0
#define HITLED 0
#define BOARDLED LED_BUILTIN
#define HIT 'h'

char ssid[] = "Blue1";          //  your network SSID (name)
char pw[] = "BlueTeam1";        // your network password

IPAddress server(192,168,1,1);
int port = 80;

int status = WL_IDLE_STATUS;

WiFiClient client;

IPAddress ip;

void setup() 
{
  Serial.begin(9600);
  pinMode(BOARDLED, OUTPUT);
  digitalWrite(BOARDLED, LOW);

  //REMOVE AFTER DEBUGGING!!!
  while(!Serial);
  
  Serial.println("Attempting to connect to: " + String(ssid));

  status = WiFi.begin(ssid, pw);
  while( status != WL_CONNECTED) 
  {
    Serial.println("Couldn't get a wifi connection");
    delay(500);
     status = WiFi.begin(ssid, pw);
  }
  Serial.println("Connected to wifi");
  digitalWrite(BOARDLED, HIGH);
  ip = WiFi.localIP();
  Serial.println(ip);

  if(client.connect(server, port))
  {
    Serial.println("Connected to server");
  }
}

void loop() 
{
  //Timeout
  if(client.available())
  {
    char c = client.read();
    if(c == HIT)
    {
      Serial.println("HIT");
      for(int i = 0; i < 20; i++)
      {
        digitalWrite(BOARDLED, !digitalRead(BOARDLED));
        delay(500);
      }
    }
  }
  Serial.println("Doing other tasks");
}
