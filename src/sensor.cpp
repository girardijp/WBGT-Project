#include "sensor.h"
#include <string>

Sensor::Sensor(){
    pin = 0;
    data = 0;
    type = 0;

}

Sensor::Sensor(int pin, float data, int type){
    this->pin = pin;
    this->data = data;
    this->type = type;
  
}

Sensor::~Sensor(){
    Serial.println("Destructing main");

}

int Sensor::getpin() const{
    return(pin);
}

float Sensor::getdata(){
    return(data);
}
int Sensor::gettype() const{
    return(type);
}

int Sensor::setpin(const int pin){
    this->pin=pin;
    
   return(1);
}

int Sensor::setdata(const float data){
    this->data=data;
    
   return(1);
}

int Sensor::settype(const int type){
    this->type=type;
    
   return(1);
}


dhttemp::dhttemp () : Sensor() {

}

dhttemp::dhttemp(int pin, float data, int type) : Sensor(pin,data,type){
    dhtset(getpin());
    dhtbegin();

}

dhttemp::~dhttemp(){
    Serial.println("Destructing dht");
    deletedhtdata();

}

void dhttemp::dhtset(int pin){
    DHT *dhtnode = new DHT(pin,DHT11);
    dhtdata=dhtnode;

}

void dhttemp::dhtbegin(){
    if(dhtdata==NULL){
        return;
    }
    dhtdata->begin();
}

float dhttemp::getdata(){
    if(dhtdata==NULL){
        return(0);
    }
    float t=dhtdata->readTemperature();
    float h=dhtdata->readHumidity();
    if(h<1){
        h=1;
    }
    if(h>100){
        h=100;
    }
    if(t<0){
        t=1;
    }
    if(t>=100){
        t=99;
    }
    
    return(h*1000+t*10);
}

void dhttemp::deletedhtdata(){
    delete dhtdata;
}

