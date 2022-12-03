#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int CE=6;
const int CSN=7;
RF24 radio(CE,CSN); //CE,CSN
float payload=0.1;
uint8_t address[][6] = { "1Node", "2Node" };
const int us_sig=8;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPayloadSize(sizeof(payload));
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  unsigned long start_timer=micros();
  bool report=radio.write(&payload,sizeof(float));
  unsigned long end_timer = micros();  
  Serial.print("Time: ");
  Serial.print(end_timer-start_timer);
  Serial.print("us. Sent:");
  Serial.println(payload);
  delay(50);
  tone(us_sig,40000);
  delayMicroseconds(500);
  noTone(us_sig);
  delay(1000);
}
