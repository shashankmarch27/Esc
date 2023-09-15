#ifndef ESC_H
#define ESC_H
#include <Arduino.h>

enum protocol{
    PWM,
    FAST_PWM,
    ONESHOT125,
    ONESHOT42,
    MULTISHOT
};

class esc{

private:
    int channel;
    int frequency;
    int pin;
    int min_value;
    int max_value;

public:

    esc(int pin, enum protocol);

    void init();
    void write(float value);
};

#endif