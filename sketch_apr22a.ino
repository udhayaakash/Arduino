Host a Local Web server
Code:
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

int irpin=D6;

ESP8266WebServer server(80);

void setup() {
  pinMode(irpin, INPUT);
  Serial.begin(115200);
  Serial.println("Start");
  WiFi.begin("vivo 1601", "aaaaaaaa"); //Connect to your router
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print("Type this IP in your browser:");
  Serial.println((WiFi.localIP().toString()));                  //Your IP address, the URL to visit
  
  server.on ( "/", handleRoot );                                //Event handling function attachment
  server.onNotFound ( handleNotFound );

  server.begin();                                               //Begin the server
  Serial.println("HTTP server started");
}

void loop() {
 server.handleClient();       
}

void handleRoot() {
  server.send ( 200, "text/html", getPage() );
}

String getPage() {
  String page = "<html lang=en-EN>";
  page+=  "<head><meta http-equiv='refresh' content='5'/><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<title>NodeMCU Web Server</title>";
  
  page += "<style>body {";
  page+=  "background-color:#EEEEEE;";
  page+=  "font-family: Verdana;";
  page+=  "font-size: 30px;";
  page+=  "Color:#333333;";
  page+=  "}</style></head>";
  
  page += "<body><p><center><strong>NodeMCU Web Server</strong></center></p>";
  page += "<p></p>";
  page += "<p></p>";
  
  page += "<p><center><strong>IR Sensor : </strong>";
  if(digitalRead(irpin))
  page += "Clear</center></p>";
  else
  page += "Obstacle Detected</center></p>";
  page += "<p></p>";
  page += "<p></p>";
  return page;
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
}
