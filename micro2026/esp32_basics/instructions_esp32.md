# 🛠️ Student Guide: ESP32 Web Server & IoT Workshop

Welcome to the ESP32 Workshop! In this session, you will learn how to transform a microcontroller into a web server and a client to build a fully integrated IoT (Internet of Things) system.

---

## 📋 Table of Contents

* [Setting Up Your Workstation](#1-setting-up-your-workstation)
* [Core Concepts](#2-core-concepts)
* [Workshop Exercises](#3-workshop-exercises)

  * [Exercise 1: Remote Control](#exercise-1-remote-control-the-web-switch)
  * [Exercise 2: Live Monitoring](#exercise-2-live-monitoring-the-dashboard)
  * [Exercise 3: Data Logging](#exercise-3-data-logging-esp32-to-laptop)
  * [Exercise 4: Full Integration & mDNS](#exercise-4-full-integration--mdns)
* [Hardware Requirements](#4-hardware-requirements)
* [Troubleshooting Tips](#5-troubleshooting-tips)

---

## 1. Setting Up Your Workstation

Before we start coding, we need to ensure your laptop can communicate with the ESP32 hardware.

### Step A: Prepare the Arduino IDE

1. Open **Arduino IDE**
2. Navigate to **File > Preferences**
3. In the **Additional Boards Manager URLs** field, paste:

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

4. Click **OK**

---

### Step B: Install ESP32 Board Support

1. Go to **Tools > Board > Boards Manager**
2. Search for `esp32`
3. Click **Install** on the package by **Espressif Systems**

---

### Step C: Configure Hardware

1. Connect your ESP32 using a **Micro-USB data cable**
2. Go to:

   * **Tools > Board > ESP32 Arduino**
   * Select: `DOIT ESP32 DEVKIT V1` (or your model)
3. Go to:

   * **Tools > Port**
   * Select the correct COM port

> 💡 **Tip:** If no port appears, install:
>
> * CP210x driver
> * CH340 driver

---

## 2. Core Concepts

* **Station Mode (STA):**
  The ESP32 connects to an existing Wi-Fi network (like a smartphone)

* **IP Address:**
  A unique identifier (e.g., `192.168.1.50`) for devices on a network

* **HTTP Requests:**

  * **GET** → Retrieve data
  * **POST** → Send data

---

## 3. Workshop Exercises

### Exercise 1: Remote Control (The Web Switch)

**Goal:** Host a website on your ESP32 to toggle an LED

**Steps:**

1. Open `ex1_led_server.ino`
2. Update:

   ```cpp
   const char* ssid = "YOUR_WIFI";
   const char* password = "YOUR_PASSWORD";
   ```
3. Upload the code
4. Open **Serial Monitor** (115200 baud)
5. Enter the IP address in your browser
6. Toggle the LED via the webpage

---

### Exercise 2: Live Monitoring (The Dashboard)

**Goal:** View real-time sensor data in your browser

**Steps:**

1. Connect a potentiometer to **GPIO 34**
2. Upload `ex2_sensor_server.ino`
3. Open the ESP32 IP in your browser
4. Observe auto-refreshing sensor values

---

### Exercise 3: Data Logging (ESP32 to Laptop)

**Goal:** Send sensor data to a central Flask server

**Steps:**

1. Get your **Laptop IP Address** from the instructor
2. Open `ex3_client_mode.ino`
3. Update:

   ```cpp
   String serverUrl = "http://YOUR_LAPTOP_IP:5000/data";
   ```
4. Upload the code
5. Verify your data appears on the dashboard

---

### Exercise 4: Full Integration & mDNS

**Goal:** Enable bi-directional communication with a custom domain

**Steps:**

1. Open `ex4_mdns_sync.ino`
2. Update:

   ```cpp
   MDNS.begin("your-group-name");
   ```
3. Upload the code
4. Access your device via:

```
http://your-group-name.local
```

5. Test server-to-device communication

---

## 4. Hardware Requirements

* **Microcontroller:** ESP32 Dev Board
* **Cable:** Micro-USB Data Cable
* **Components:**

  * 1x LED
  * 1x 220Ω Resistor
  * 1x Potentiometer
* **Software:** Arduino IDE 2.0+

---

## 5. Troubleshooting Tips

* ✅ **Wi-Fi Connection**

  * SSID and password are case-sensitive

* ✅ **Serial Monitor**

  * Set baud rate to `115200`

* ✅ **Network Issues**

  * Ensure ESP32 and laptop are on the same **2.4GHz Wi-Fi**

* ✅ **mDNS Issues**

  * Install:

    * Bonjour
    * or iTunes (for Windows)

---

## 🚀 You're Ready!

You now have the foundation to build:

* IoT dashboards
* Remote control systems
* Real-time monitoring solutions

Happy building! 🔧
