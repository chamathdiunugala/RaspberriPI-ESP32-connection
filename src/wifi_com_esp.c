
// ESP32-S3 Client Code (Arduino IDE)
#include <WiFi.h>

// WiFi credentials
const char* ssid = "SSID";
const char* password = "password";

// Raspberry Pi server details
const char* serverIP = "192.168.8.118"; // Replace with your Raspberry Pi's IP
const int serverPort = 12345;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println(" CONNECTED");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Create a message to send
  String message = "Hello from ESP32-S3! Time: " + String(millis());
  
  // Connect to the server
  if (client.connect(serverIP, serverPort)) {
    // Send the message
    client.println(message);
    Serial.println("Message sent: " + message);
    
    // Wait for response
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout!");
        client.stop();
        delay(10000); // Wait 10 seconds before retrying
        return;
      }
    }
    
    // Read response
    String response = client.readStringUntil('\n');
    Serial.println("Server response: " + response);
    
    // Close the connection
    client.stop();
  } else {
    Serial.println("Connection to server failed");
  }
  
  delay(5000); // Wait 5 seconds before sending the next message
}