/*
 * Arteen Galstyan
 * Jacob Hagen
 *
 * COMP 522 Embedded Systems
 * Do a thing!
 *
 * Examples used from Freenove built in examples
 * - LCD Display (Sketch 20.1): https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_ESP32/tree/master/C/Sketches
 * - MPU6050 sensor (Sketch 26.1): https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_ESP32/tree/master/C/Sketches
 *
 * created  07 May 2022
 * modified 10 May 2022
 */

#include <LiquidCrystal_I2C.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

// Pinout definitions
#define SDA 13
#define SCL 14

#define BLUE_LED 15
#define RED_LED 4
#define INTERRUPT_DRIVER 19
#define INTERRUPT_PIN 18

// variables
int16_t az, gz;
float calc;
long timer = 0;

/*
 * note: If lcd1602 uses PCF8574T, IIC's address is 0x27,
 *       or lcd1602 uses PCF8574AT, IIC's address is 0x3F.
 *       0x68
 */
LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 mpu6050(Wire);

void setup()
{
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(INTERRUPT_DRIVER, OUTPUT);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  digitalWrite(INTERRUPT_DRIVER, HIGH);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), upsideDown, FALLING);
  // attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), rightsideUp, RISING);
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  Wire.begin(SDA, SCL);
  lcd.init();          // LCD driver initialization
  lcd.backlight();     // Turn on the backlight
  lcd.setCursor(0, 0); // 2x16 Display (0,0) is the beginning
  lcd.print("Calibrating...");
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  lcd.setCursor(0, 0);
  lcd.print("Calibration done");
  delay(2000);
  lcd.clear();
}

void loop()
{
  if (millis() - timer > 350) // Update + Frame Rate
  {
    mpu6050.update();
    getMotion();
    calc = (float)az / 16384;
    timer = millis();
    if ((calc < 0) && (digitalRead(INTERRUPT_PIN) == HIGH))
    {
      digitalWrite(INTERRUPT_DRIVER, LOW);
      printMessage(0);
    }
    else if (calc > 0)
    {
      digitalWrite(INTERRUPT_DRIVER, HIGH);
      rightsideUp();
      printMessage(1);
    }
    lcd.setCursor(1, 0);
    lcd.print(calc);
  }
}

void printMessage(int option)
{
  lcd.clear();
  lcd.setCursor(0, 1);
  if (option)
  {
    lcd.print("Hello :)");
  }
  else
  {
    lcd.print("Help I've Fallen");
  }
}

void upsideDown()
{
  digitalWrite(RED_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
}

void rightsideUp()
{
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
}

void getMotion(void)
{
  az = mpu6050.getRawAccZ();  // gain the values of Z axis acceleration raw data
  gz = mpu6050.getRawGyroX(); // gain the values of Z axis Gyroscope raw data
}
