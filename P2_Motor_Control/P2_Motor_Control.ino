/*
 * Arteen Galstyan
 * Jacob Hagen
 *
 * COMP 522 Embedded Systems
 * Project 2: Motor Control w/ Interrupts
 *
 * created  12 Apr 2022
 * modified 15 Apr 2022
 */

#define IN1_PIN 19
#define IN2_PIN 15

int outPorts[] = {14, 27, 26, 25};
volatile int currentState = 1;
volatile int savedState = 1;
enum state
{
    STOPPED,
    SPEED_1,
    SPEED_2,
    SPEED_3,
    SPEED_4
};

void setup()
{
    for (int i = 0; i < 4; i++)
    {
        pinMode(outPorts[i], OUTPUT);
    }

    // interrupt pins
    pinMode(IN1_PIN, INPUT);
    pinMode(IN2_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(IN1_PIN), in1Routine, RISING);
    attachInterrupt(digitalPinToInterrupt(IN2_PIN), in2Routine, RISING);
    Serial.begin(9600);
}
void loop()
{
    switch (currentState)
    {
    case 1:
        break;
    case 2:
        moveOneStep(true);
        delay(20);
        break;
    case 3:
        moveOneStep(true);
        delay(12);
    case 4:
        moveOneStep(true);
        delay(6);
    case 5:
        moveOneStep(true);
        delay(3);
        break;
    }
}

void in1Routine()
{
    Serial.println("In 1");
    if (currentState == 1 && savedState == 1) // if STOPPED and no speed set
    {
        currentState++;
    }
    else if (currentState == 1 && savedState != 1) // if STOPPED and speed set
    {
        currentState = savedState;
    }
    else if (currentState < 5) // increase speed
    {
        currentState++;
    }
}

void in2Routine()
{

    Serial.println("In 2");
    if (currentState != 1) // if not STOPPED, save speed and stop
    {
        savedState = currentState;
        currentState = 1;
    }
    else
    { // set speed to saved value
        savedState = 1;
    }
}

void moveOneStep(bool dir)
{
    // Define a variable, use four low bit to indicate the state of port
    static byte out = 0x01;
    // Decide the shift direction according to the rotation direction
    if (dir)
    { // ring shift left
        out != 0x08 ? out = out << 1 : out = 0x01;
    }
    else
    { // ring shift right
        out != 0x01 ? out = out >> 1 : out = 0x08;
    }
    // Output singal to each port
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
    }
}