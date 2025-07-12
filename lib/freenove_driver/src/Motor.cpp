#include "Motor.h"

Motor::Motor(Adafruit_PWMServoDriver& pwm_driver, int fwd_channel, int bkwd_channel):
    _pwm_driver(pwm_driver), _fwd_channel(fwd_channel), _bkwd_channel(bkwd_channel) {}

void Motor::set_speed(float speed){
    int fwd_duty, bkwd_duty;

    int duty = abs(speed * speed_scale);
    duty = min(duty, max_duty);

    if (speed > 0) {
        fwd_duty = duty;
        bkwd_duty = 0;
    }
    else {
        fwd_duty = 0;
        bkwd_duty = duty;
    }

    _pwm_driver.setPin(_fwd_channel, fwd_duty);
    _pwm_driver.setPin(_bkwd_channel, bkwd_duty);
}