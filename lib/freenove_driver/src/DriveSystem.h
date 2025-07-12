#include "Motor.h"
#include <utility>


class DriveSystem {
    public:
        DriveSystem(
            Motor right_rear_motor,
            Motor right_front_motor,
            Motor left_front_motor,
            Motor left_rear_motor    
        );

        void set_speed(float linear, float angular);
        static constexpr float max_speed = Motor::max_speed;
        
    private:
        std::pair<float, float> scale_velocities(float v_left_wheel, float v_right_wheel);
        Motor _right_rear_motor;
        Motor _right_front_motor;
        Motor _left_front_motor;
        Motor _left_rear_motor;
        static constexpr float wheelbase = 0.15;

};