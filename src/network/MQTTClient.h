//
// Created by Matthew on 2/28/2026.
//

#ifndef LIGHTSWITCH_WEBSERVER_H
#define LIGHTSWITCH_WEBSERVER_H

#include <WiFi.h>
#include <PubSubClient.h>

#include "../ServoManager.h"


class MQTTClient {
    WiFiClient espClient;
    PubSubClient client;

    ServoManager servo_manager;

    void callback(char *topic, byte *payload, unsigned int length);
public:
    explicit MQTTClient(ServoManager servo_manager) : client(espClient), servo_manager(servo_manager) {}
    void initialize();
    void loop();
    void reconnect(bool isWiFi);
    void cleanup();
};


#endif //LIGHTSWITCH_WEBSERVER_H