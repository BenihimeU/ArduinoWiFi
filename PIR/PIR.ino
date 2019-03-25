const int pir = 8;
const int LED = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(pir, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pirValue = digitalRead(pir);
  Serial.print(pirValue);
  if ( pirValue == HIGH) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  delay(1000);
}
