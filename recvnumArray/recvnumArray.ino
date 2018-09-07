#include <SPI.h>
#include <RF24.h>
#include <LiquidCrystal.h>
const int rs = 9, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

RF24 radio(7,8);
int i=0;
int A[50];
const int buzzer = 6;
const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  Serial.begin(9600);  
  Serial.println("--- Receiver at transformer ---");
  Serial.println();
  if(i<10){
    recv123();
  }
  ArrayComp();
  Serial.println("Wire cut at: Pole ");
  Serial.println(A[0]);
  
  
}

int recv123() {
    int text = 0;
    if (radio.available()) {
    radio.read(&text, sizeof(int));
    int transData = int(text);
    if (transData == 11) {
        tone(buzzer, 3000);
        A[i]=1;
        
        
        Serial.println(A[i]);
        i=i+1;
        lcd.print("pole 1 power cut");
        noTone(buzzer);
        delay(100);
      } 
  
    else if (transData == 12) {
        tone(buzzer, 2000);
        A[i]=2;
        
        Serial.println(A[i]);
        i=i+1;
        lcd.print("pole 2 power cut");
        delay(100);
        noTone(buzzer);
     }
    else if (transData == 13 ) {
        tone(buzzer, 700);
        A[i]="3";
        Serial.println(A[i]);
        i=i+1;
        lcd.print("pole 3 power cut");
        delay(100);
        noTone(buzzer);
       }
     return A;
     return i;
     }
   
    }
 int ArrayComp()
   {
    for(i=0;i<10;i++){
     if(A[i]>A[i+1]){
      int swap=A[i];
      A[i]=A[i+1];
      A[i+1]=swap;
    } 
   
    }
    return A[0]; 
   }
     
  
