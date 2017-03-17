# Project
//contain all my practice and job project

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
SoftwareSerial mySerial1(10,11);

void setup(void)
{
  ads.begin();
  Serial.begin(115200);
  mySerial1.begin(115200); 
  
}

void loop(void)
{
  int16_t results;
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */
  int data_length ;
  String data;
  String send_command;

   results = ads.readADC_Differential_0_1();
   data = String(results * multiplier);
   //data =String("client3:")+String(data);
//   data_length = data.length();
//   send_command = String("AT+CIPSEND=4,")+String(data_length)+String("\r\n");
   Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");
//   mySerial1.print(send_command);
//   delay(10);
//   mySerial1.print(data);mySerial1.print("\r\n");
   delay(1000);
   
}
