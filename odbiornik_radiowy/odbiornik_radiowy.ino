#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(A0, A1, 2, 3, 4, 5); //Informacja o podłączeniu nowego wyświetlacza
const int CE = 9;
const int CSN = 10;
RF24 radio(CE, CSN); //CE,CSN
float payload;
float text = 0.2;
const byte address[][6] = {"00001", "00002"};
const int fake_sig = 8;
const int echo = 7;
long czas;
float distance;

void setup() {

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Odleglosc:");
  lcd.setCursor(0, 1);
  lcd.print("0.00cm");

  Serial.begin(9600);
  radio.begin();
  radio.setPayloadSize(sizeof(payload));
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.setPALevel(RF24_PA_MIN);
  pinMode(fake_sig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  radio.startListening();
  while (!radio.available());
  unsigned long start_timer = micros();
  radio.read(&payload, sizeof(payload));
  unsigned long end_timer = micros();
  readUS();
  /*Serial.print("Received:");
    Serial.println(payload);
    Serial.print("Time: ");
    Serial.print(end_timer - start_timer);
    Serial.print("us.");
  */
  //delay(500);
}

void readUS() {
  digitalWrite(fake_sig, HIGH);
  delayMicroseconds(10);
  digitalWrite(fake_sig, LOW);
  czas = pulseIn(echo, HIGH);
  distance = 0.0344 * czas;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Odleglosc:");
  lcd.setCursor(0, 1);
  lcd.print(distance - 7);
  lcd.print(" cm");

  Serial.print(distance - 962 + 23);
  Serial.println(" cm");

}
