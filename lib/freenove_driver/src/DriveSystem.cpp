#include "DriveSystem.h"
#include <cmath>

#define DEG2RAD M_PI/180.f

DriveSystem::DriveSystem(
    Motor right_rear_motor,
    Motor right_front_motor,
    Motor left_front_motor,
    Motor left_rear_motor
) :
    _right_rear_motor(right_rear_motor),
    _right_front_motor(right_front_motor),
    _left_front_motor(left_front_motor),
    _left_rear_motor(left_rear_motor)
{}

void DriveSystem::set_speed(float linear, float angular){
    
    // Apply motor velocities such that system moves 
    // with forward velocity "linear" (m/s) and
    // angular velocity "angular" (rad/s).
    // Forward velocity will be limited if required to
    // prevent exceeding motor speed limits.

    float v_l, v_r; // left and right side velocities. 

    // if angular vel less than 5 degrees per sec, treat as 
    // straight line driving
    // (special case required to avoid divide-by-zero in curvature calculations)
    
    bool driving_straight = abs(angular) < 5*DEG2RAD;
    if (driving_straight)
    {
       // left and right wheel velocities are the same
        v_l = linear;
        v_r = linear;
    }
 
    else {
        // kinematic model:
        // Just treating as two wheel diff drive, and assigning the output to both
        // wheels on the corresponding side.
        // Calculate radius of curvature for centre wheel (v/w).
        // Use wheelbase to calculate radius of curvature for each
        // wheel.
        // Use wheel radius to calculate wheel velocity 

        float r_c = linear / angular;   // radius of curvature - robot centre
        float r_l = r_c - wheelbase/2;  // radius of curvature - left wheel
        float r_r = r_c + wheelbase/2;  // radius of curvature - right wheel
        v_l = r_l * angular;            // left wheel velocity
        v_r = r_r * angular;            // right wheel velocity
    }



    // scale velocities down if needed to avoid exceeding vel limits
    auto [scaled_v_l, scaled_v_r] = scale_velocities(v_l, v_r);
    v_l = scaled_v_l;
    v_r = scaled_v_r;

    // apply velocities to motors
    _left_front_motor.set_speed(v_l);
    _left_rear_motor.set_speed(v_l);
    _right_rear_motor.set_speed(v_r);
    _right_front_motor.set_speed(v_r);
}

std::pair<float, float> DriveSystem::scale_velocities(float v_left_wheel, float v_right_wheel){
    // Given wheel velocities, scale down as necessary such that:
    // * neither wheel absolute vel exceeds motor speed limits
    // * radius of curvature is unchanged

    float scale_factor;

    if (v_left_wheel == 0 && v_right_wheel == 0){
        // avoid division by zero 
        scale_factor = 1.0;
    }                
    else {
        scale_factor = max_speed / max(abs(v_left_wheel), abs(v_right_wheel));
    }
    
    if (scale_factor > 1){
        // only scale down (reduce speed), not up
        scale_factor = 1.0;
    }
    
    return {v_left_wheel * scale_factor, v_right_wheel * scale_factor};
}
