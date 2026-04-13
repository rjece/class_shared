#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPmDNS.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }

  // Start mDNS so we can find the ESP32 at http://esp32-workshop.local
  if (!MDNS.begin("esp32-workshop")) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started: esp32-workshop.local");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    // Replace IP with your laptop IP
    http.begin("http://192.168.1.XX:5000/update"); 
    http.addHeader("Content-Type", "application/json");

    String json = "{\"value\":\"" + String(random(0, 1024)) + "\"}";
    int httpCode = http.POST(json);

    if (httpCode == 200) {
      String payload = http.getString();
      // Simple logic: if server response contains "ON", turn on LED
      if (payload.indexOf("ON") > 0) digitalWrite(ledPin, HIGH);
      else digitalWrite(ledPin, LOW);
    }
    http.end();
  }
  delay(2000);
}
