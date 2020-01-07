//COMMENT OUT BEFORE DELIVERY
#define DEBUG
//DEFINE WHICH TEAM & # BEFORE PROGRAMMING ARDUINO
#define RED1

#include <WiFiNINA.h>

//Trigger/Button Input
#define trigger A4

//IR Emitter
#define IRLED 0

//RGB LED
#define HitLedR A1 //Pin A1 on Arduino
#define HitLedG A2 //Pin A2 on Arduino
#define HitLedB A3 //Pin A3 on Arduino

//Board LED
#define BOARDLED LED_BUILTIN

//Commands
#define HIT 'h'

#ifdef BLUE1
char ssid[] = "Blue1"; //Blue1 vest SSID
char pw[] = "BlueTeam1"; //Blue1 vest PW
IPAddress server(192,168,1,1); 
#endif
#ifdef BLUE2
char ssid[] = "Blue2"; //Blue2 vest SSID
char pw[] = "BlueTeam2"; //Blue2 vest PW
IPAddress server(192,168,2,1); 
#endif
#ifdef RED1
char ssid[] = "Red1"; //Red1 vest SSID
char pw[] = "RedTeam1"; //Red1 vest PW
IPAddress server(192,168,3,1); 
#endif
#ifdef RED2
char ssid[] = "Red2"; //Red2 vest SSID
char pw[] = "RedTeam2"; //Red2 vest PW
IPAddress server(192,168,4,1); 
#endif

//Wifi Variables
int port = 80;
int status = WL_IDLE_STATUS;
bool connection = false;
WiFiClient client;
IPAddress ip;

//Trigger Variables
int buttonState;
int oldState;

void setup() 
{
  buttonState = HIGH;
  oldState = HIGH;
  //Setup LED output and initialize
  pinMode(HitLedR, OUTPUT);
  pinMode(HitLedG, OUTPUT);
  pinMode(HitLedB, OUTPUT);
  pinMode(BOARDLED, OUTPUT);
  digitalWrite(HitLedR, LOW);
  digitalWrite(HitLedG, LOW);
  digitalWrite(HitLedB, LOW);
  digitalWrite(BOARDLED, LOW);

  //Setup Trigger input
  pinMode(trigger, INPUT_PULLUP);

  #ifdef DEBUG
  Serial.begin(9600);
  while(!Serial);   
  Serial.println("Attempting to connect to: " + String(ssid));
  #endif

  status = WiFi.begin(ssid, pw);
  while( status != WL_CONNECTED) 
  {
    #ifdef DEBUG
    Serial.println("Couldn't get a wifi connection");
    #endif
    delay(500);
    status = WiFi.begin(ssid, pw);
  }
  digitalWrite(BOARDLED, HIGH);
  ip = WiFi.localIP();
  #ifdef DEBUG
  Serial.println("Connected to wifi");
  Serial.println(ip);
  #endif
    
  connection = client.connect(server,port);  
  while(!connection)
  {
    #ifdef DEBUG
    Serial.println("Couldn't get a connection to server");
    #endif
    delay(100);
    connection = client.connect(server,port);  
  }
  #ifdef DEBUG
  Serial.println("Connected to server");
  #endif
}

void loop() 
{
  //Trigger Press
  buttonState = digitalRead(trigger);
  //Serial.println(buttonState);
  if((buttonState != oldState) && (oldState != LOW))
  {
    //IR Handler here
    #ifdef DEBUG
    Serial.println("Button Pressed");
    #endif
  }  
  oldState = buttonState;

  //Hit Handler
  if(client.available())
  {
    char c = client.read();
    if(c == HIT)
    {
      #ifdef DEBUG
      Serial.println("HIT");
      #endif
      for(int i = 0; i < 20; i++)
      {
        digitalWrite(HitLedR, !digitalRead(HitLedR));
        delay(500);
      }
    }
  }  
  #ifdef DEBUG
  //Serial.println("Doing other tasks");
  #endif
}
