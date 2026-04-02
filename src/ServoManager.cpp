#include "ServoManager.h"
#include "Constants.h"

ServoManager::ServoManager(int rockerPort, int sliderPort) {
    rockerServo.setPeriodHertz(50);
    rockerServo.attach(rockerPort, 500, 2400);
    sliderServo.setPeriodHertz(50);
    sliderServo.attach(sliderPort, 500, 2400);
}

void ServoManager::updateServos(std::optional<int> sliderPercentage, std::optional<bool> rockerOn) {
    if (sliderPercentage.has_value()) {
        Serial.printf("Slider Percentage: %d\n", sliderPercentage.value());
        int sliderValue = map(*sliderPercentage, 1, 3, ServoConstants::SLIDER_MIN, ServoConstants::SLIDER_MAX);
        sliderServo.write(sliderValue);
    }

    if (rockerOn.has_value()) {
        Serial.printf("Rocker On: %s\n", rockerOn.value() ? "true" : "false");
        int rockerValue = *rockerOn ? ServoConstants::ROCKER_ON_POS : ServoConstants::ROCKER_OFF_POS;
        rockerServo.write(rockerValue);
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

