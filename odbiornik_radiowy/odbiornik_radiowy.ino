#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int CE = 9;
const int CSN = 10;
RF24 radio(CE, CSN); //CE,CSN
float payload;
float text = 0.2;
const byte address[][6] = {"00001", "00002"};
const int us_sig = 8;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPayloadSize(sizeof(payload));
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  radio.startListening();
  while (!radio.available());
  radio.read(&payload, sizeof(payload));
  Serial.print("Received:");
  Serial.println(payload);
  delay(5);
  radio.stopListening();
  unsigned long start_timer = micros();
  bool report=radio.write(&text,sizeof(float));
  unsigned long end_timer = micros();
  Serial.print("Time: ");
  Serial.print(end_timer-start_timer);
  Serial.print("us. Sent:");
  Serial.println(text);  
  delay(1000);
}
