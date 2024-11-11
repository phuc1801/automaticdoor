#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 5); // Khởi tạo I2C
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100); // Giữ cho vòng lặp chạy
}

void receiveEvent(int bytes) {
  String data = "";

  while (Wire.available()) {
    char c = Wire.read();
    data += c;
  }

  if (data.length() > 0) {
    Serial.println("Nhận: " + data);
  }
}
