#include "send.h"
#include <iostream>
#include <string>
#include <Arduino.h>
#include <stdlib.h>
using namespace std;

int testcounter =0;

void setup() {
  

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
  Serial.println("Error initializing ESP-NOW");
  return;
  }

  esp_now_register_send_cb(OnDataSent);
  //addPeer(broadcastAddress);
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
  }
  esp_now_register_recv_cb(OnDataRecv);
  

}

void loop() {
    testcounter+=1;
    Serial.println("");
    Serial.println("");
    for(int i=0;i<4;i++){
      if(i==0){
        Serial.print("Umidade do solo: ");
        Serial.println(incomingReadings[1]);

      }
      if(i==1){
        Serial.print("Temperatura do solo: ");
        Serial.println(incomingReadings[2]);

      }
      if(i==2){
        Serial.print("Umidade do ar: ");
        Serial.println(incomingReadings[3]);

      }
      if(i==3){
        Serial.print("Temperatura do ar: ");
        Serial.println(incomingReadings[4]);

      }

    
    }
    //LocalReadings[0]=rand()%10;
    if(testcounter>10){
      LocalReadings[0]=1;
      LocalReadings[1]=1;
      LocalReadings[2]=2;
      LocalReadings[3]=3;

    }
    Serial.println("Teste");
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &LocalReadings, sizeof(LocalReadings));
    Serial.print("Send Status: ");
    if (result == ESP_OK) {
        Serial.println("Success");
    }
    else {
        Serial.println("Error");
    }
    //send(&LocalReadings,broadcastAddress);
    delay(3150);
}