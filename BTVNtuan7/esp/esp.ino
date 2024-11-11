#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

#define rxPin 4
#define txPin 5
SoftwareSerial mySerial(rxPin, txPin);


const char* apSSID = "nhom7";    
const char* apPassword = "123456789";  


ESP8266WebServer server(80);

String temperature = "";
String humidity = "";

bool ledState = false;  

void setup() {
  Serial.begin(115200); 
  mySerial.begin(9600);  


  WiFi.softAP(apSSID, apPassword);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  


  server.on("/", HTTP_GET, handleRoot); 
  server.on("/toggle", HTTP_GET, toggleLED);  


  server.begin();
}

void loop() {

  if (mySerial.available() > 0) {
    String receivedData = mySerial.readStringUntil('\n');  
    int commaIndex = receivedData.indexOf(',');
    if (commaIndex != -1) {
      temperature = receivedData.substring(0, commaIndex);  
      humidity = receivedData.substring(commaIndex + 1);   
    }
  }
  server.handleClient();
}

void handleRoot() {

  String html = "<html><head>";
  
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; background-color: #f4f4f4; color: #333; margin: 0; padding: 0; text-align: center; }";
  html += "h1 { color: #4CAF50; }"; 
  html += "p { font-size: 18px; margin: 10px 0; }";  
  html += "strong { color: #333; }";  
  html += "button { background-color: #008CBA; border: none; color: white; padding: 12px 20px; font-size: 16px; cursor: pointer; border-radius: 4px; margin: 10px 0; }";
  html += "button:hover { background-color: #005f73; }";  
  html += "a { text-decoration: none; }"; 
  html += "a:hover { color: #4CAF50; }"; 
  html += "</style>";
  
  html += "</head><body>";
  

  html += "<h1>TEAM 7</h1>";
  html += "<h2>Temperature and Humidity Data</h2>";
  html += "<p><strong>Temperature:</strong> " + temperature + " &#8451;</p>";
  html += "<p><strong>Humidity:</strong> " + humidity + " %</p>";


  if (ledState) {
    html += "<p><strong>LED is ON</strong></p>";
  } else {
    html += "<p><strong>LED is OFF</strong></p>";
  }


  html += "<a href='/toggle'><button>Toggle LED</button></a>";
  html += "<br><br>";
  html += "<a href='/'>Refresh</a>"; 
  html += "</body></html>";

  server.send(200, "text/html", html);
}



void toggleLED() {
 
  ledState = !ledState;
  String flag = mySerial.readStringUntil('\n');
 
  if (ledState) {
    mySerial.println("LED_ON");
    Serial.println("Sending LED_ON to Arduino");
  } else {
    mySerial.println("LED_OFF");
    Serial.println("Sending LED_OFF to Arduino");
  }


  server.sendHeader("Location", "/");
  server.send(303);
}
