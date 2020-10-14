#include "sensor.h"
#include "sendslave.h"
#include <vector>

using namespace std;

void setvector(vector<Sensor*>&);

vector<Sensor*> sensors;

void clearsensors();

void setup(){
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
    memcpy(peerInfo.peer_addr,broadcastAddress, 6);

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    }
    esp_now_register_recv_cb(OnDataRecv);

    setvector(sensors);
}

void loop( ){
    Serial.println("comeco");
    
    /*if(LocalReadings[0]!=incomingReadings[0]){
        setvector(sensors);
        LocalReadings.change=incomingReadings.change;
    }
    else{*/
        for(int i=1; i<6;i++){
            if(sensors[i-1]->getpin()!=0){
                //Serial.print(i);
                //Serial.println(Local)
                //switch i:
                LocalReadings[i]=sensors[i-1]->getdata();
                if(i==1){
                    if(LocalReadings[i]>100){
                        LocalReadings[i]=100;
                    }
                    if(LocalReadings[i]<=0){
                        LocalReadings[i]=1;
                    }
                    Serial.println(LocalReadings[i]);
                }
                if(i==2){
                    Serial.println(LocalReadings[i]);
                }
                if(i==3){
                    if(LocalReadings[i]!=0){
                        LocalReadings[4]=((float((int)(LocalReadings[3])%1000))/10);
                        Serial.println(LocalReadings[4]);
                        LocalReadings[3]=(int)(LocalReadings[3]/1000);
                        Serial.println(LocalReadings[3]);
                        i++;
                    }
                }
                //Serial.println("Teste aaaaaa");
                /*
                if(i==0){
                    LocalReadings.data1=sensors[i]->getdata();
                    if(LocalReadings.data1>100){
                        LocalReadings.data1=100;
                    }
                    if(LocalReadings.data1<=0){
                        LocalReadings.data1=5;
                    }
                    Serial.println(LocalReadings.data1);
                }
                if(i==1){
                    LocalReadings.data2=sensors[i]->getdata();
                }
                if(i==2){

                    LocalReadings.data3=sensors[i]->getdata();
                    if(LocalReadings.data3!=0){
                        LocalReadings.data4=((float((int)(LocalReadings.data3)%1000))/10);
                        Serial.println(LocalReadings.data4);
                        LocalReadings.data3=(int)(LocalReadings.data3/1000);
                        Serial.println(LocalReadings.data3);
                    }
                }
                if(i==3){
                    Serial.println("e4");
                    LocalReadings.data4=sensors[i]->getdata();
                }*/
                /*if(i==4){
                    LocalReadings.data5=sensors[i]->getdata();
                }*/

            }
       }
    //}
    //send(&LocalReadings,broadcastAddress);
    Serial.println("Teste");
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &LocalReadings, sizeof(LocalReadings));
    Serial.print("Send Status: ");
    if (result == ESP_OK) {
        Serial.println("Success");
    }
    else {
        Serial.println("Error");
    }

    delay(1000);
}

void setvector(vector<Sensor*>& sensor_vector){
    int size;
    int pin_input=0;
    //float data_input;
    int type_input=0;
    size = 5;


    for(int i=1; i<=size; i++){

        if(i==1){
            type_input=incomingReadings[1];
            pin_input=32;
        }
        if(i==2){
            type_input=incomingReadings[2];
            pin_input=26;
        }
        if(i==3){
            type_input=incomingReadings[3];
            pin_input=12;
        }
        if(i==4){
            type_input=incomingReadings[4];
            pin_input=0;
        }
        if(i==5){
            type_input=incomingReadings[5];
            pin_input=0;
        }

        if(type_input==0){
            sensor_vector.push_back(new Sensor(0,0,0));
        }
        if(type_input==1){
           sensor_vector.push_back(new soilmoisturesensor(pin_input, 0, type_input));
        }
        if(type_input==2){
            Serial.println("creating");
            sensor_vector.push_back(new thermalsensor(pin_input, 0, type_input));
        }
        if(type_input==3){
            sensor_vector.push_back(new dhttemp(pin_input, 0, type_input));
        }


        /*switch(type_input){

            case 0:{
            //Sensor inputsensor(0,0,0);
            Serial.println("bbbb");
            sensor_vector.push_back(new Sensor(0,0,0));
            //sensor_vector.emplace_back(move(inputsensor));
            //sensor_vector.push_back(inputsensor);
            }
            
            case 1:{
            int setmesh=Serial.read();
            if(setmesh==1){
            }
            */
            //thermalsensor inputsensor(pin_input, data_input, type_input);
            
            //sensor_vector.push_back(move(inputsensor));
            

           /* Serial.println("aaaa");
            sensor_vector.push_back(new thermalsensor(pin_input, 0, type_input));
            //sensor_vector.emplace_back(move(inputsensor));
            //sensor_vector.push_back(inputsensor);
            }

            case 2:{

            sensor_vector.push_back(new soilmoisturesensor(pin_input, 0, type_input));

            }
        }*/
        
    }
    
}

void clearsensors(){
    LocalReadings[1]=0;
    LocalReadings[2]=0;
    LocalReadings[3]=0;
    LocalReadings[4]=0;
    LocalReadings[5]=0;
}







