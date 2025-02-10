#pragma once

#include <PubSubClient.h>
#include <WiFiClient.h>
#include <SerialNumber.h>
#include <WiFi.h>

class MQTT {
private:
    WiFiClient espClient;
    PubSubClient client;
    const char* mqtt_server;
    const char* mqtt_user;
    const char* mqtt_password;
    int mqtt_port;
    unsigned long lastMqttAttempt = 0;
    const int reconnectInterval = 10000; // 10 seconds

public:
    MQTT(const char* server,
         const char* user,
         const char* password,
         int port) 
        : client(espClient),
          mqtt_server(server),
          mqtt_user(user),
          mqtt_password(password),
          mqtt_port(port) {
    }

    void setup() {
        client.setServer(mqtt_server, mqtt_port);
        client.setCallback([this](char* topic, byte* payload, unsigned int length) {
            this->callback(topic, payload, length);
        });
    }

    void loop() {
        if (millis() - lastMqttAttempt > reconnectInterval && WiFi.status() == WL_CONNECTED) {
            if (!client.connected()) {
                reconnect();
            }
            lastMqttAttempt = millis();
        }
        client.loop();
    }

    void publishHappiness(float happinessRate) {
        if (client.connected()) {
            client.publish(
                ("aipeaq/" + SerialNumber::getSerialNumber() + "/happiness").c_str(), 
                String(happinessRate).c_str()
            );
        }
    }

private:
    void callback(char* topic, byte* message, unsigned int length) {
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");
        String messageTemp;
        
        for (int i = 0; i < length; i++) {
            Serial.print((char)message[i]);
            messageTemp += (char)message[i];
        }
        Serial.println();

        if (String(topic) == "aipeaq/output") {
            Serial.print("Changing output to ");
            if(messageTemp == "on"){
                Serial.println("on");
            }
            else if(messageTemp == "off"){
                Serial.println("off");
            }
        }
    }

    void reconnect() {
        Serial.print("Attempting MQTT connection...");
        if (client.connect(
            ("aipeaq_" + SerialNumber::getSerialNumber()).c_str(), 
            mqtt_user, 
            mqtt_password)) {
            Serial.println("connected");
            client.subscribe("aipeaq/output");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
        }
    }
};