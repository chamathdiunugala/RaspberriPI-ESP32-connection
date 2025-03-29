#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "12345678-1234-5678-1234-56789abcdef0" // Unique BLE service UUID
#define CHARACTERISTIC_UUID "87654321-4321-6789-4321-abcdef987654" // Unique characteristic UUID

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// Callback for when a device connects or disconnects
class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
        Serial.println("Device connected!");
    }
    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        Serial.println("Device disconnected!");
        pServer->startAdvertising();  // Restart advertising when disconnected
    }
};

void setup() {
    Serial.begin(115200);
    Serial.println("Starting ESP32-S3 BLE server...");

    // Create the BLE device
    BLEDevice::init("ESP32-S3 BLE");

    // Create the BLE Server
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ   | 
                        BLECharacteristic::PROPERTY_WRITE  | 
                        BLECharacteristic::PROPERTY_NOTIFY);

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // Helps with iOS connections
    BLEDevice::startAdvertising();

    Serial.println("ESP32-S3 BLE Server is now advertising...");
}

void loop() {
    if (deviceConnected) {
        String message = "Hello from ESP32-S3! Time: " + String(millis());
        pCharacteristic->setValue(message.c_str());
        pCharacteristic->notify();  // Notify the connected device
        Serial.println("Sent: " + message);
    }
    delay(5000);
}
