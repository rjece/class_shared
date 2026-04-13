#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);
const int ledPin = 2; // Onboard LED

void handleRoot() {
  String html = "<h1>ESP32 LED Control</h1>";
  html += "<p><a href='/on'><button>ON</button></a></p>";
  html += "<p><a href='/off'><button>OFF</button></a></p>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", []() {
    digitalWrite(ledPin, HIGH);
    server.send(200, "text/html", "LED is ON. <a href='/'>Back</a>");
  });
  server.on("/off", []() {
    digitalWrite(ledPin, LOW);
    server.send(200, "text/html", "LED is OFF. <a href='/'>Back</a>");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
