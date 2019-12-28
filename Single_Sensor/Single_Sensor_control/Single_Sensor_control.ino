#include <EEPROM.h>
#include "display.h"

MAX7219 show_all(7);
MAX7219 show_single(6);
#define ON LOW
#define OFF HIGH
#define Re2zeroe_bt 2
#define Power_LED 9
#define State_LED 8
bool raise_flag = false;
bool fall_flag = false;
long average_valuse = 0;
long ADC_trigger=0;
long total = 0;
long batch = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(230400);
  pinMode(3, OUTPUT);
  pinMode(State_LED, OUTPUT);
  pinMode(Power_LED, OUTPUT);
  pinMode(Re2zeroe_bt, INPUT_PULLUP);
  digitalWrite(3, LOW);
  digitalWrite(State_LED, HIGH);
  //  digitalWrite(8,LOW);
  digitalWrite(Power_LED, LOW);
  delay(200);
  show_all.initial();
  show_all.on();
  show_single.initial();
  delay(10);
  show_single.on();
  average();
  ADC_trigger = read_limitfromEEPROM();
}
long read_limitfromEEPROM()
{
  long EE_ADC = EEPROM.read(0);
  return EE_ADC;
}
void loop() {
  //   Serial.println(analogRead(A0));
  if (raise_flag == true && fall_flag == true)
  {
    Serial.println("凸");
    digitalWrite(State_LED, HIGH);
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
    if (analogRead(A0) < average_valuse - ADC_trigger)
    {
      Serial.println("<");
      digitalWrite(State_LED, LOW);
      fall_flag = true;
    }
    while (fall_flag == true && (analogRead(A0) >= average_valuse + 10 || analogRead(A0) <= average_valuse - 10))
    {
      Serial.println("<>");
      raise_flag = true;
    }
  }
  if (digitalRead(Re2zeroe_bt) == LOW)
  {
    long timer_counter = 0;
    while (1)
    {
      if (digitalRead(Re2zeroe_bt) == LOW)
      {
        timer_counter++;
      }
      else
      {
        timer_counter = 0;
      }
        
//      if (digitalRead(Re2zeroe_bt) == HIGH && timer_counter > 100000)
      if (timer_counter > 250000)
      {
        while (1)
        {
          for (int i = 0; i < 3; i++)
          {
            show_single.off();
            delay(300);
            show_single.on();
            delay(300);
          }
          int EEPROM_ADC_val = 0;
          EEPROM_ADC_val = EEPROM.read(0);
          show_single.show____();
          delay(1000);
          show_single.show(EEPROM_ADC_val);
          while(1)
          {
            if(digitalRead(Re2zeroe_bt) == LOW)
            {
              delay(200);
              EEPROM_ADC_val++;
              if(EEPROM_ADC_val>255)EEPROM_ADC_val=0;
              show_single.show(EEPROM_ADC_val);
              EEPROM.write(0, EEPROM_ADC_val);
              
            }
          }
        }

      }
      else if (digitalRead(Re2zeroe_bt) == HIGH && timer_counter < 10000)
      {

        timer_counter = 0;

        break;
      }
    }
    batch = 0;
    show_single.show(batch);
  }
}
void average()
{
  for (int i = 0; i < 50; i++)
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
  digitalWrite(3, OFF);
  delay(500);
  digitalWrite(3, ON);
}
