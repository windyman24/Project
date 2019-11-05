#define ON LOW
#define OFF HIGH
bool raise_flag = false;
bool fall_flag = false;
long average_valuse = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(3,LOW);
  average();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (raise_flag == true && fall_flag == true)
  {
    Serial.println("凸");
    digitalWrite(8,OFF);
    send_pulse();
    raise_flag = false; 
    fall_flag = false;
  }
  else
  {
    if (analogRead(A0) < average_valuse-50)
    {
      Serial.println("<");
      digitalWrite(8,ON);
      fall_flag = true;
    }
    while (fall_flag == true && (analogRead(A0) >= average_valuse+10 ||analogRead(A0) <= average_valuse-10))
    {
      Serial.println("<>");
      raise_flag = true;
    }
  }
//     Serial.println(analogRead(A0));
    
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
