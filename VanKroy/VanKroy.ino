#include <ESP8266WiFi.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

float Temperature;
float Humidity;
String formattedTime;
String Date;
int Day;
int Month;
int Year;

WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 3600;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

unsigned long epochTime = timeClient.getEpochTime();
struct tm *ptm = gmtime ((time_t *)&epochTime);

// WiFi login credentials
char* ssid = "wlan1313" ;
char* password = "wlan1313pw" ;

// Initialising Server
WiFiServer server(80);

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

String controlString; // Captures out URI querystring
int blueLEDPin = 2; // pin where our blue LED is connected
 
void setup(){
pinMode(blueLEDPin, OUTPUT); // change pin 2 to OUTPUT pin
  Serial.begin (115200);
  // Network connection
  Serial.print ("Connecting to ");
  Serial.println (ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
    {
    delay (500) ;
    Serial.print(".");
    }
  Serial.println ("WiFi connected");
  Serial.println ("local IP-Adress :");
  Serial.println (WiFi.localIP());
  //Start Server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  // if new client connects
  if (client) {
    Serial.println ("new client");
      //String with incoming data from client
      String header;
      String currentLine = "";
      while (client.connected()) {
        // If there is a byte available
        if (client.available()) {
          // read the byte
          char c = client.read();
          Serial.write (c);
          header += c;
          if (c == '\n') {
            if (currentLine.length() == 0) {
              client.println("HTTP/I.1 200 0K");
              client.println ("Content-type:text/html");
              client.println ("Connection: close");
              client.println();
              //HTML
              client.println("<p> Hallo Mamer </p>");
              // stopping the while loop
              break ;

              // control arduino pin
              if(controlString.indexOf("?GPLED2ON") &gt; -1) //checks for LEDON
              {
              digitalWrite(blueLEDPin, HIGH); // set pin high
              }
              else{
              if(controlString.indexOf("?GPLED2OFF") &gt; -1) //checks for LEDOFF
              {
              digitalWrite(blueLEDPin, LOW); // set pin low
              }
              }
              //clearing string for next read
              controlString="";
              }
              else {
              currentLine = "";
              }
            }
            else if (c != '\r') {
            currentLine += c;
            }
          }
        }
        header = "";
  
        client.stop();
        Serial.println("client closed connection" );
        Serial.println();
  }
}
