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

struct Sender_send_data{
    float data1;
    float data2;
    float data3;
    float data4;
    float data5;
};

struct Sender_recive_data{
    int change;
    int pin1;
    int pin2;
    int pin3;
    int pin4;
    int pin5;
};

void OnDataSent(const uint8_t *, esp_now_send_status_t);

void OnDataRecv(const uint8_t *, const uint8_t *, int);

void addPeer(uint8_t *);

Sender_send_data LocalReadings;

Sender_recive_data incomingReadings;


void send(Sender_send_data *, uint8_t *);




#endif