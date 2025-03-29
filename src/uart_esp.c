#include <HardwareSerial.h>

HardwareSerial SerialPort(1);  // Use UART1

#define TX_PIN 17  // ESP32-S3 TX
#define RX_PIN 18  // ESP32-S3 RX

void setup() {
    Serial.begin(115200); // USB Serial for debugging
    SerialPort.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN); // UART1

    Serial.println("ESP32-S3 UART Ready");
}

void loop() {
    if (SerialPort.available()) {
        String receivedData = SerialPort.readStringUntil('\n');
        Serial.print("Received: ");
        Serial.println(receivedData);
    }

    SerialPort.println("Hello from ESP32-S3!");
    delay(1000);
}
