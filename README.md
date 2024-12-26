# Distributed Sensor Network with ESP32 and DHT11

This project demonstrates a distributed sensor network using two ESP32 microcontrollers and a DHT11 temperature and humidity sensor. The system includes a **Sensor Node** that collects environmental data and sends it to a **Base Station** via Wi-Fi. The Base Station hosts a web server to display the received data in real-time.

---

## Features
- **Temperature and Humidity Monitoring:** Real-time data collection using the DHT11 sensor.
- **HTTP Communication:** Sensor Node sends data to the Base Station via HTTP POST requests.
- **Web Interface:** Base Station hosts a live web page displaying the latest sensor readings.
- **Wi-Fi Connectivity:** Both devices communicate over a shared Wi-Fi network.

---

## System Architecture
The system consists of two ESP32 devices:
1. **Sensor Node:**
   - Reads data from the DHT11 sensor.
   - Sends the data to the Base Station over Wi-Fi.

2. **Base Station:**
   - Acts as an HTTP server to receive data.
   - Displays the latest sensor readings on a web page.

**Diagram:**

```plaintext
[ Sensor Node (ESP32 + DHT11) ] ---> [ Base Station (ESP32) ] ---> [ Web Browser ]
```

---

## Hardware Requirements
- 2 x ESP32 microcontrollers
- 1 x DHT11 temperature and humidity sensor
- 1 x Breadboard
- Jumper wires
- 4.7kΩ - 10kΩ resistor (pull-up for the DHT11 data line)

---

## Software Requirements
- Arduino IDE
- Libraries:
  - [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library) by Adafruit
  - [Adafruit Unified Sensor Library](https://github.com/adafruit/Adafruit_Sensor)
  - Built-in ESP32 Wi-Fi and HTTP libraries (`WiFi.h`, `HTTPClient.h`, `WebServer.h`)

---

## Setup Instructions

### **Sensor Node Wiring**
1. Connect the DHT11 sensor:
   - **VCC** → **3.3V** (ESP32 power pin).
   - **GND** → **GND** (ESP32 ground pin).
   - **DATA** → **GPIO2 (D2)** with a 4.7kΩ pull-up resistor to **3.3V**.
2. Upload the **Sensor Node Code** to the ESP32.

### **Base Station Setup**
1. No external peripherals are required for the Base Station.
2. Upload the **Base Station Code** to the second ESP32.

### **Wi-Fi Configuration**
Update the following lines in both sketches with your Wi-Fi credentials:
```cpp
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
```

---

## How to Use
1. **Power On Both ESP32 Boards:**
   - Ensure both the Sensor Node and Base Station are connected to the same Wi-Fi network.

2. **Access the Web Interface:**
   - Open the Serial Monitor for the Base Station to find its IP address.
   - Enter the IP address in your browser (e.g., `http://192.168.1.100`).

3. **Monitor the Data:**
   - The web page will display the latest temperature and humidity readings sent by the Sensor Node.

---

## Screenshots
### Hardware Setup
![Hardware Setup](Images/hardware_setup.jpg)

### Web Interface
![Web Interface](Images/web_interface.png)

---

## Future Improvements
- **Data Logging:** Store sensor data in ESP32 flash memory or on an external server.
- **Encryption:** Secure communication between the Sensor Node and Base Station with HTTPS.
- **Scalability:** Support multiple Sensor Nodes sending data to the same Base Station.

---

## Lessons Learned
- Setting up Wi-Fi communication between IoT devices.
- Hosting a web server on the ESP32.
- Troubleshooting and debugging hardware and software interactions.

---

## License
This project is shared for educational purposes under the MIT License. Feel free to use, modify, and improve upon this work.

---

## Acknowledgments
- [Adafruit DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
- [Espressif's ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/)

---
