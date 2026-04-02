#include <Arduino.h>

#include "Constants.h"
#include "ServoManager.h"
#include "network/BLEManager.h"
#include "network/MQTTClient.h"

ServoManager *servo_manager;
MQTTClient *mqtt_client;
BLEManager *ble_manager;

void setup(){
    Serial.begin(115200);
    Serial.println("Started");
    servo_manager = new ServoManager(ServoConstants::ROCKER_PORT, ServoConstants::DIMMER_PORT);
    // ble_manager = new BLEManager(*servo_manager);
    mqtt_client = new MQTTClient(*servo_manager);
    // ble_manager->initialize();
    mqtt_client->initialize();
}

void loop(){
    mqtt_client->loop();
}