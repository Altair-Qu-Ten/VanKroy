#include <WiFi.h>
#include "SPIFFS.h"

// WiFi login credentials
const char* ssid = "wlan1313" ;
const char* password = "wlan1313pw" ;

// Initialising Server
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  // Network connection
  Serial.print ("Connecting to ");
  Serial.println ("wlan1313");
  WiFi.begin("wlan1313", "wlan1313pw");
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
