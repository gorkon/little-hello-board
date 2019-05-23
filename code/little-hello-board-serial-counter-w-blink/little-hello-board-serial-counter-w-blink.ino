/*

*/
#include <SoftwareSerial.h>

#define TX 2
#define RX 3

SoftwareSerial Serial(RX, TX);

#define leftLED 1
#define rightLED 0
#define timing 100
#define buttonPin 4

int counter = 0;
char val;
bool buttonState = 0; //store the button state
bool newData = false; //store whether there's new data from serial or not

void setup() {
  // put your setup code here, to run once:
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  //Serial.println("Starting serial communication...");
  Serial.print("Counter: "); Serial.println(counter);
  delay(200); //do I need this?
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(buttonPin);

  if (Serial.available() > 0 ) {  //if serial data is coming in
    val = Serial.read();        //store it in val
    newData = true;             //set newData flag
  }

  if (newData){
    if (val == 'L' || val == 'l'){  //'L' turns on left LED
      digitalWrite(leftLED, HIGH);
      digitalWrite(rightLED, LOW);
    }
    else if (val == 'R' || val == 'l'){   //'R' turns on right LED
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, HIGH);
    }
    else if (val == 'B' || val == 'b'){   //'B' turns on both LEDs
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, LOW);
    }
    else{                           //Any other value turns them both off
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, LOW);
    }
  }

  if (buttonState == LOW){      //button press increments counter and flashes each LED
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
