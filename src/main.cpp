#include "sensor.h"
#include "send.h"
#include <vector>


using namespace std;

void setvector(vector<Sensor*>&);

vector<Sensor*> sensors;

void clearsensors();

void setup(){
    //Serial.println("socorro");
    Serial.begin(9600);
     //vector<Sensor> sensors;

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
    }

    esp_now_register_send_cb(OnDataSent);
    addPeer(broadcastAddress);
    esp_now_register_recv_cb(OnDataRecv);


    //setvector(sensors);
}

void loop( ){
    
    clearsensors();
    if(LocalReadings.change!=incomingReadings.change){
        setvector(sensors);
        LocalReadings.change=incomingReadings.change;
    }
    else{
        for(int i=1; i<6;i++){
            if(sensors[i]->getpin()!=0){
                if(i==1){
                    LocalReadings.data1=sensors[i]->getdata();
                }
                if(i==2){
                    LocalReadings.data2=sensors[i]->getdata();
                }
                if(i==3){
                    LocalReadings.data3=sensors[i]->getdata();
                }
                if(i==4){
                    LocalReadings.data4=sensors[i]->getdata();
                }
                if(i==5){
                    LocalReadings.data5=sensors[i]->getdata();
                }

            }
       }
    }
    send(&LocalReadings,broadcastAddress);
}

void setvector(vector<Sensor*>& sensor_vector){
    int size;
    int pin_input;
    //float data_input;
    int type_input;
    size = 5;

    //pin_input=27;
    //data_input=0;
    //type_input=1;
    //input size
    //cin >> size;
    //size = Serial.read();
    //

    for(int i=1; i<=size; i++){
        //input values
        //cin >> pin_input >> data_input >> type_input;
        /*pin_input = Serial.read();
        data_input = Serial.read();
        type_input = Serial.read();*/

        /*if(pin_input<0){
            //re_do
            Serial.println("error pin");
        }
        if(data_input<0){
            //re_do
            Serial.println("error data");
        }
        if(type_input<0){
            //re_do
            Serial.println("error type");
        }
        */

        if(i==1){
            type_input=incomingReadings.pin1;
            pin_input=26;
        }
        if(i==2){
            type_input=incomingReadings.pin2;
            pin_input=32;
        }
        if(i==3){
            type_input=incomingReadings.pin3;
            pin_input=0;
        }
        if(i==4){
            type_input=incomingReadings.pin4;
            pin_input=0;
        }
        if(i==5){
            type_input=incomingReadings.pin5;
            pin_input=0;
        }

        switch(type_input){

            case 0:{
            //Sensor inputsensor(0,0,0);
            sensor_vector.push_back(new Sensor(0,0,0));
            //sensor_vector.emplace_back(move(inputsensor));
            //sensor_vector.push_back(inputsensor);
            }
            
            case 1:{
            /*int setmesh=Serial.read();
            if(setmesh==1){
            }
            */
            //thermalsensor inputsensor(pin_input, data_input, type_input);
            
            //sensor_vector.push_back(move(inputsensor));

            sensor_vector.push_back(new thermalsensor(pin_input, 0, type_input));
            //sensor_vector.emplace_back(move(inputsensor));
            //sensor_vector.push_back(inputsensor);
            }

            case 2:{

            sensor_vector.push_back(new thermalsensor(pin_input, 0, type_input));
            
            }
        }
        
    }
    
}

void clearsensors(){
    LocalReadings.data1=0;
    LocalReadings.data2=0;
    LocalReadings.data3=0;
    LocalReadings.data4=0;
    LocalReadings.data5=0;
}







