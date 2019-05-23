/*

*/
#include <SoftwareSerial.h>

#define TX 3
#define RX 2

SoftwareSerial Serial(RX, TX);

#define leftLED 1
#define rightLED 0
#define timing 100
#define buttonPin 4

int counter = 0;
bool buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Starting serial communication...");
  Serial.print("Counter: "); Serial.println(counter);
  delay(200); //do I need this?
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW){
    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, LOW);
    delay(timing);
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, HIGH);
    delay(timing);
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
    counter++;
    Serial.print("Counter: "); Serial.print(counter); Serial.println("");
  }
}
