#include <Wire.h>
#include <DHT.h>

#define DHTPIN 4        // Chân kết nối DATA của DHT11
#define DHTTYPE DHT11   // Sử dụng cảm biến DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); // Khởi tạo Serial Monitor
  Wire.begin(8); // Khởi tạo I2C với địa chỉ 8
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();    // Đọc độ ẩm
  float t = dht.readTemperature();  // Đọc nhiệt độ (C)

  // Kiểm tra lỗi
  if (isnan(h) || isnan(t)) {
    Serial.println("Không thể đọc dữ liệu từ DHT11");
    return;
  }

  // Gửi dữ liệu qua I2C dưới dạng chuỗi
  String data = String(t) + "," + String(h); // Chuỗi "nhiệt độ,độ ẩm"
  Wire.beginTransmission(4); // Gửi đến địa chỉ I2C 4
  Wire.write(data.c_str());   // Gửi dữ liệu
  Wire.endTransmission();      // Kết thúc truyền

  Serial.println("Gửi: " + data); // In ra dữ liệu gửi

  delay(2000); // Gửi dữ liệu mỗi 2 giây
}
