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
bool led2State = false;  // Trạng thái LED thứ hai

void setup() {
  Serial.begin(115200); 
  mySerial.begin(9600);  

  WiFi.softAP(apSSID, apPassword);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  

  server.on("/", HTTP_GET, handleRoot); 
  server.on("/toggle", HTTP_GET, toggleLED);  
  server.on("/toggle2", HTTP_GET, toggleLED2);  // Đường dẫn mới cho LED thứ 2

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
    html += "<p><strong>LED 1 is ON</strong></p>";
  } else {
    html += "<p><strong>LED 1 is OFF</strong></p>";
  }

  if (led2State) {
    html += "<p><strong>LED 2 is ON</strong></p>";
  } else {
    html += "<p><strong>LED 2 is OFF</strong></p>";
  }

  html += "<a href='/toggle'><button>Toggle LED 1</button></a>";
  html += "<a href='/toggle2'><button>Toggle LED 2</button></a>";  // Nút điều khiển LED thứ 2
  html += "<br><br>";
  html += "<a href='/'>Refresh</a>"; 
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void toggleLED() {
  ledState = !ledState;
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

void toggleLED2() {
  led2State = !led2State;
  if (led2State) {
    mySerial.println("LED2_ON");
    Serial.println("Sending LED2_ON to Arduino");
  } else {
    mySerial.println("LED2_OFF");
    Serial.println("Sending LED2_OFF to Arduino");
  }

  server.sendHeader("Location", "/");
  server.send(303);
}