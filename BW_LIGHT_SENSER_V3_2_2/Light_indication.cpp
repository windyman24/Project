#include "Light_indication.h"

Light_indication :: Light_indication(int pin)
{
  pinMode(pin,OUTPUT);
  Ethrnet_State_pin = pin;
}
void Light_indication :: Initial(void)
{
  
}
void Light_indication :: work(void)
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (Ethrnet_ledState == LOW) {
      Ethrnet_ledState = HIGH;
    } else {
      Ethrnet_ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(Ethrnet_State_pin, Ethrnet_ledState);
  }
}
void Light_indication :: disconnect(void)
{
  off();
}
void Light_indication :: connect(void)
{
  on();
}
void Light_indication :: on(void)
{
  digitalWrite(Ethrnet_State_pin,LOW);
}
void Light_indication :: off(void)
{
  digitalWrite(Ethrnet_State_pin,HIGH);
}
