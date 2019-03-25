const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int  R  = 11;
const int  G  = 10;
const int  B  = 9;
const int buzz = 3;
void setup() {
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(R, OUTPUT);
  pinMode(buzz, OUTPUT);
}

void loop() {
  digitalWrite(R, LOW);
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  if(cm < 10){
    tone(buzz, 1000);
    digitalWrite(R, HIGH);
    delay(300);
  }
  noTone(buzz);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println("");
  delay(500);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
