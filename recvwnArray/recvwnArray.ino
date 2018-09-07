#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>

const int rs = 9, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

RF24 radio(7,8);
int i=0;
int A[10];
int count=0;
const int buzzer =6;
const byte address[6] = "00001";

void setup() {
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
  lcd.print("AP ELECTROTHON");
  recv123();
  
} 

void recv123() {
  Serial.println("Hello");
  while(1){
      int text = 0;
    if (radio.available()) {
    radio.read(&text, sizeof(int));
    int transData = int(text);
    if (transData == 11) {
        tone(buzzer, 1500);
        A[i]=int(1);
       Serial.println(1);
        i=i+1;
        
        noTone(buzzer);
        delay(100);
      } 
  
    else if (transData == 12) {
        tone(buzzer, 2000);
        A[i]=int(2);
        Serial.println(2);
        i=i+1;
        
        delay(100);
        noTone(buzzer);
     }
    else if (transData == 13 ) {
        tone(buzzer, 700);
        A[i]=int(3);
        Serial.println(3);
        i=i+1;
        delay(100);
        noTone(buzzer);
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


 void loop() {
    
  }


