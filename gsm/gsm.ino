#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);  
  delay(100);
}


void loop()
{
  if (mySerial.available()>0)
  {
   switch(Serial.read())
  {
    case 's':
    Serial.println("Send press.0");
      SendMessage();
      
      break;
    case 'r':
      RecieveMessage();
      break;
  }
  }
 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919966333721\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CMGF=1");
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
