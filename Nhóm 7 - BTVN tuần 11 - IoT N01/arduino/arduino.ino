#include <SoftwareSerial.h>

int i1 = 3;
int i2 = 4;
int e1 = 5;
int ls1 = 7;  // Limited switch 1
int ls2 = 8;  // Limited switch 2
int echo1 = 9;
int trig1 = 10;
int echo2 = 11;
int trig2 = 12;
int H = 150;
int T = 1000;
unsigned long thoigian;
int ds1;
int ds2;
int dental = 15;
SoftwareSerial espSerial(2, 6); // TX = pin 6, RX = pin 7

void forward() {
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
  analogWrite(e1, H);
}

void goback() {
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  analogWrite(e1, 250);
}

void stop() {
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  analogWrite(e1, 0);
}

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600); // Khởi tạo SoftwareSerial
  pinMode(ls1, INPUT_PULLUP);
  pinMode(ls2, INPUT_PULLUP);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(e1, OUTPUT);
}

void distance() {
  // Đo khoảng cách cảm biến 1
  digitalWrite(trig1, 0);
  delayMicroseconds(2);
  digitalWrite(trig1, 1);
  delayMicroseconds(10);
  digitalWrite(trig1, 0);
  thoigian = pulseIn(echo1, HIGH);
  ds1 = int(thoigian / 2 / 29.412);

  // Đo khoảng cách cảm biến 2
  digitalWrite(trig2, 0);
  delayMicroseconds(2);
  digitalWrite(trig2, 1);
  delayMicroseconds(10);
  digitalWrite(trig2, 0);
  thoigian = pulseIn(echo2, HIGH);
  ds2 = int(thoigian / 2 / 29.412);
}

void program() {
  distance();
  int rls1 = digitalRead(ls1);
  int rls2 = digitalRead(ls2);

  // Gửi dữ liệu tới ESP8266 qua SoftwareSerial
  String data = String(rls1) + " " + String(rls2) + " " + String(ds1) + " " + String(ds2) + "\n";
  espSerial.print(data);

  // Debug dữ liệu
  Serial.print("Data sent to ESP8266: ");
  Serial.println(data);

  // Điều khiển logic
  if (rls1 == 1 && rls2 == 1) {
    if (ds1 >= dental && ds2 >= dental) {
      goback();
    } else {
      forward();
    }
  } else if (rls1 == 0 && rls2 == 1) {
    if (ds1 >= dental && ds2 >= dental) {
      stop();
      delay(T);
    } else {
      forward();
    }
  } else if (rls1 == 1 && rls2 == 0) {
    if (ds1 >= dental && ds2 >= dental) {
      goback();
    } else {
      stop();
      delay(T);
    }
  }
  delay(1000);
}

void loop() {
  program();
}
