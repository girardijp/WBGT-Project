#ifndef SENDSLAVE_H
#define SENDSLAVE_H

#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>


uint8_t broadcastAddress[] = {0x24, 0x62, 0xAB, 0xFF, 0x69, 0xF8};

float ports[]={0,32,26,12};

float LocalReadings[] = {0,0,0,0,0,0,0};

float incomingReadings[] = {0,3,3,3};

float logsensor[] = {0,3,3,3};


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);

}





#endif