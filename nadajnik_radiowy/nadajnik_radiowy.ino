#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int CE = 9;
const int CSN = 10;
RF24 radio(CE, CSN); //CE,CSN
float payload = 0.1;
float text;
const byte address[][6] = {"00001", "00002"};
const int us_sig = 8;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPayloadSize(sizeof(payload));
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);
  radio.setPALevel(RF24_PA_MIN);
  pinMode(us_sig, OUTPUT);
}

void loop() {
  radio.stopListening();
  unsigned long start_timer = micros();
  radio.write(&payload, sizeof(float));
  unsigned long end_timer = micros();
  delayMicroseconds(68);
  sendUS();
  Serial.print("Time: ");
  Serial.print(end_timer - start_timer);
  Serial.print("us. Sent:");
  Serial.println(payload);


  delay(1000);
}

void sendUS() {
  digitalWrite(us_sig, HIGH);
  delayMicroseconds(10);
  digitalWrite(us_sig, LOW);
}
