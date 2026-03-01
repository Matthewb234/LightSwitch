#include <Arduino.h>

#include "ServoManager.h"
#include "network/BLEManager.h"

ServoManager *servo_manager;
BLEManager *ble_manager;

void setup(){
    Serial.begin(115200);
    delay(3000);
    Serial.println("Started");
    servo_manager = new ServoManager(1, 2);
    ble_manager = new BLEManager(*servo_manager);
    ble_manager->initialize();
}

void loop(){
    Serial.println("Running");
    delay(5000);
}