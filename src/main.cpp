#include <Arduino.h>

#include "Constants.h"
#include "ServoManager.h"
#include "network/BLEManager.h"

ServoManager *servo_manager;
BLEManager *ble_manager;

void setup(){
    Serial.begin(115200);
    Serial.println("Started");
    servo_manager = new ServoManager(ServoConstants::ROCKER_PORT, ServoConstants::DIMMER_PORT);
    ble_manager = new BLEManager(*servo_manager);
    ble_manager->initialize();
}

void loop(){
    // servo_manager->printValues();
}