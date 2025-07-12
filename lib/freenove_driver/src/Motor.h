#pragma once

#include <Adafruit_PWMServoDriver.h>



class Motor {
    public:
        Motor(Adafruit_PWMServoDriver& pwm_driver, int fwd_channel, int bkwd_channel);
        void set_speed(float speed);        
        static constexpr float max_speed = 0.4;
        
    private:
        Adafruit_PWMServoDriver& _pwm_driver;
        int _fwd_channel;
        int _bkwd_channel;

        static constexpr int max_duty = 4095;
        static constexpr float speed_scale = max_duty / max_speed;
};