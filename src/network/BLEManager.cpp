//
// Created by Matthew on 2/28/2026.
//

#include "BLEManager.h"
#include <ArduinoJson.h>

class CharacteristicCallback : public BLECharacteristicCallbacks {
    ServoManager &servo_manager;

public:
    explicit CharacteristicCallback(ServoManager &servo_manager) : servo_manager(servo_manager) {}

    void onWrite(BLECharacteristic *characteristic) override {
        String message = characteristic->getValue().c_str();
        if (message.length() == 0) return;

        JsonDocument doc;
        if (deserializeJson(doc, message) != DeserializationError::Ok) return;

        int light_level = doc["light_level"];
        bool light_on = doc["light_on"];
        servo_manager.updateServos(light_level, light_on);
    }
};

class ServerCallback : public BLEServerCallbacks {
    void onDisconnect(BLEServer *server) override {
        Serial.println("Client disconnected, restarting advertising");
        BLEDevice::getAdvertising()->start();
    }

    void onConnect(BLEServer *server) override {
        Serial.println("Client connected");
    }
};

void BLEManager::initialize() {
    BLEDevice::init("LightSwitch");
    server = BLEDevice::createServer();
    server->setCallbacks(new ServerCallback());

    BLEService *service = server->createService(SERVICE_UUID);
    characteristic = service->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );

    characteristic->addDescriptor(new BLE2902());
    characteristic->setCallbacks(new CharacteristicCallback(servo_manager));

    service->start();

    BLEAdvertising *advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(SERVICE_UUID);
    advertising->start();

    Serial.println("BLE ready");
}