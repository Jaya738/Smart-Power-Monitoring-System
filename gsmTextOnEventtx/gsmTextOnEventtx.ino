#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;
Servo myservo1;
int pos = 0;
int temp=0,j=0;
char str[15];
boolean power, lastState;
const int rs = 9, en = 10, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
RF24 radio(7,8);
const byte address[6] = "00001";
int i=0;
int A[10];
int count=0;

void setup()
{
  Serial.begin(9600);
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(1000);
  pinMode(2, INPUT_PULLUP);
  power = digitalRead(2);
  lastState = power;

  lcd.begin(16, 2);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  radio.startListening();
  Serial.begin(9600);  
  Serial.println("--- Receiver at transformer ---"); 
  Serial.println();
  lcd.print("AP ELECTROTHON");
                  //Function to detect pole data
  Serial.println("Hello servo");
  myservo.attach(A0);     //Servo to pull MCB UP
  myservo1.attach(A1);    //Servo to pull MCB down
 }

void loop()
{
  lastState = power;
  power = digitalRead(2);
  
  if ( power != lastState ) {
    Serial.println("Change in State");
    sendSMS();
  }
  if(temp==1)
  {
    check();
    temp=0;
    i=0;
    delay(1000);
  }
  recv123();
  delay(500);
}

void sendSMS() {
  Serial.println("AT+CMGS=\"+919966333721\"");
  
  delay(500);
  
  Serial.print("Power was turned ");
  Serial.println(power ? "on" : "off");
  Serial.write( 0x1a ); // ctrl+Z character
  
  delay(500);
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
      str[j++]=inChar;
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
  
    if(!(strncmp(str,"on",2)))
    {
      Serial.println("Servo on");
      myservo.write(180);
      delay(4000);
      myservo.write(0);
      delay(2000);
      myservo.write(90);
      delay(200);
    }  
   
    if(!(strncmp(str,"off",3)))
    {
      Serial.println("Servo off");
      delay(200);
      myservo.write(180);
      delay(4000);
      myservo.write(0);
      delay(2000);
      myservo.write(90);
      delay(200);
    }
}


void recv123() {
  
  Serial.println("collecting pole data");
  while(1){
      int text = 0;
    if (radio.available()) {
    radio.read(&text, sizeof(int));
    int transData = int(text);
    if (transData == 11) {
        A[i]=int(1);
       Serial.println(1);
        i=i+1;
      
        delay(100);
      } 
  
    else if (transData == 12) {
       
        A[i]=int(2);
        Serial.println(2);
        i=i+1;
        
        delay(100);
       
     }
    else if (transData == 13 ) {
       
        A[i]=int(3);
        Serial.println(3);
        i=i+1;
        delay(100);
   
       }
     }
     if(i==10){
      count=1;
      break;
     }
    }
    if(count==1){
    for(int j=0;j<10;j++){
      for(int k=j+1;k<10;k++){
         if(A[j]>A[k]){
            int swap=A[j];
            A[j]=A[k];
            A[k]=swap;
         } 
      }
    
    }
    Serial.println("power lost at");
    Serial.println(A[0]); 
    lcd.clear(); 
    lcd.print("pole:");
    lcd.print(A[0]);
    Serial.println("printing to LCD");
    delay(5000);
    
    
}
}

