#include <WiFi.h>
#include <WebServer.h>

// Configuration for the ESP32's own network
const char* ssid = "ESP32_Sensor_AP";
const char* password = "sensor_password"; // Min 8 characters

WebServer server(80);

void handleRoot() {
  int sensorValue = analogRead(34); // Read from GPIO 34
  // Meta-refresh tag keeps the dashboard updating every 2 seconds
  String html = "<html><head><meta http-equiv='refresh' content='2'></head><body>";
  html += "<h1>ESP32 Sensor Dashboard</h1>";
  html += "<h2>Current Value: " + String(sensorValue) + "</h2>";
  html += "<p>Mode: Local Access Point</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  
  // Set up the ESP32 as an Access Point
  Serial.print("Starting Access Point...");
  WiFi.softAP(ssid, password);

  // Print the IP - default is 192.168.4.1
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.begin();
  
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
