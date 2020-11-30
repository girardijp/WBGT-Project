#include "sensor.h"
#include "sendslave.h"
#include <vector>

using namespace std;

int size=3,buffer=0;
vector<Sensor*> sensors;
void setvector(vector<Sensor*>&);
void clearsensors();
void addPeer(uint8_t *,esp_now_peer_info_t&);

void setup(){
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
    }

    esp_now_register_send_cb(OnDataSent);
    esp_now_peer_info_t peerInfo;
    addPeer(broadcastAddress,peerInfo);
    esp_now_register_recv_cb(OnDataRecv);

    setvector(sensors);
}

void loop( ){
    
    int i=1;
    if(LocalReadings[0]!=incomingReadings[0]){
        setvector(sensors);
        LocalReadings[0]=incomingReadings[0];
    }
    else{
        for(i=1; i<=size*2;i+=2){
            if(sensors[(i-1)/2]->getpin()!=0){
                LocalReadings[i]=sensors[(i-1)/2]->getdata();

                if(sensors[(i-1)/2]->gettype()==3){
                        int buf=LocalReadings[i]
;                       LocalReadings[i]=(int)(buf/1000);
                        Serial.println(LocalReadings[i]);
                        LocalReadings[i+1]=((float(buf%1000))/10);
                        Serial.println(LocalReadings[i+1]);
                    
                }

            }
       }
    }
    i=1;
   
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &LocalReadings, sizeof(LocalReadings));
    Serial.print("Send Status: ");
    if (result == ESP_OK) {
        Serial.println("Success");
    }
    else {
        Serial.println("Error");
    }

    delay(1500);
}

void setvector(vector<Sensor*>& sensor_vector){

    int type_input=0;
    
    //32.26.12
    if(buffer==0){
        for(int i=1; i<=size; i++){
            type_input=incomingReadings[i];

            if(type_input==0){
                sensor_vector.push_back(new Sensor(0,0,0));
            }
            if(type_input==3){
                sensor_vector.push_back(new dhttemp(ports[i], 0, type_input));
            }
            logsensor[i]=type_input;
            
        }
    }   
    else{
        for(int i=1; i<=size; i++){
            if((logsensor[i])!=(incomingReadings[i])){
                type_input=incomingReadings[i];

                if(type_input==0){
                    delete sensors[i-1];
                    sensors[i-1]=new Sensor(0,0,0);
                }
                if(type_input==3){
                    delete sensors[i-1];
                    sensors[i-1]=new dhttemp(ports[i], 0, type_input);
                }
                logsensor[i]=type_input;
            }
        }
    }
    buffer=1;
}


void addPeer(uint8_t *peerMacAddress,esp_now_peer_info_t &peerInfo){
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    memcpy(peerInfo.peer_addr, peerMacAddress, 6);

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}








