#include<LiquidCrystal.h>
LiquidCrystal LCD(12, 11, 5, 4, 3, 2);
const int LM_35 = A0;
int in_val = 0;
float temperature = 0;

void setup() {
  // put your setup code here, to run once:
  LCD.begin(16, 2);
  LCD.home();
  LCD.print("Temperature");
}

void loop() {
  in_val = analogRead(LM_35);
  temperature = (5.0 * in_val * 100.0) / 1024;
  LCD.setCursor(0, 1);
  LCD.print(temperature);
  LCD.setCursor(5, 1);
  LCD.print("C");
  delay(1000);
}
