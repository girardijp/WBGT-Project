#include "sensor.h"
#include <vector>


using namespace std;

void setvector(vector<Sensor*>&);

vector<Sensor*> sensors;

void setup(){
    //Serial.println("socorro");
    Serial.begin(9600);
     //vector<Sensor> sensors;
    setvector(sensors);
}

void loop( ){

   
    //
    if(sensors[0]->gettype()==1){
        Serial.print(sensors[0]->getdata());
        Serial.println(" °C \n");
        delay(1000);
    }






}

void setvector(vector<Sensor*>& sensor_vector){
    int size;
    int pin_input;
    float data_input;
    int type_input;

    size = 1;
    pin_input=27;
    data_input=1;
    type_input=1;
    //input size
    //cin >> size;
    //size = Serial.read();
    //

    for(int i=0; i<size; i++){
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

        switch(type_input){

            case 0:{
            Sensor inputsensor(pin_input, data_input, type_input);
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
            sensor_vector.push_back(new thermalsensor(pin_input, data_input, type_input));
            //sensor_vector.emplace_back(move(inputsensor));
            //sensor_vector.push_back(inputsensor);
            }
        }
        
    }
    
}





