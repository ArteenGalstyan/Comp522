/*
 * Arteen Galstyan
 *
 * COMP 522 Embedded Systems
 * Project 1: PWM LED Dimmer w/ Analog Input
 *
 * created  08 Mar 2022
 * modified 18 Mar 2022
 */

// constants:
#define PIN_LED 2       // LED pin
#define PIN_ANALOG_IN 4 // Potentiometer input pin
#define CHN 0           // PWM channel

// variables:
int analogValue = 0; // analog input of potentiometer

//----------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  ledcSetup(CHN, 1000, 12); // set PWM settings
  ledcAttachPin(PIN_LED, CHN);
}

//----------------------------------------------------------------------------------
void loop()
{
  analogValue = map(analogRead(PIN_ANALOG_IN), 0, 4095, 0, 255); // map analog input to 0-255 range for PWM
  Serial.println(analogValue);
  ledcWrite(CHN, analogValue); // output PWM to LED pin
}
