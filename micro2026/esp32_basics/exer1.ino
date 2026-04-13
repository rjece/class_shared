#include <WiFi.h>
#include <WebServer.h>

// Set the credentials for your ESP32's own network
const char* ssid = "ESP32_Control_Panel";
const char* password = "password123"; 

WebServer server(80);
const int ledPin = 2; // Onboard LED

void handleRoot() {
  String html = "<h1>ESP32 LED Control (AP Mode)</h1>";
  html += "<p><a href='/on'><button>ON</button></a></p>";
  html += "<p><a href='/off'><button>OFF</button></a></p>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  // Configure the ESP32 as an Access Point
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  // Get the IP assigned to the AP (Default is 192.168.4.1)
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

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
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
