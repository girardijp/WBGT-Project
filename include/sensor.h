#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>
#include "DHT.h"
using namespace std;

class Sensor{
    
    public:
    Sensor();
    Sensor(int, float, int);
    virtual ~Sensor();
    Sensor(const Sensor &s){
        this->pin=s.pin;
        this->data=s.data;
        this->type=s.type;
    }

    int getpin() const;
    virtual float getdata();
    int gettype() const;
    int setpin(const int);
    int settype(const int);
    int setdata(const float);

    private:

    int pin;
    mutable float data;
    int type;

};


class dhttemp : public Sensor{
    public:
    dhttemp();
    dhttemp(int,float,int);
    ~dhttemp();
    float getdata();
    void dhtbegin();
    void dhtset(int);
    void deletedhtdata();

    private:
    DHT *dhtdata;
    float temp;
    float humi;
};








#endif