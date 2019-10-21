#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>
#include "sensor.h"
#include "Light_indication.h"

#define check_connect_time 5000
#define send_keeplive_time 1000

Light_Sensor sensor(2, 5, 6);
Light_indication Light_indication(8);

unsigned long check_connect_previousMillis = 0;
unsigned long send_keeplive_previousMillis = 0;

int Sensor1PushCounter = 0;
int Sensor1_State = 1;
int lastSensor1_State = 1;
unsigned long Sensor1_previousMillis = 0;
const long Sensor1_interval = 100;

int Sensor2PushCounter = 0;
int Sensor2_State = 1;
int lastSensor2_State = 1;
unsigned long Sensor2_previousMillis = 0;
const long Sensor2_interval = 100;

int Sensor3PushCounter = 0;
int Sensor3_State = 1;
int lastSensor3_State = 1;
unsigned long Sensor3_previousMillis = 0;
const long Sensor3_interval = 100;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};//change this MAC Address the last byte 21->E1,22->E2,,23->E3,24->E4
IPAddress ip(192, 168, 2, 169);
IPAddress myDns(192, 168, 2, 1);
IPAddress gateway(192, 168, 2, 254);
IPAddress subnet(255, 255, 255, 0);
EthernetServer server(8000);// telnet defaults to port 8000
//IPAddress ip(10, 0, 0, 22);
//IPAddress myDns(10, 0, 0, 10);
//IPAddress gateway(10, 0, 0, 10);
//IPAddress subnet(255, 255, 255, 0);
EthernetClient clients;
unsigned long previousMillis = 0;
String S1data = "S11";
String S2data = "S21";
String S3data = "S31";
bool keep_live_flag = true;
void Ethernet_init(void);
bool connect_flag = 0;
void setup()
{
  Serial.begin(115200);
  Serial.println("Restart");
  Ethernet_init();
  wdt_enable(WDTO_8S);

}
void loop()
{
  EthernetClient newClient = server.accept();
  if (newClient) {
    if (!clients) {
      Light_indication.connect();
      clients = newClient;
      connect_flag = true;
    }
  }
  while (connect_flag)
  {
    Sensor1_State = sensor.ReadSensor1_D();
    Sensor2_State = sensor.ReadSensor2_D();
    Sensor3_State = sensor.ReadSensor3_D();
    keeplive();
    check_connect();
    Light_indication.work();
    check_sensors();
  }
}
void check_sensors()
{
  //  clients.println("S11"+String(sensor.ReadSensor1_A()));
  //  clients.println("S21"+String(sensor.ReadSensor2_A()));
  //  clients.println("S31"+String(sensor.ReadSensor3_A()));
  unsigned long currentMillis = millis();
  if (Sensor1_State != lastSensor1_State) {
    // if the state has changed, increment the counter
    if (Sensor1_State == LOW) {
      currentMillis = millis();
      if (currentMillis - Sensor1_previousMillis >= Sensor1_interval)
      {
        currentMillis = millis();
        Sensor1_previousMillis = currentMillis;
        clients.println(S1data + String(sensor.ReadSensor1_A()));
        //        Serial.println(S1data+String(sensor.ReadSensor1_A()));
      }
    }
    else
    {

    }
    // Delay a little bit to avoid bouncing
    //    delay(1);
  }
  // save the current state as the last state, for next time through the loop
  lastSensor1_State = Sensor1_State;

  //s2
  if (Sensor2_State != lastSensor2_State) {
    // if the state has changed, increment the counter
    if (Sensor2_State == LOW) {
      currentMillis = millis();
      if (currentMillis - Sensor2_previousMillis >= Sensor2_interval)
      {
        currentMillis = millis();
        Sensor2_previousMillis = currentMillis;
        clients.println(S2data + String(sensor.ReadSensor2_A()));
        //        Serial.println(S2data+String(sensor.ReadSensor2_A()));
        //        Serial.println("S2 on");
      }
    }
    // Delay a little bit to avoid bouncing
    //    delay(1);
  }
  // save the current state as the last state, for next time through the loop
  lastSensor2_State = Sensor2_State;

  //s3
  if (Sensor3_State != lastSensor3_State) {
    // if the state has changed, increment the counter
    if (Sensor3_State == LOW) {
      if (currentMillis - Sensor3_previousMillis >= Sensor3_interval)
      {
        currentMillis = millis();
        Sensor3_previousMillis = currentMillis;
        clients.println(S3data + String(sensor.ReadSensor3_A()));
      }
    }
    //    delay(1);
  }
  // save the current state as the last state, for next time through the loop
  lastSensor3_State = Sensor3_State;
}
void Ethernet_init()
{
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields
  // initialize the Ethernet device
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  // Open serial communications and wait for port to open:
  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    //    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    Light_indication.disconnect();
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
      wdt_reset();
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    //    Serial.println("Ethernet cable is not connected.");
    Light_indication.disconnect();
  }
  else
  {

  }

  // start listening for clients
  server.begin();
  Light_indication.connect();
}
int wait_flag = 0;
int wait_to_restart = 0;
int no_response = 0;
void keeplive()
{
  unsigned long currentMillis = millis();
  if (currentMillis - send_keeplive_previousMillis >= send_keeplive_time)
  {
    send_keeplive_previousMillis = currentMillis;
    //Serial.println("Enter Keeplive time for check ");
    if (no_response == 0)
    {
      send_keeplive_previousMillis = currentMillis;
      clients.println("S000000");
//      wdt_reset();
    }
  }
}
void check_connect()
{
  unsigned long currentMillis = millis();
  if (currentMillis - check_connect_previousMillis >= check_connect_time)
  {
    check_connect_previousMillis = currentMillis;
    if (clients && clients.available() > 0)
    {
      wait_to_restart = 0;
      // read bytes from a client
      byte buffer[2];
      clients.read(buffer, 2);
      //Serial.println("Recive:A");
      //Serial.println("wait_flag = 0");
//      if (buffer[0] == 'A')
//      {
        wait_flag = 0;
        no_response = 0;
        keep_live_flag = true;
        clear_recive_buf();
        wdt_reset();
//      }

    }
    else if (!clients.connected())
    {
      //Serial.println("!clients.connected()");
      connect_flag = false;
      clients.stop();
      Light_indication.disconnect();

    }
    else
    {
      wait_to_restart++;
      //Serial.print("wait_to_restart:");
      //Serial.println(wait_to_restart);
      if (wait_to_restart > 10)
      {
        clients.stop();
        Ethernet.begin(mac, ip, myDns, gateway, subnet);
        clients.stop();
        Light_indication.disconnect();
        wait_to_restart = 0;
        connect_flag = false;
        no_response = 1;
      }
    }
  }
}
void clear_recive_buf()
{
  while (clients.available() > 0)
  {
    clients.read();
  }
}
