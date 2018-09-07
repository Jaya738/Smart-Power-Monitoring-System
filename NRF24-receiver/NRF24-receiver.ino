#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);
int i=0;
String A[50];
const int buzzer = 2;
const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  Serial.begin(9600);  
  Serial.println("--- Receiver at transformer ---");
  Serial.println("NRF module");  
  Serial.println();
}

void loop() {
  char text[32] = "";
  
  if (radio.available()) {
    radio.read(&text, sizeof(text));
    String transData = String(text);
    if (transData == "1") {
        tone(buzzer, 1000);
        A[i]=transData;
        Serial.print(A[i]);
        i=i+1;
        Serial.println();
        delay(500);
        noTone(buzzer);
      } 
  
    else if (transData == "2") {
        tone(buzzer, 1000);
        A[i]=transData;
        Serial.print(A[i]);
        i=i+1;
        Serial.println();
        delay(500);
        noTone(buzzer);
     }
    else if (transData == "3") {
        tone(buzzer, 1000);
        A[i]=transData;
        Serial.print(A[i]);
        i=i+1;
        Serial.println();
        delay(500);
        noTone(buzzer);
     }
    }
     
  }
