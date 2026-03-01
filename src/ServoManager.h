//
// Created by Matthew on 2/21/2026.
//

#ifndef LIGHTSWITCH_SERVOMANAGER_H
#define LIGHTSWITCH_SERVOMANAGER_H
#include "ESP32Servo.h"

class ServoManager {
    Servo rockerServo;
    Servo sliderServo;

    int SLIDER_MIN = 0;
    int SLIDER_MAX = 180;
    int ROCKER_ON_POS = 90;
    int ROCKER_OFF_POS = 0;
    public:
    ServoManager(int, int);
    void updateServos(int, bool);
};


#endif //LIGHTSWITCH_SERVOMANAGER_H