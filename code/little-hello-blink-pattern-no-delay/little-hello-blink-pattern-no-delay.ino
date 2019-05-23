/*
  Blink Pattern without Delay
  
  Heavily Modified from Arduino Example Code from:
  http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 4;    // the number of the pushbutton pin
const int leftLED =  1;      // the number of the red LED pin
const int rightLED = 0;     // the number of the green LED pin

const long long_interval = 1000;    // long interval at which to blink (milliseconds)
const long short_interval = 100;    // short interval at which to blink (milliseconds)
const long micro_interval = 50;     // very short interval at which to blink (ms)

// variables will change:
int buttonState = 0;        // variable for reading the pushbutton status
int blinkNum = 0;           // variable to store the current blink pattern
int leftState = LOW;         // leftState used to set the red LED
int rightState = LOW;       // rightState used to set the red LED
int counter = 0;            // a counter variable for blinkN()
int sosCounter = 0;         // a counter var for sos()

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis = 0;        // will store the current time
long timer = 0;                         // for incrementing the delay speed
unsigned long default_timer = 1000;     // stores default timer value
unsigned long decrement = 100;          // stores the timer decrement value

// the setup function runs once when you power the board
void setup() {
  // initialize digital pins 7 & 8 as an output.
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  //initialize digital pin 3 as input.
  pinMode(buttonPin, INPUT_PULLUP);
}

//turns both LEDs off
void bothOff(){
  rightState = LOW;
  leftState = LOW;
  
  digitalWrite(rightLED, rightState);
  digitalWrite(leftLED, leftState);
}

//turns both LEDs on
void bothOn(){
  rightState = HIGH;
  leftState = HIGH;
  
  digitalWrite(rightLED, rightState);
  digitalWrite(leftLED, leftState);
}

//blinks both LEDs together with interval t
void blinkTogether(long t){
  
  if (t <= 0){     // if given a negative or zero interval, turn off both LEDs and end the function call
    bothOff();
    return;
  }

  currentMillis = millis();

  if (currentMillis - previousMillis >= t) {
    previousMillis = currentMillis;

    if (leftState == LOW)
      bothOn();
    else
      bothOff();
  }

  return;
  
}

//alternates the Red and Green LEDs with a time interval of t
void alternate(long t){
  
  if (t <= 0){     // if given a negative or zero interval, turn off both LEDs and end the function call
    bothOff();
    return;
  }
  
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  currentMillis = millis();

  if (currentMillis - previousMillis >= t) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the red LED is off turn it on and vice-versa:
    if (leftState == LOW) {
      leftState = HIGH;
      rightState = LOW;
    } else {
      leftState = LOW;
      rightState = HIGH;
    }

    // set the LEDs with the states:
    digitalWrite(leftLED, leftState);
    digitalWrite(rightLED, rightState);
  }
}

// blinks green n times for t time and then blinks red once for t time
void blinkN(int n, int t){
  if (n <= 0){     // if given a negative or zero interval, turn off both LEDs and end the function call
    bothOff();
    return;
  }

  currentMillis = millis();


  //check if it's time to change the blink state
  if (currentMillis - previousMillis >= t){
    previousMillis = currentMillis;
    
    //check if it's time to blink green or red, after blinking increment counter
    if (counter < n){
      if (rightState == LOW){
        rightState = HIGH;
        leftState = LOW;
        counter++;
      }
      else{
        rightState = LOW;
        leftState = LOW;
      }
    }
    else{
      if (rightState == HIGH && leftState == LOW){
        rightState = LOW;
        leftState = LOW;
      }
      else if (rightState == LOW && leftState == LOW){
        rightState = LOW;
        leftState = HIGH;
      }
      else{
        rightState = LOW;
        leftState = LOW;
        counter = 0;
      }
    }
  }

  digitalWrite(rightLED, rightState);
  digitalWrite(leftLED, leftState);
  
}


void sos(){
  int s = 125;  //short blink interval for s
  int l = 333;  //long blink interval for o
  
  currentMillis = millis();

  //if sosCounter is 0, 1, 2 || 6, 7, 8
  if ((sosCounter >= 0 && sosCounter <= 2) || (sosCounter >= 6 && sosCounter <=8)){
    if (currentMillis - previousMillis >= s){
      previousMillis = currentMillis;
      if (rightState == LOW){
        rightState = HIGH;
        leftState = LOW;
      }
      else{
        rightState = LOW;
        leftState = LOW;
        sosCounter++;
      }
    }
  }
  else if (sosCounter >= 3 && sosCounter <= 5){
    if (currentMillis - previousMillis >= l){
      previousMillis = currentMillis;
      if (leftState == LOW){
        leftState = HIGH;
        rightState = LOW;
      }
      else{
        leftState = LOW;
        rightState = LOW;
        sosCounter++; 
      }
    }
  }
  else{
    if (currentMillis - previousMillis >= 2*l){
      previousMillis = currentMillis;
      sosCounter = 0;
    }
  }

  digitalWrite(rightLED, rightState);
  digitalWrite(leftLED, leftState);
}


// function to call blink functions dependent on blinkNum
void blinkPattern(int n){
  switch (n){
    case 0:
      bothOff();
      break;
    case 1:
      bothOn();
      break;
    case 2:
      blinkTogether(long_interval);
      break;
    case 3:
      blinkTogether(short_interval);
      break;
    case 4:
      blinkTogether(micro_interval);
      break;
    case 5: 
      alternate(long_interval);
      break;
    case 6:
      alternate(short_interval);
      break;
    case 7:
      alternate(micro_interval);
      break;
    case 8:
      blinkN(2, 200);
      break;
    case 9:
      blinkN(3, 150);
      break;
    case 10:
      sos();
      break;
    default:
      bothOff();
      blinkNum = 0;
  }
}

void loop() {
  //complex blinkPattern program
  
  //read the state of the pushbutton value
  buttonState = digitalRead(buttonPin);
  
  //check if the pushbutton is pressed, if it is, increment blinkNum by 1
  if (buttonState == LOW){
    bothOff();      //turn off both LEDs
    delay(250);     // delay allows user to push button for up to 250ms and release
    if (blinkNum < 10){
      blinkNum++;
    }  
    else
      blinkNum = 0; 
  }

  blinkPattern(blinkNum);

//
////Simple Blink program
//  bothOn();
//  delay(250);
//  bothOff();
//  delay(250);

  
}
