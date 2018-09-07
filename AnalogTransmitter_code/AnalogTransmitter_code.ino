#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7,8); 
int AnalogPin =1;         
int state = 0;     
const byte address[6] = "00001";     

void setup() {     
  pinMode(AnalogPin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  Serial.begin(9600);  
  Serial.println("--- Transmitter ---");
  Serial.println("pole no");  
  Serial.println();     
}

void loop(){
  state = analogRead(AnalogPin);
  Serial.println(state);
  delay(500);
  if (state < 700) 
  { 
  const int text = 12;
  delay(100);
  radio.write(&text, sizeof(int));
  delay(50);       
  } 
 
}
