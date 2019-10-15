#ifndef Light_indication_h
#define Light_indication_h
#include "Arduino.h"
#define Ethrnet_disconnect LOW;
#define Ethrnet_connect HIGH;

class Light_indication
{
  public:
    int Ethrnet_ledState = LOW;             // ledState used to set the LED
    // Generally, you should use "unsigned long" for variables that hold time
    // The value will quickly become too large for an int to store
    unsigned long previousMillis = 0;        // will store last time LED was updated
    // constants won't change:
    const long interval = 300;           // interval at which to blink (milliseconds)
    Light_indication(int pin);
    void Initial(void);
    void work(void);
    void disconnect(void);
    void connect(void);
  private:
    int Ethrnet_State_pin;
    void on(void);
    void off(void);
};

#endif
