#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7,8); 
int hallSensorPin = 2;         
int state = 0;     
const byte address[6] = "00001";     

void setup() {     
  pinMode(hallSensorPin, INPUT);
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
  state = digitalRead(hallSensorPin);
  if (state == HIGH) 
  { 
  const int text = 13;
  Serial.println("Pole 3");
  radio.write(&text, sizeof(int));
  delay(1000);       
  } 
 
}
