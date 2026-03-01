#include "ServoManager.h"

ServoManager::ServoManager(int rockerPort, int sliderPort) {
    rockerServo.setPeriodHertz(50);
    rockerServo.attach(rockerPort, 500, 2400);
    sliderServo.setPeriodHertz(50);
    sliderServo.attach(sliderPort, 500, 2400);
}

void ServoManager::updateServos(int sliderPercentage, bool rockerOn) {
    int sliderValue = map(sliderPercentage, 0, 100, SLIDER_MIN, SLIDER_MAX);
    sliderServo.write(sliderValue);
    rockerServo.write(rockerOn ? ROCKER_ON_POS : ROCKER_OFF_POS);
}

