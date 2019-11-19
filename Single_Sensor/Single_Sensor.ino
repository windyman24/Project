#include "display.h"

MAX7219 show_all(7);
MAX7219 show_single(6);
#define ON LOW
#define OFF HIGH
#define Re2zeroe_bt 2
bool raise_flag = false;
bool fall_flag = false;
long average_valuse = 0;
long total = 0;
long batch = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(3,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(Re2zeroe_bt,INPUT_PULLUP);
  digitalWrite(3,LOW);
  digitalWrite(8,HIGH);
//  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(200);
  show_all.initial();
  show_all.on();
  show_single.initial();
  show_single.on();
  average();
}

void loop() {
//   Serial.println(analogRead(A0));
  if (raise_flag == true && fall_flag == true)
  {
    Serial.println("凸");
    digitalWrite(8,HIGH);
    total++;
    batch++;
    show_all.show(total);
    show_single.show(batch);
    send_pulse();
    raise_flag = false; 
    fall_flag = false;
  }
  else
  {
    if (analogRead(A0) < average_valuse-35)
    {
      Serial.println("<");
      digitalWrite(8,LOW);
      fall_flag = true;
    }
    while (fall_flag == true && (analogRead(A0) >= average_valuse+10 ||analogRead(A0) <= average_valuse-10))
    {
      Serial.println("<>");
      raise_flag = true;
    }
  }
  if(digitalRead(Re2zeroe_bt) == LOW)
  {
    batch = 0;
    show_single.show(batch);
  }
}
void average()
{                                                                           
  for (int i=0;i < 50; i++)
  {
    average_valuse += analogRead(A0);
    delay(10);
  }
  average_valuse = average_valuse / 50;
  Serial.print("average_valuse:");
  Serial.println(average_valuse);
}
void send_pulse()
{
   digitalWrite(3,OFF);
   delay(500);
   digitalWrite(3,ON);
}
