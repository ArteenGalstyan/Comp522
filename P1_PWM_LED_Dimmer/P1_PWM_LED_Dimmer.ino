/*
 * Arteen Galstyan
 *
 * COMP 522 Embedded Systems
 * Project 1
 *
 * Examples used from Arduino's built in examples:
 * 
 *
 * created  08 Mar 2022
 * modified 08 Mar 2022
 */

// constants:

#define PIN_LED       2
#define PIN_ANALOG_IN 4
#define CHN           0


// variables:
int analogValue = 0;

//----------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  ledcSetup(CHN, 1000, 12);
  ledcAttachPin(PIN_LED, CHN);
}

//----------------------------------------------------------------------------------
void loop()
{
   analogValue = map(analogRead(PIN_ANALOG_IN), 0, 4095, 0, 255);
   Serial.println(analogValue);
   ledcWrite(CHN,analogValue);
}
