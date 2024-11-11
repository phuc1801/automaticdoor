#include <SoftwareSerial.h>
#include <DHT.h>


#define DHTPIN 2     
#define DHTTYPE DHT11   


#define rxPin 10
#define txPin 11
SoftwareSerial mySerial(rxPin, txPin);  

DHT dht(DHTPIN, DHTTYPE); 

#define ledPin 3 

void setup() {
  Serial.begin(9600);     
  mySerial.begin(9600);    
  dht.begin();             

  pinMode(ledPin, OUTPUT);  
}

void loop() {

  float h = dht.readHumidity();      
  float t = dht.readTemperature();   


  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  String data = String(t) + "," + String(h);


  mySerial.println(data);              
  Serial.println("Sent: " + data);   
  delay(2000); 
  

  if (mySerial.available() > 0) {
    String command = mySerial.readStringUntil('\n');  
    Serial.println("Received command: " + command);  
    command.trim(); 
    
    if (command == "LED_ON") {
      digitalWrite(ledPin, HIGH);  
      Serial.println("LED is ON"); 
    }
 
    else if (command == "LED_OFF") {
      digitalWrite(ledPin, LOW);   
      Serial.println("LED is OFF"); 
     
    }
     
  }

  
}
