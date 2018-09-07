#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  Serial.begin(9600);  
  Serial.println("--- Transmitter ---");
  Serial.println("NRF module");  
  Serial.println();
}

void loop() {
  const char text[] = "1";
  Serial.println("1");
  radio.write(&text, sizeof(text));
  delay(1000);
}
