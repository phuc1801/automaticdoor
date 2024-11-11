#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 2     
#define DHTTYPE DHT11   

#define rxPin 10
#define txPin 11
SoftwareSerial mySerial(rxPin, txPin);  

DHT dht(DHTPIN, DHTTYPE); 

#define ledPin1 3   // LED hiện tại
#define ledPin2 4   // LED mới

void setup() {
  Serial.begin(9600);     
  mySerial.begin(9600);    
  dht.begin();             

  pinMode(ledPin1, OUTPUT);  
  pinMode(ledPin2, OUTPUT);  // Thiết lập chân LED mới làm OUTPUT
}

void loop() {

  float h = dht.readHumidity();      
  float t = dht.readTemperature();   

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String data = String(t) + "," + String(h);
  mySerial.println(data);  // Gửi dữ liệu đến ESP8266
  Serial.println("Sent: " + data);   
  delay(2000); 
  
  if (mySerial.available() > 0) {
    String command = mySerial.readStringUntil('\n');  
    Serial.println("Received command: " + command);  
    command.trim(); 

    // Điều khiển LED 1
    if (command == "LED_ON") {
      digitalWrite(ledPin1, HIGH);  
      Serial.println("LED 1 is ON"); 
    } else if (command == "LED_OFF") {
      digitalWrite(ledPin1, LOW);   
      Serial.println("LED 1 is OFF"); 
    }

    // Điều khiển LED 2
    else if (command == "LED2_ON") {
      digitalWrite(ledPin2, HIGH);  
      Serial.println("LED 2 is ON"); 
    } else if (command == "LED2_OFF") {
      digitalWrite(ledPin2, LOW);   
      Serial.println("LED 2 is OFF"); 
    }
  }
}
