#ifndef SENDSLAVE_H
#define SENDSLAVE_H

#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>


uint8_t broadcastAddress[] = {0x24, 0x62, 0xAB, 0xFF, 0x69, 0xF8};

float ports[]={0,32,26,12,0,0};

float LocalReadings[] = {0,0,0,0,0,0};

float incomingReadings[] = {0,0,0,0,0,0};

float logsensor[] = {0,0,0,0,0,0};


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);

}

/*void OnDataSent(const uint8_t *, esp_now_send_status_t);

void OnDataRecv(const uint8_t *, const uint8_t *, int);

void addPeer(uint8_t *);

void send(Sender_send_data *, uint8_t *);

void addPeer(uint8_t *peerMacAddress){
    esp_now_peer_info_t peerInfo;
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    memcpy(peerInfo.peer_addr, peerMacAddress, 6);

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}*/

/*void send(Sender_send_data *value, uint8_t *peerMacAddress){
    esp_err_t result = esp_now_send(peerMacAddress, (uint8_t *) value, sizeof(value));
    Serial.print("Send Status: ");
    if (result == ESP_OK) {
        Serial.println("Success");
    }
    else {
        Serial.println("Error");
    }
}*/




#endif