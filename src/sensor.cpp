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
    /*try{
        if(this->type!=type||this->pin!=pin||this->data!=data){
            throw a;
        }   
    }
    catch(int a){
        cout<<"error in assumption";
    }
    */
}

Sensor::~Sensor(){

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
    /*try{
        if(this->pin!=pin){
            throw a;
        }   
    }
    catch(int a){
        cout<<"error in assumption";
        return(0);
    }
    */
   return(1);
}

int Sensor::setdata(const float data){
    this->data=data;
    /*try{
        if(this->data!=data){
            throw a;
        }   
    }
    catch(int a){
        cout<<"error in assumption";
        return(0);
    }
    */
   return(1);
}

int Sensor::settype(const int type){
    this->type=type;
    /*try{
        if(this->type!=type){
            throw a;
        }   
    }
    catch(int a){
        cout<<"error in assumption";
        return(0);
    }
    */
   return(1);
}

thermalsensor::thermalsensor(int pin, float data, int type) : Sensor(pin,data,type){
    setwire(pin);
    setdalasdata();
    dalasbegin();

}

thermalsensor::thermalsensor() : Sensor(){

}

thermalsensor::~thermalsensor(){

}

int thermalsensor::settempmesh(int temp_mesh){
    if (temp_mesh!=0 || temp_mesh!=1){
        return(0);
    }
    this->temp_mesh=temp_mesh;
    /*try{
        if(this->temp_mesh!=temp_mesh){
            throw a;
        }   
    }
    catch(int a){
        cout<<"error in assumption";
        return(0);
    }
    */

}

int thermalsensor::gettempmesh() const{
    return temp_mesh;
}

int thermalsensor::setwire(const int input_pin){
    if(input_pin<0){
        return(0);
    }
    OneWire *tempwire = new OneWire(input_pin);
    wire=tempwire;
    Serial.println("set thermalwire");
    return(1);

}


OneWire thermalsensor::getwire() const{
    return (*wire);
}

int thermalsensor::setdalasdata(){
    if(wire==NULL){
        return(0);
    }
    DallasTemperature *tempdalasdata = new DallasTemperature(wire);
    dalasdata=tempdalasdata;

    return(1);
}

DallasTemperature thermalsensor::getdalasdata() const{
    return(*dalasdata);
}

void thermalsensor::dalasbegin() const{
    Serial.println("begin thermal");
    if(dalasdata!=NULL){
        dalasdata->begin();
    }
}

float thermalsensor::gettempc(){
    if(dalasdata==NULL){
        return(0);
    }
    dalasdata->requestTemperatures();
    this->temperature_C = dalasdata->getTempCByIndex(0);
    setdata(this->temperature_C);
    return(this->temperature_C);
}

float thermalsensor::getdata(){
    return(gettempc());
}

soilmoisturesensor::soilmoisturesensor() : Sensor(){

}

soilmoisturesensor::soilmoisturesensor(int pin, float data, int type) : Sensor(pin,data,type){

}

soilmoisturesensor::~soilmoisturesensor(){

}

float soilmoisturesensor::getdata(){
    if(getpin()<=0){
        return(0);
    }
    moisture = analogRead(getpin());
    Serial.println(moisture);
    moisture=map(moisture, 3700, 1700, 0, 100);
    setdata(moisture);
    /*if(moisture>=100){
      //moisture=100;
    }*/
    return(moisture);
}

dhttemp::dhttemp () : Sensor() {

}

dhttemp::dhttemp(int pin, float data, int type) : Sensor(pin,data,type){
    dhtset(getpin());
    dhtbegin();

}

dhttemp::~dhttemp(){

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

