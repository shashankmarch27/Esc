#include "esc.h"
#define RESOLUTION 10

int counter = 1;

esc::esc(int pin, protocol protocol_t){
    this->pin = pin;
    switch (protocol_t){
    case PWM:
        frequency = 50; // 20ms
        min_value = 51; // 1ms
        max_value = 103; // 2ms
        break;
    
    case FAST_PWM:
        frequency = 400; // 2.5ms
        min_value = 20; // 1ms
        max_value = 40; // 2ms
        break;

    case ONESHOT125:
        frequency = 2000; // 500 us
        min_value = 255; // 125 us
        max_value = 512; // 250 us
        break;

    case ONESHOT42:
        frequency = 10000; // 100 us
        min_value = 429; // 42 us
        max_value = 860; // 84 us
        break;

    case MULTISHOT:
        frequency = 25000; // 40us
        min_value = 128;
        max_value = 640;
        break;

    default:
        break;
    }

    channel = counter;
    counter++;
}

void esc::init(){
    ledcSetup(channel,frequency, RESOLUTION);
    ledcAttachPin(pin,channel);
    ledcWrite(channel,min_value);
}

void esc::write(int value){
    ledcWrite(channel,map(value,0,1023,min_value,max_value));
}
