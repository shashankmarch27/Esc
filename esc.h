#ifndef ESC_H
#define ESC_H
#include <Arduino.h>

#define MODE_3D true

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
    int mid_value;
    int max_value;
    bool mode;
    protocol protocol_t;

public:

    esc(int pin, protocol protocol, bool mode = false);

    void init();
    void write(float value);
};

#endif