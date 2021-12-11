#include <Arduino.h>
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(21, OUTPUT);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("loop...");
  digitalWrite(21, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(21, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
}