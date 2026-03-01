//
// Created by Matthew on 2/28/2026.
//

#ifndef LIGHTSWITCH_WEBSERVER_H
#define LIGHTSWITCH_WEBSERVER_H

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>

#include <utility>

#include "../ServoManager.h"


class WebServer {
    AsyncWebServer server;
    AsyncWebSocket ws;

    ServoManager servo_manager;

    void onEvent(AsyncWebSocket*, AsyncWebSocketClient*, AwsEventType, void*, uint8_t*, size_t);
public:
    explicit WebServer(ServoManager servo_manager) : server(80), ws("/ws"), servo_manager(servo_manager) {}
    void initialize();
    void cleanup();
};


#endif //LIGHTSWITCH_WEBSERVER_H