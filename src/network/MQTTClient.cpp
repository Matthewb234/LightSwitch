//
// Created by Matthew on 2/28/2026.
//

#include "MQTTClient.h"
#include <ArduinoJson.h>
#include "../Constants.h"
#include <esp_wpa2.h>

void MQTTClient::initialize() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true);
    reconnect(true);

    client.setServer(NetworkConstants::MQTT_IP, NetworkConstants::MQTT_PORT);
    client.setCallback([this](char *topic, byte *payload, unsigned int length) {
        this->callback(topic, payload, length);
    });
}

void MQTTClient::cleanup() {
    client.disconnect();
    espClient.stop();
}

void MQTTClient::loop() {
    if (WiFi.status() != WL_CONNECTED) {
        reconnect(true);
    } else if (!client.connected()) {
        reconnect(false);
    } else {
        client.loop();
    }
}

void MQTTClient::callback(char *topic, byte *payload, unsigned int length) {
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';

    String msgString = String(message);
    String topicString = String(topic);

    if (topicString == "smarthub/light/power") {
        servo_manager.updateServos(std::nullopt, msgString == "true");
    } else if (topicString == "smarthub/light/dimmer") {
        servo_manager.updateServos(msgString.toInt(), std::nullopt);
    }
}

void MQTTClient::reconnect(bool isWiFi) {
    if (isWiFi) {
        WiFi.begin(NetworkConstants::SSID, NetworkConstants::PASSWORD);
        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
            attempts++;
            if (attempts > 30) {
                Serial.print("\nWiFi Not Connected: ");
                Serial.println(WiFi.status());
                return;
            }
        }
        Serial.print("\nWiFi Connected: ");
        Serial.println(WiFi.localIP());
        WiFi.printDiag(Serial);
    } else {
        if (!client.connected()) {
            String client_id = "esp32-client-" + String(WiFi.macAddress());
            if (client.connect(client_id.c_str(), nullptr, nullptr)) {
                Serial.println("Connected!");
                client.subscribe("smarthub/light/power");
                client.subscribe("smarthub/light/dimmer");
            } else {
                Serial.print("MQTT Connect failed, state: ");
                Serial.println(client.state());
                // No delay here! Let the main loop run.
            }
        }
    }
}




