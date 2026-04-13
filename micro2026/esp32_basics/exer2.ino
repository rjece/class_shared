#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

void handleRoot() {
  int sensorValue = analogRead(34); // Read from GPIO 34
  String html = "<html><head><meta http-equiv='refresh' content='2'></head><body>";
  html += "<h1>ESP32 Sensor Dashboard</h1>";
  html += "<h2>Current Value: " + String(sensorValue) + "</h2>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Server started at: " + WiFi.localIP().toString());
}

void loop() {
  server.handleClient();
}
