#include "esc.h"
#define RESOLUTION 10

#if defined(ESP32)
int counter = 1;
#endif

esc::esc(int pin, protocol protocol_t ,bool mode){
    this->pin = pin;
    this->mode = mode;
    this->protocol_t = protocol_t;

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
        min_value = 128; // 5us
        max_value = 640; // 25us
        break;

    default:
        break;
    }

    mid_value = (min_value + max_value) / 2;

    #if defined(ESP32)
    channel = counter;
    counter++;
    #endif
}

void esc::init(){
    #if defined(ESP32)
    ledcSetup(channel,frequency, RESOLUTION);
    ledcAttachPin(pin,channel);
    if(mode && (protocol_t == ONESHOT125)){
        ledcWrite(channel,mid_value);
    }
    else{
        ledcWrite(channel,min_value);
    }
    
    #elif defined(STM32F4xx)
    pinMode(pin,OUTPUT);
    analogWriteResolution(RESOLUTION);
    #endif
}

void esc::write(float value){
    #if defined(ESP32)
    ledcWrite(channel,constrain(map(value,0,1023,min_value,max_value),min_value,max_value));

    #elif defined(STM32F4xx)
    analogWriteFrequency(frequency);
    analogWrite(pin,constrain(map(value,0,1023,min_value,max_value),min_value,max_value));
    #endif
}
