#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// DHT11 setup
#define DHTPIN 2       // GPIO2 corresponds to D2
#define DHTTYPE DHT11  // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi setup
const char* ssid = "Your_SSID";       // Replace with your Wi-Fi SSID
const char* password = "Your_PASSWORD"; // Replace with your Wi-Fi password
const char* serverIP = "0.0.0.0"; // Replace with the Base Station's IP
const int serverPort = 80;

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  // Read DHT11 data
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Send data to Base Station
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String serverURL = String("http://") + serverIP + ":" + serverPort + "/data";
    http.begin(serverURL);

    String postData = "temperature=" + String(temp) + "&humidity=" + String(humidity);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      Serial.print("Data sent. HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending data: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Wi-Fi not connected.");
  }

  delay(5000); // Send data every 5 seconds
}

