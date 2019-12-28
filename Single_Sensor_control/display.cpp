#include "display.h"

MAX7219::MAX7219(int cs)
{
  pinMode(cs, OUTPUT);
  cs_pin = cs;
}
void MAX7219::on(void)
{
  digitalWrite(cs_pin, LOW);
//  delay(1);
  SPI.transfer(0x0C);
  SPI.transfer(0x01);
  digitalWrite(cs_pin, HIGH);
}
void MAX7219::off(void)
{
  digitalWrite(cs_pin, LOW);
//  delay(1);
  SPI.transfer(0x0C);
  SPI.transfer(0x00);
  digitalWrite(cs_pin, HIGH);
}
void MAX7219::show____(void)
{
  for(byte i=5;i<0x09;i++)
   {
   digitalWrite(cs_pin, LOW);
   delay(1);
   SPI.transfer(i);
   SPI.transfer(0x0A);
   digitalWrite(cs_pin, HIGH);
   delay(1);
   }
}
void MAX7219::initial(void)
{
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE0);
  SPI.begin();
  // Shutdown Register 0xXC 0/1
  digitalWrite(cs_pin, LOW);
  delay(1);
  SPI.transfer(0x0C);
  SPI.transfer(0x01);
  digitalWrite(cs_pin, HIGH);
  delay(1);
  //  Decode-Mode Code B 0x01
  digitalWrite(cs_pin, LOW);
  delay(1);
  SPI.transfer(0x09);
  SPI.transfer(0xFF);
  digitalWrite(cs_pin, HIGH);
  delay(1);
  // Intensity Register Format (Address (Hex) = 0xXA)亮度
  digitalWrite(cs_pin, LOW);
  delay(1);
  SPI.transfer(0x0A);
  SPI.transfer(0x09);
  digitalWrite(cs_pin, HIGH);
  delay(1);
  //  Scan-Limit Register Format (Address (Hex) = 0xXB)
  digitalWrite(cs_pin, LOW);
  delay(1);
  SPI.transfer(0x0B);
  SPI.transfer(0x07);
  digitalWrite(cs_pin, HIGH);
  delay(1);
  // Display-Test Register Format(Address (Hex) = 0xXF) 0/1
  digitalWrite(cs_pin, LOW);
  delay(1);
  SPI.transfer(0x0F);
  SPI.transfer(0x00);//0x00 Normal Operation;0x01 Display Test Mode
  digitalWrite(cs_pin, HIGH);
  delay(1);

   for(byte i=1;i<0x09;i++)
   {
   digitalWrite(cs_pin, LOW);
   delay(1);
   SPI.transfer(i);
   SPI.transfer(0x00);
   digitalWrite(cs_pin, HIGH);
   delay(1);
   }

}
void MAX7219::single(int which_reg, int val)
{
   //byte reg_num[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
  digitalWrite(cs_pin, LOW);
  SPI.transfer(reg_num[which_reg]);
  SPI.transfer(reg[val]);
  digitalWrite(cs_pin, HIGH);
}
void MAX7219::show(long num)
{
  //count++;
  // long ddd = 0;
  // long sss  = 0;
  // for(unsigned long i = 0;i<num;i++)
  // {
  // ddd++;
  // if(ddd>9999)
  // {
  // ddd =0;
  // sss++;
  // if(sss > 9999)
  // sss = 0;
  // }
  // }
  if (num > 9999)
  {
    count2 = num / 10000;
    count1 = num - (count2 * 10000);
  }
  else
  {
    count2 = count2;
    count1 = num;
  }
  // Serial.print("sss:");Serial.println(count2);
  // Serial.print("ddd:");Serial.println(count1);


  eight = count2 / 1000;
  eight_remainder = count2 % 1000;

  seven = eight_remainder / 100;
  seven_remainder = eight_remainder % 100;

  six = seven_remainder / 10;
  six_remainder = seven_remainder % 10;

  five = six_remainder;


  four = count1 / 1000;
  four_remainder  = count1 % 1000;

  three = four_remainder / 100;
  three_remainder = four_remainder % 100;

  two = three_remainder / 10;
  two_remainder = three_remainder % 10;

  one = two_remainder;

  digitalWrite(cs_pin, LOW);
  SPI.transfer(0x01);
  SPI.transfer(reg[one]);
  digitalWrite(cs_pin, HIGH);
  // delay(1);

  digitalWrite(cs_pin, LOW);
  SPI.transfer(0x02);
  SPI.transfer(reg[two]);
  digitalWrite(cs_pin, HIGH);
  // delay(1);

  digitalWrite(cs_pin, LOW);
  SPI.transfer(0x03);
  SPI.transfer(reg[three]);
  digitalWrite(cs_pin, HIGH);
  //delay(1);

  digitalWrite(cs_pin, LOW);
  SPI.transfer(0x04);
  SPI.transfer(reg[four]);
  digitalWrite(cs_pin, HIGH);
  //delay(1);

  digitalWrite(cs_pin, LOW);
  SPI.transfer(0x05);
  SPI.transfer(reg[five]);
  digitalWrite(cs_pin, HIGH);
  //delay(1);

  digitalWrite(cs_pin, LOW);
  SPI.transfer(0x06);
  SPI.transfer(reg[six]);
  digitalWrite(cs_pin, HIGH);
  //delay(1);

  digitalWrite(cs_pin, LOW);
  SPI.transfer(0x07);
  SPI.transfer(reg[seven]);
  digitalWrite(cs_pin, HIGH);
  //delay(1);

  digitalWrite(cs_pin, LOW);
  SPI.transfer(0x08);
  SPI.transfer(reg[eight]);
  digitalWrite(cs_pin, HIGH);
  //delay(1);

  //    delay(10);
}
