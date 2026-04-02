//
// Created by Matthew on 2/21/2026.
//

#ifndef LIGHTSWITCH_SERVOMANAGER_H
#define LIGHTSWITCH_SERVOMANAGER_H
#include "ESP32Servo.h"

class ServoManager {
    Servo rockerServo;
    Servo sliderServo;

    int prevRockerValue;
    int prevSliderValue;

    public:
    ServoManager(int, int);
    void updateServos(int, bool);
    void printValues();
};


#endif //LIGHTSWITCH_SERVOMANAGER_H