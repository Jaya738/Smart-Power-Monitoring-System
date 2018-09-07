#include <SoftwareSerial.h>
#include <Wire.h>
int temp=0,i=0;
int led=13;
String msg;
char str[15];
void setup()
{
  SendMessage("Transmitted");
  Serial.begin(9600);
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(1000);
 
}

void loop()
{
if(temp==1)
  {
    check();
    temp=0;
    i=0;
    delay(1000);
  }
  
}
void SendMessage(String msg)
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+919966333721\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println(msg);
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void serialEvent() 
 {
  while(Serial.available()) 
  {
    if(Serial.find("#"))
    {
      while (Serial.available()) 
      {
      char inChar=Serial.read();
      str[i++]=inChar;
      if(inChar=='*')
      {
        temp=1;
        return;
      } 
      } 
    }
   }
   
 }

void check()
{
  
   if(!(strncmp(str,"ON",6)))
    {
      
      SendMessage("Transformer is ON");

      delay(200);
    }  
   
    else if(!(strncmp(str,"OFF",9)))
    {
      SendMessage("Transformer is OFF");
      delay(200);
    }    
}

