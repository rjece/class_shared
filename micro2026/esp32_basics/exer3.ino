#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
// REPLACE with your laptop's IP address from the Flask app terminal
const char* serverUrl = "http://192.168.1.XX:5000/update"; 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int sensorVal = analogRead(34);
    String httpRequestData = "{\"value\":\"" + String(sensorVal) + "\"}";
    
    int httpResponseCode = http.POST(httpRequestData);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response: " + response);
    }
    http.end();
  }
  delay(5000); // Send data every 5 seconds
}
