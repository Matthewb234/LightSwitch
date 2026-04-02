//
// Created by Matthew on 2/28/2026.
//

#ifndef LIGHTSWITCH_CONSTANTS_H
#define LIGHTSWITCH_CONSTANTS_H

namespace NetworkConstants {
    constexpr const char* SSID = "SmartHub";
    constexpr const char* PASSWORD = "Reptille!23";
    constexpr const char* MQTT_IP = "192.168.4.1";
    constexpr int MQTT_PORT = 1883;
};

namespace ServoConstants {
    constexpr int ROCKER_PORT = 1;
    constexpr  int DIMMER_PORT = 2;

    constexpr int SLIDER_MIN = 120;
    constexpr int SLIDER_MAX = 20;
    constexpr int ROCKER_ON_POS = 130;
    constexpr int ROCKER_NUETRAL_POS = 100;
    constexpr int ROCKER_OFF_POS = 80;
}

#endif //LIGHTSWITCH_CONSTANTS_H