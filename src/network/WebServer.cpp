//
// Created by Matthew on 2/28/2026.
//

#include "WebServer.h"
#include <ArduinoJson.h>
#include "../Constants.h"
#include <esp_wpa2.h>



void WebServer::initialize() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true);

    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)Constants::IDENTITY, strlen(Constants::IDENTITY));
    // esp_wifi_sta_wpa2_ent_set_username((uint8_t *)Constants::USERNAME, strlen(Constants::USERNAME));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)Constants::PASSWORD, strlen(Constants::PASSWORD));
    esp_wifi_sta_wpa2_ent_enable();

    WiFi.begin(Constants::SSID);
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

    ws.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
        this->onEvent(server, client, type, arg, data, len);
    });
    server.addHandler(&ws);
    server.begin();
}

void WebServer::cleanup() {
    ws.cleanupClients();
}

void WebServer::onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
    if(type == WS_EVT_CONNECT){
        Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
        client->printf("Hello Client %u :)", client->id());
        client->ping();
    } else if(type == WS_EVT_DISCONNECT){
        //client disconnected
        Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
    } else if(type == WS_EVT_ERROR){
        //error was received from the other end
        Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
    } else if(type == WS_EVT_PONG){
        //pong message was received (in response to a ping request maybe)
        Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
    } else if(type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo*)arg;
        if(info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
            data[len] = 0;
            JsonDocument doc;
            String message = (char*)data;

            if(deserializeJson(doc, message) != DeserializationError::Ok) return;
            int light_level = doc["light_level"];
            bool light_on = doc["light_on"];
            servo_manager.updateServos(light_level, light_on);
        }
    }
}




