#include "ServoManager.h"

#include "Constants.h"

ServoManager::ServoManager(int rockerPort, int sliderPort) {
    rockerServo.setPeriodHertz(50);
    rockerServo.attach(rockerPort, 500, 2400);
    sliderServo.setPeriodHertz(50);
    sliderServo.attach(sliderPort, 500, 2400);
}

void ServoManager::updateServos(int sliderPercentage, bool rockerOn) {
    int sliderValue = map(sliderPercentage, 1, 3, ServoConstants::SLIDER_MIN, ServoConstants::SLIDER_MAX);
    if (prevSliderValue != sliderValue) {
        sliderServo.write(sliderValue);
        prevSliderValue = sliderValue;
    }

    int rockerValue = rockerOn ? ServoConstants::ROCKER_ON_POS : ServoConstants::ROCKER_OFF_POS;
    if (prevRockerValue != rockerValue) {
        rockerServo.write(rockerValue);
        prevRockerValue = rockerValue;
        delay(200);
        rockerServo.write(ServoConstants::ROCKER_NUETRAL_POS);
    }
}

void ServoManager::printValues() {
    Serial.print("Slider: ");
    Serial.println(sliderServo.read());
    Serial.print("Rocker: ");
    Serial.println(rockerServo.read());
}

