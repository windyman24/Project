#ifndef  Display_h
#define Display_h
#include "Arduino.h"
#include "SPI.h"

// the MAX7219 address map (datasheet table 2)
#define MAX7219_DECODE_REG      (0x09)
#define MAX7219_DIGIT_REG(pos)  ((pos) + 1)
#define MAX7219_INTENSITY_REG   (0x0A)
#define MAX7219_SCANLIMIT_REG   (0x0B)
#define MAX7219_SHUTDOWN_REG    (0X0C)
#define MAX7219_DISPLAYTEST_REG (0x0F)
#define MAX7219_OFF             (0x0)
#define MAX7219_ON              (0x1)

const int slaveSelectPin = 10;
const byte reg[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
const byte reg_num[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
class MAX7219
{
  public:
    MAX7219(int cs_pin);
    void on(void);
    void off(void);
    void initial(void);
    void single(int which_reg,int val);
    void show(long  num);
    void show____(void);
  private:
    int cs_pin;
    long count1 =0;
    long count2 = 0;
    int eight,seven,six,five,four,three,two,one;
    int eight_remainder,seven_remainder,six_remainder,five_remainder,four_remainder,three_remainder,two_remainder,one_remainder;
    
    //byte reg_num[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
};
#endif
