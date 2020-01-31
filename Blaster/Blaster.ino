//COMMENT OUT BEFORE DELIVERY
//#define DEBUG
//DEFINE WHICH TEAM & # BEFORE PROGRAMMING ARDUINO
#define BLUE1

#include <WiFiNINA.h>

//Trigger/Button Input
#define trigger A4

//IR Emitter
#define IRLED 5

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
IPAddress server(192, 168, 1, 1);
void Command(int PIN)
{
  //Command : 0010_0000
  //1
  for (int i = 0; i <= 1; i++) {
    Zero(PIN);
  }
  ONE(PIN);
  for (int i = 3; i <= 7; i++) {
    Zero(PIN);
  }

  for (int i = 0; i <= 1; i++) {
    ONE(PIN);
  }
  Zero(PIN);
  for (int i = 3; i <= 7; i++) {
    ONE(PIN);
  }
}
#endif

#ifdef BLUE2
char ssid[] = "Blue2"; //Blue2 vest SSID
char pw[] = "BlueTeam2"; //Blue2 vest PW
IPAddress server(192, 168, 2, 1);
void Command(int PIN)
{
  //Command : 0101_0000
  //2
  Zero(PIN);
  ONE(PIN);
  Zero(PIN);
  ONE(PIN);
  for (int i = 4; i <= 7; i++) {
    Zero(PIN);
  }

  ONE(PIN);
  Zero(PIN);
  ONE(PIN);
  Zero(PIN);
  for (int i = 4; i <= 7; i++) {
    ONE(PIN);
  }
}
#endif

#ifdef RED1
char ssid[] = "Red1"; //Red1 vest SSID
char pw[] = "RedTeam1"; //Red1 vest PW
IPAddress server(192, 168, 3, 1);
void Command(int PIN)
{
  //Command : 1010_0000
  //3
  ONE(PIN);
  Zero(PIN);
  ONE(PIN);
  for (int i = 3; i <= 7; i++) {
    Zero(PIN);
  }

  Zero(PIN);
  ONE(PIN);
  Zero(PIN);
  for (int i = 3; i <= 7; i++) {
    ONE(PIN);
  }
}
#endif

#ifdef RED2
char ssid[] = "Red2"; //Red2 vest SSID
char pw[] = "RedTeam2"; //Red2 vest PW
IPAddress server(192, 168, 4, 1);
void Command(int PIN)
{
  //Command : 1101_0000
  //4
  ONE(PIN);
  ONE(PIN);
  Zero(PIN);
  ONE(PIN);
  for (int i = 4; i <= 7; i++) {
    Zero(PIN);
  }

  Zero(PIN);
  Zero(PIN);
  ONE(PIN);
  Zero(PIN);
  for (int i = 4; i <= 7; i++) {
    ONE(PIN);
  }
}
#endif

//Wifi Variables
int port = 80;
int status = WL_IDLE_STATUS;
bool connection = false;
WiFiClient client;
IPAddress ip;

void configwifi()
{
  #ifdef DEBUG
  Serial.println("Attempting to connect to: " + String(ssid));
  #endif

  status = WiFi.begin(ssid, pw);
  while(status != WL_CONNECTED)
  {
    #ifdef DEBUG
    Serial.println("Couldn't get a wifi connection");
    #endif
    delay(500);
    status = WiFi.begin(ssid, pw);
  }
  digitalWrite(BOARDLED, HIGH);
  
  #ifdef DEBUG
  ip = WiFi.localIP();
  Serial.println("Connected to wifi");
  Serial.println(ip);
  #endif

  connection = client.connect(server, port);
  while(!connection)
  {
    #ifdef DEBUG
    Serial.println("Couldn't get a connection to server");
    #endif
    delay(100);
    connection = client.connect(server, port);
  }
  #ifdef DEBUG
  Serial.println("Connected to server");
  #endif
}

//Trigger Variables
int buttonState;
int oldState;

void ONE(int PIN) //Logical '1' – a 562.5µs pulse burst followed by a 1.6875ms space, with a total transmit time of 2.25ms
{
  tone(PIN,38000);
  delayMicroseconds(563);
  noTone(PIN);
  delayMicroseconds(1687);
}

void Zero(int PIN) //Logical '0' – a 562.5µs pulse burst followed by a 562.5µs space, with a total transmit time of 1.125ms
{
  tone(PIN,38000);
  delayMicroseconds(563);
  noTone(PIN);
  delayMicroseconds(563);
}

void Start(int PIN)
{
  tone(PIN,38000);
  delay(9);
  noTone(PIN);
  delayMicroseconds(4500);
}

void Address(int PIN)
{
  for (int i = 0; i <= 7; i++) {
    Zero(PIN); //  address  = 0000_0000
  }
  for (int i = 0; i <= 7; i++) {
    ONE(PIN); // !address = 1111_1111
  }
}

void dummybit(int PIN)
{
  Zero(PIN);
}

void ShootSignal(int PIN)
{
  Start(PIN);
  dummybit(PIN);
  Address(PIN);
  Command (PIN);
  dummybit(PIN);
}

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
  while (!Serial);
  #endif

  configwifi();
}

void loop()
{ 
  if(WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(BOARDLED, LOW);
    configwifi();
  }
      
  //Trigger Press
  buttonState = digitalRead(trigger);
  //Serial.println(buttonState);
  if ((buttonState != oldState) && (oldState != LOW))
  {
    //IR Handler here
    #ifdef DEBUG
    Serial.println("Button Pressed");
    #endif
    ShootSignal(IRLED);
  }
  oldState = buttonState;

  //Hit Handler
  if (client.available())
  {
    char c = client.read();
    if (c == HIT)
    {
      #ifdef DEBUG
      Serial.println("HIT");
      #endif
      for (int i = 0; i < 20; i++)
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
