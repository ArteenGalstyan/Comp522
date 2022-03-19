## Project 1: LED dimmer with analog input

To output PWM signals on the esp32 WROVER module, you have to first setup the parameters of the PWM channel. In `setup()` configure a PWM channel and set the signal's frequency and precision. Then attach your desired GPIO pin to the PWM channel. Then in `loop()` you can set the desired duty cycle to be outputted.

```C
setup(
    ledcSetup(channel, frequency, bit_num); //setup pwm channel
    ledcAttachPin(pin, channel);  //attach led pin to pwm channel
)
loop(
    ledcWrite(channel, duty_cycle);   //write the pulse width value to pwm channel
)
```

The esp32 has a max bit precision of 31 bits (0 to 2^31-1). To calculate the max PWM frequency for a given bit precision, you must divide 80MHz by the bit precision. For example, an 8-bit precision has 255 possible values, so the maximum frequency you can run a PWM channel with 8-bit precision is 80,000,000/255 (312,500Hz). This is only an upper bound, you can always run the channel at a lower frequency.
