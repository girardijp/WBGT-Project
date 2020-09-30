#include "send.h"

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);

}

void addPeer(uint8_t *peerMacAddress){
    esp_now_peer_info_t peerInfo;
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    memcpy(peerInfo.peer_addr, peerMacAddress, 6);

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void send(Sender_send_data *value, uint8_t *peerMacAddress){
    esp_err_t result = esp_now_send(peerMacAddress, (uint8_t *) value, sizeof(value));
    Serial.print("Send Status: ");
    if (result == ESP_OK) {
        Serial.println("Success");
    }
    else {
        Serial.println("Error");
    }
}