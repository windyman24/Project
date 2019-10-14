#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#define Sensor1_analog A2
#define Sensor2_analog A1
#define Sensor3_analog A0
//＊＊Important sensor can't use pin 13,12,11,10 ,because these pins are used for W5500 Ethernet
class Light_Sensor
{
  public:
    Light_Sensor(int s1,int s2,int s3);
    bool ReadSensor1_D(void);
    bool ReadSensor2_D(void);
    bool ReadSensor3_D(void);
    int ReadSensor1_A(void);
    int ReadSensor2_A(void);
    int ReadSensor3_A(void); 
    byte ReadAll(void);
  private:
    int sensor1,sensor2,sensor3;
    
};
#endif
