#ifndef SEND_H
#define SEND_H

#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
//#include <sensor.h>

//IMPLEMENTAR COMO CLASSE
/*class Message{
    
    public:

    private:

};*/

uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xB5, 0xEC, 0x58};

/*struct Master_recive_data{
    int change=0;
    float data1=0;
    float data2=0;
    float data3=0;
    float data4=0;
    float data5=0;
};

struct Master_send_data{
    int change=0;
    int pin1=1;
    int pin2=2;
    int pin3=3;
    int pin4=0;
    int pin5=0;
};*/


float LocalReadings[] = {0,0,0,0,0,0};

float incomingReadings[] = {0,0,0,0,0,0};
//Master_send_data LocalReadings;

//Master_recive_data incomingReadings;

/*void OnDataSent(const uint8_t *, esp_now_send_status_t);

void OnDataRecv(const uint8_t *, const uint8_t *, int);

void addPeer(uint8_t *);

Master_send_data * sendmasterdata();*/

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  //uint8_t *data= (uint8_t*)sendmasterdata();
  //esp_err_t result = esp_now_send(broadcastAddress, data, sizeof(data));
  //esp_now_send(broadcastAddress, data, sizeof(data));

}

/*void addPeer(uint8_t *peerMacAddress){
    esp_now_peer_info_t peerInfo;
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    memcpy(peerInfo.peer_addr, peerMacAddress, 6);

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}*/

//Master_send_data * sendmasterdata(){
    //return(&LocalReadings);

//}

/*void send(Master_send_data *value, uint8_t *peerMacAddress){
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