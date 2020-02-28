//COMMENT OUT BEFORE DELIVERY
//#define DEBUG
//DEFINE WHICH TEAM & # BEFORE PROGRAMMING ARDUINO
#define RED1

#include <Adafruit_NeoPixel.h>
#include <WiFiNINA.h>

#define LEDSTRIP 7
#define NUMLED 30
#define BOARDLED LED_BUILTIN

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
  Serial.println("IP Address: " + String(ip));
}
#endif

int team = 0;
int player = 0;
int hit = 0;

void read_data(int PIN, int data[])
{
  int start;
  int i;
  int low;
  
  start = pulseIn(PIN,LOW,100000);

  if(start >= 8750 && start <= 9250)
  {
    low = pulseIn(PIN,HIGH,10000);
    i = 0;
    
    while(low != 0)
    {    
      low = pulseIn(PIN,HIGH,5000);
      if(low >= 500 && low <= 600){data[i] = 0;}
      else 
      {
        if(low >= 1500 && low <= 2100){data[i] = 1;}
            else{data[i] = 0;}
      }
    
      i++; 
    }               
  }
}

void Decoder(int data[])
{  
  if(data[16] == 0 && data[17] == 0 && data[18] == 1 && data[19] == 0 && data[20] == 0 && data[21] == 0 && data[22] == 0 && data[23] == 0){
        if(data[24] == 1 && data[25] == 1 && data[26] == 0 && data[27] == 1 && data[28] == 1 && data[29] == 1 && data[30] == 1 && data[31] == 1){
              team = 1;
              player = 1;
              hit = 1;
        }
       }
  else if(data[16] == 0 && data[17] == 1 && data[18] == 0 && data[19] == 1 && data[20] == 0 && data[21] == 0 && data[22] == 0 && data[23] == 0){
       if(data[24] == 1 && data[25] == 0 && data[26] == 1 && data[27] == 0 && data[28] == 1 && data[29] == 1 && data[30] == 1 && data[31] == 1){
              team = 2;
              player = 2;
              hit = 2;
        }
       }
  else  if(data[16] == 1 && data[17] == 0 && data[18] == 1 && data[19] == 0 && data[20] == 0 && data[21] == 0 && data[22] == 0 && data[23] == 0){
        if(data[24] == 0 && data[25] == 1 && data[26] == 0 && data[27] == 1 && data[28] == 1 && data[29] == 1 && data[30] == 1 && data[31] == 1){
              team = 3;
              player = 3;
              hit = 3;
        }
       }
   else if(data[16] == 1 && data[17] == 1 && data[18] == 0 && data[19] == 1 && data[20] == 0 && data[21] == 0 && data[22] == 0 && data[23] == 0){
        if(data[24] == 0 && data[25] == 0 && data[26] == 1 && data[27] == 0 && data[28] == 1 && data[29] == 1 && data[30] == 1 && data[31] == 1){
              team = 4;
              player = 4;
              hit = 4;
        }
       }  
}

void IR_Check(int PIN)
{
  int data[32];
  
  read_data(PIN,data);
  
  Decoder(data);
}

void setup() 
{
  //Initialize LED strip
  pixels.begin();

  pinMode(BOARDLED, OUTPUT);
  digitalWrite(BOARDLED, LOW);
  
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

  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
}

void loop()
{
  if (status != WiFi.status()) 
  {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) 
    {
      #ifdef DEBUG
      Serial.println("Device connected to AP");
      #endif
    } 
    else 
    {
      // a device has disconnected from the AP, and we are back in listening mode
      #ifdef DEBUG
      Serial.println("Device disconnected from AP");
      #endif
    }
  }
  //}
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
//    server.print('h');
//    delay(20000);

//    //LED Strip handler
//    for(int i=0;i<NUMLED;i++){
//        pixels.setPixelColor(i, pixels.Color(100,0,0));
//        pixels.show();
//        //delay(delayval);
//    }
//
    IR_Check(6); //  Parameter  = PIN Number to check in the form of an integer.
//    IR_Check(5);
//    IR_Check(4);
//    IR_Check(3);
    if(hit){
      server.print('h');
      for (int t = 0; t < 10; t++)
      {
        for (int i = 0; i < NUMLED; i++)
        {
          pixels.setPixelColor(i, pixels.Color(255,0,0));
        }
        pixels.show();
        delay(500);
        pixels.clear();
        pixels.show();
        delay(500);
      }
      hit=0;
    }

//    IR_Check(6); //  Parameter  = PIN Number to check in the form of an integer.
//    if(hit)
//    {
//      server.print('h');
//      pixels.setPixelColor(3, pixels.Color(255,0,0));
//      pixels.show();
//      delay(1000);
//      pixels.clear();
//      pixels.show();
////      Serial.println(team);
////      Serial.println(player);
////      Serial.println(hit);
////      delay(10000);
//    }
    team = 0;
    player = 0;
    hit = 0;
}
