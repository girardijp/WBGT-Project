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
    ~Sensor();
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

class thermalsensor : public Sensor{
    
    public:
    thermalsensor();
    thermalsensor(int, float, int);
    ~thermalsensor();

    int settempmesh(const int);
    int gettempmesh() const;

    float getdata();

    private:

    int setwire(const int);
    OneWire getwire() const;
    int setdalasdata();
    DallasTemperature getdalasdata() const; //setar como private
    void dalasbegin() const;
    float gettempc();

    OneWire* wire=NULL;
    DallasTemperature* dalasdata=NULL;
    int temp_mesh=0;
    float temperature_C;

};

class soilmoisturesensor : public Sensor{
    public:
    soilmoisturesensor();
    soilmoisturesensor(int,float,int);
    ~soilmoisturesensor();
    float getdata();

    private:
    float moisture;

};

class dhttemp : public Sensor{
    public:
    dhttemp();
    dhttemp(int,float,int);
    ~dhttemp();
    float getdata();
    void dhtbegin();
    void dhtset(int);

    private:
    DHT *dhtdata;
    float temp;
    float humi;
};








#endif