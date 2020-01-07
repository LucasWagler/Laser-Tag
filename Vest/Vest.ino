//COMMENT OUT BEFORE DELIVERY
#define DEBUG
//DEFINE WHICH TEAM & # BEFORE PROGRAMMING ARDUINO
#define RED1

#include <Adafruit_NeoPixel.h>
#include <WiFiNINA.h>

#define LEDSTRIP 6
#define NUMLED 150

#ifdef BLUE1
char ssid[] = "Blue1"; //Blue1 vest SSID
char pw[] = "BlueTeam1"; //Blue1 vest PW
IPAddress serverIP(192,168,1,1); 
WiFiServer server(80);
#endif
#ifdef BLUE2
char ssid[] = "Blue2"; //Blue2 vest SSID
char pw[] = "BlueTeam2"; //Blue2 vest PW
IPAddress serverIP(192,168,2,1); 
WiFiServer server(80);
#endif
#ifdef RED1
char ssid[] = "Red1"; //Red1 vest SSID
char pw[] = "RedTeam1"; //Red1 vest PW
IPAddress serverIP(192,168,3,1); 
WiFiServer server(80);
#endif
#ifdef RED2
char ssid[] = "Red2"; //Red2 vest SSID
char pw[] = "RedTeam2"; //Red2 vest PW
IPAddress serverIP(192,168,4,1); 
WiFiServer server(80);
#endif

int status = WL_IDLE_STATUS;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMLED, LEDSTRIP, NEO_GRB + NEO_KHZ800);

#ifdef DEBUG
void printWiFiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.println("SSID: " + String(WiFi.SSID()));

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: " + String(ip));
}
#endif

void setup() 
{
  //Initialize LED strip
  pixels.begin();
  
  #ifdef DEBUG
  Serial.begin(9600);
  while(!Serial){};
  Serial.println("Access Point Testing");
  if(WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication Failed");
  }
  #endif
  
  WiFi.config(serverIP);

  #ifdef DEBUG
  Serial.println("Access Point is: " + String(ssid));
  #endif
  status = WiFi.beginAP(ssid, pw);
  if (status != WL_AP_LISTENING) {
    #ifdef DEBUG
    Serial.println("Creating access point failed");
    #endif
    // don't continue
    while (true);
  }

  // start the web server on port 80
  server.begin();
  
  #ifdef DEBUG
  printWiFiStatus();
  #endif
}

void loop()
{
  if (status != WiFi.status()) 
  {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) 
    {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } 
    else 
    {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }
  // put your main code here, to run repeatedly:
//  WiFiClient client = server.available();
//  Serial.println(client.status());
//  if(client)
//  {
//    if(client.connected())
//    {
//      Serial.println("Client Found");
//      server.print('v');
//    }
//  }
//  client.stop();
  server.print('h');
  delay(20000);

  //LED Strip handler
  for(int i=0;i<NUMLED;i++){
      pixels.setPixelColor(i, pixels.Color(100,0,0));
      pixels.show();
      //delay(delayval);
  }
}
