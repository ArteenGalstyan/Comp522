/*
 * Arteen Galstyan
 * 
 * COMP 522 Embedded Systems
 * Warmup Project 0
 * 
 * Examples used from Arduino's built in examples
 * - State Change Detection(for button press): https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection
 * - Blink Without Delay(for LED blinking): https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay
 * 
 * created  14 Feb 2022
 * modified 15 Feb 2022
 */


// constants:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int RESET = 4;         // number of presses that resets the frequency to 1Hz
const long interval = 1000;  // 1000 ms = 1 second

// variables:
int ledState = LOW;          // used to turn on/off the LED (starts OFF)
int buttonState = 0;         // used for reading the pushbutton status
int lastButtonState = 0;     // previous state of the button
int timeScale = 0;           // timescale (0 = 1Hz, 1 = 2Hz, 2 = 4Hz, ...)

unsigned long previousTime = 0; //used to store the last time the LED changed states

//----------------------------------------------------------------------------------
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

//----------------------------------------------------------------------------------
void loop() { 
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {

    // when button is pressed, change timescale
    if (buttonState == HIGH) {
      timeScale = (timeScale + 1) % RESET;
    }
    delay(10);
  }
  lastButtonState = buttonState; // save button state 

  // check to see if it is time to change the LED state(ON/OFF)
  unsigned long currentTime = millis();
  
  if (currentTime - previousTime >= (interval/pow(2,timeScale))){
    
    previousTime = currentTime; // save current time
    
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    
    digitalWrite(ledPin, ledState); // set the LED's new state
  }
}
