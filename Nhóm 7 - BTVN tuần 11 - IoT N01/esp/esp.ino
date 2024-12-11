#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

// Khai báo SoftwareSerial (D1 = GPIO5, D2 = GPIO4)
SoftwareSerial ArduinoSerial(5, 4); // RX = D1 (GPIO5), TX = D2 (GPIO4)

// Cập nhật các thông tin mạng Wi-Fi
const char* ssid = "Duy Hieu";
const char* password = "2knife4me";
const char* server = "http://192.168.1.11:4433/ctd/receive.php"; // Địa chỉ server PHP của bạn

WiFiClient client;  // Tạo đối tượng WiFiClient

void setup() {
  Serial.begin(9600);         // UART chính để debug
  ArduinoSerial.begin(9600);  // SoftwareSerial để nhận dữ liệu từ Arduino

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (ArduinoSerial.available() > 0) {
    String data = ArduinoSerial.readStringUntil('\n'); // Đọc dữ liệu từ Arduino

    // Kiểm tra nếu có dữ liệu nhận được
    if (data.length() > 0) {
      Serial.println("Data received: " + data); // Debug dữ liệu nhận được

      // Gửi dữ liệu lên server PHP qua HTTP POST
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(client, server); // Sử dụng WiFiClient và URL

        // Cấu hình HTTP POST
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        String postData = "data=" + data; // Dữ liệu cần gửi

        int httpResponseCode = http.POST(postData); // Gửi yêu cầu POST

        // Kiểm tra mã phản hồi HTTP
        if (httpResponseCode > 0) {
          Serial.println("Data sent to server successfully, Response Code: " + String(httpResponseCode));
        } else {
          Serial.println("Error sending data to server, Response Code: " + String(httpResponseCode));
        }

        http.end(); // Kết thúc HTTP request
      } else {
        Serial.println("WiFi not connected. Skipping data sending.");
      }
    }
  }
  delay(1000); // Delay một chút trước khi tiếp tục
}
