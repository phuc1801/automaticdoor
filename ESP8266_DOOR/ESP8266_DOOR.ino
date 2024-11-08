#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>


const char* ssid = "duyphuc";       
const char* password = "123456789"; 

#define DHT_PIN D4        
#define DHTTYPE DHT11     
#define LED_PIN D2       

DHT dht(DHT_PIN, DHTTYPE); 
ESP8266WebServer server(80); 

bool LEDstatus = LOW;

void setup() {
  Serial.begin(115200);
  dht.begin(); 
  pinMode(LED_PIN, OUTPUT); 
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Access Point IP:");
  Serial.println(myIP);
  
  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.on("/data", handleData); 
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
  
  if(LEDstatus) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void handle_OnConnect() {
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledon() {
  LEDstatus = HIGH;
  Serial.println("LED: ON");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledoff() {
  LEDstatus = LOW;
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}


void handleData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  String data = "{ \"temp\": " + String(t) + ", \"humidity\": " + String(h) + " }";
  server.send(200, "application/json", data);
}

String updateWebpage(uint8_t LEDstatus) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>TEAM 7</h1>\n";
  ptr += "<h1>ESP8266 Web Server</h1>\n";
  
  // Trang thai led
  if(LEDstatus) {
    ptr += "<p>LED: ON</p><a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  } else {
    ptr += "<p>LED: OFF</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";
  }

  // Them thong tin t va h
  ptr += "<h3>THONG TIN CAM BIEN:</h3>\n";
  ptr += "<p>Nhiet Do: <span id='temp'>--</span> °C</p>";
  ptr += "<p>Do Am: <span id='humidity'>--</span> %</p>";
  
  ptr += "<script>";
  ptr += "setInterval(() => {";
  ptr += "  fetch('/data').then(response => response.json()).then(data => {";
  ptr += "    document.getElementById('temp').textContent = data.temp;";
  ptr += "    document.getElementById('humidity').textContent = data.humidity;";
  ptr += "  });";
  ptr += "}, 2000);"; 
  ptr += "</script>";
  
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
