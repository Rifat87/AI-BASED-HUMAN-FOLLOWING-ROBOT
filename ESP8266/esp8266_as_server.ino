#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial arduinoSerial(2, 3);  // RX, TX pins connected to Arduino

const char* ssid = "No_Network";
const char* password = "rifat2001005";
// const int espSerialBaudRate= 9600;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.softAP(ssid, password);

  IPAddress apIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(apIP);

  server.begin();
  arduinoSerial.begin(115200);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    // Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        // Serial.print("Received data from ESP32: ");
        Serial.println(data);

        // Process the received data as needed
        // ...
        arduinoSerial.println(data);
        // Send response back to ESP32
        client.println("Hello Rifat vai.. Paisi");
      }
    }
    client.stop();
    // Serial.println("Client disconnected");
  }
}
