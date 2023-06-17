#include <WiFi.h>

const char* ssid = "No_Network";
const char* password = "rifat2001005";
const char* serverIP = "192.168.4.1";  // IP address of ESP8266 AP
const int serverPort = 80;

int value1 ;
int value2 ;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi network
  // Serial.println();
  // Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  // Serial.println("WiFi connected");
  // Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (!client.connected()) {
    // Serial.println("Connecting to server...");
    if (client.connect(serverIP, serverPort)) {
      Serial.println("Connected to server");
      if(Serial.available()){
        
          String data = Serial.readStringUntil('\n');
  
  // Parse the received data
      int commaIndex = data.indexOf(',');
      if (commaIndex != -1) {
      String value2String = data.substring(0, commaIndex);
      String value1String = data.substring(commaIndex + 1);
      value2 = value2String.toInt();
      value1 = value1String.toInt();

      String data = String(value1) + "," + String(value2);
      // client.print("The angle is: ");
      // Send data to ESP8266
      client.println(data);
      
      String response = "Received: " + data;
      Serial.println(response);

        // String data = Serial.readStringUntil('\n');
        // sscanf(data.c_str(), "%d %d", &value1, &value2);
        
        

        // String response = "REceived: " + data;
        // Serial.println(response);
      }
      }
      // Send data to ESP8266
      // for(int i=1; i<=10; i++){
      //   client.println(i);
      //   delay(1000);
      // }
      // this is for sending one by one
      // client.print("The angle is: ");
      //   client.println(value1);
      //   client.print("The distance is: ");
      //   client.println(value2);
      // client.println("Hello vai.. Disi..paisen?");

      delay(1000); // Adjust the delay according to your needs

      // Read response from ESP8266
      while (client.available()) {
        String response = client.readStringUntil('\n');
        // Serial.print("Response from ESP8266: ");
        Serial.println(response);
      }
      client.stop();
    } else {
      Serial.println("Connection failed");
    }
  }
}
