//
// Created by Matthew on 2/21/2026.
//

#ifndef LIGHTSWITCH_SERVOMANAGER_H
#define LIGHTSWITCH_SERVOMANAGER_H
#include "ESP32Servo.h"
#include <optional>

class ServoManager {
    Servo rockerServo;
    Servo sliderServo;

    public:
    ServoManager(int, int);
    void updateServos(std::optional<int>, std::optional<bool>);
    void printValues();
};


#endif //LIGHTSWITCH_SERVOMANAGER_H