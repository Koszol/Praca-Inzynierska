int val = 0;
const int us_sig = 8;
long czas;
float distance;
void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
}

void loop() {
  /*
    noInterrupts();
    unsigned long start_time=micros();
    sendUS();
    interrupts();
    delayMicroseconds(200);
    while(val<490){
    val=analogRead(A0);
    }
    unsigned long end_time=micros();
    Serial.println(end_time-start_time);
    delay(1000);
  */
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  czas=pulseIn(6,HIGH);
  distance=0.0344*czas;
  Serial.println(distance);
  delay(500);
}
