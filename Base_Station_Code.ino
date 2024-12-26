#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi setup
const char* ssid = "SSID";       // Replace with your Wi-Fi SSID
const char* password = "PASSWORD"; // Replace with your Wi-Fi password

WebServer server(80);  // HTTP server on port 80

// Variables to store received data
float receivedTemp = 0.0;
float receivedHumidity = 0.0;

// Handle HTTP POST requests for /data
void handleData() {
  if (server.hasArg("temperature") && server.hasArg("humidity")) {
    receivedTemp = server.arg("temperature").toFloat();
    receivedHumidity = server.arg("humidity").toFloat();
    Serial.println("Data received via POST.");
  }
  server.send(200, "text/plain", "Data received");
}

// Serve data on a web page
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP32 Sensor Data</h1>";
  html += "<p><b>Temperature:</b> " + String(receivedTemp) + " °C</p>";
  html += "<p><b>Humidity:</b> " + String(receivedHumidity) + " %</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.print("Base Station IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up server routes
  server.on("/data", HTTP_POST, handleData);
  server.on("/", HTTP_GET, handleRoot);  // Handle GET requests for the web page
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();  // Handle incoming HTTP requests
}
