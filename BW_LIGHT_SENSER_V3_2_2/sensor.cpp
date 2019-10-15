#include "Arduino.h"
#include "sensor.h"

Light_Sensor :: Light_Sensor(int s1, int s2, int s3)
{
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);

  sensor1 = s1;
  sensor2 = s2;
  sensor3 = s3;

}
/*Read digital state on sensor1 */
bool Light_Sensor ::ReadSensor1_D(void)
{
  return digitalRead(sensor1);
}
/*Read digital state on sensor2 */
bool Light_Sensor ::ReadSensor2_D(void)
{
  return digitalRead(sensor2);
}
/*Read digital state on sensor3 */
bool Light_Sensor ::ReadSensor3_D(void)
{
  return digitalRead(sensor3);
}

byte Light_Sensor ::ReadAll(void)
{
  byte state = 0x00;
  state = ReadSensor1_D();
  state << 1 ;
  state = ReadSensor2_D();
  state << 1 ;
  state = ReadSensor3_D();
  state << 1 ;
  return state;
}
int Light_Sensor ::ReadSensor1_A(void)
{
  int val= analogRead(Sensor1_analog);
  return val;
}
int Light_Sensor ::ReadSensor2_A(void)
{
  int val= analogRead(Sensor2_analog);
  return val;
}
int Light_Sensor ::ReadSensor3_A(void)
{
  int val= analogRead(Sensor3_analog);
  return val;
}
