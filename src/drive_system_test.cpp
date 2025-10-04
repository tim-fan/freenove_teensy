#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <Motor.h>
#include <DriveSystem.h>
#include <cmath>

#define DEG2RAD M_PI/180.f

Adafruit_PWMServoDriver pwm_driver = Adafruit_PWMServoDriver();

DriveSystem drive_system(
    Motor(pwm_driver, 0, 1), // right rear
    Motor(pwm_driver, 2, 3), // right front
    Motor(pwm_driver, 5, 4), // left front
    Motor(pwm_driver, 6, 7) // left rear
);

void setup() {
  Serial.begin(9600); // Start serial communication
  while (!Serial && millis() < 5000); // Wait for serial port to connect. Needed for native USB port only.
  Serial.println("\n Drive system test");

  setup_pwm_driver(pwm_driver);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    Serial.println("loop");


    const float speed = 0.2f; // base speed
    bool toggle = false;

    std::vector<std::tuple<String, float, float>> speed_profile = {
        {String("forward, ") + String(speed) + " m/s",    speed,         0.0f},
        {"stop",                                         0.0f,          0.0f}, // String literal "stop" converts to String
        {String("backward, ") + String(speed) + " m/s",   -speed,        0.0f},
        {"stop",                                         0.0f,          0.0f},
        {"left turn on spot, 90 deg/s",                  0.0f,          static_cast<float>(90.0 * DEG2RAD)},
        {"stop",                                         0.0f,          0.0f},
        {"right turn on spot, 90 deg/s",                 0.0f,          static_cast<float>(-90.0 * DEG2RAD)},
        {"stop",                                         0.0f,          0.0f},
        {"left turn forward, 90 deg/s",                  speed / 2.0f,  static_cast<float>(90.0 * DEG2RAD)},
        {"stop",                                         0.0f,          0.0f},
        {"right turn backward, 90 deg/s",                -speed / 2.0f, static_cast<float>(-90.0 * DEG2RAD)},
        {"stop",                                         0.0f,          0.0f},
    };
    for (const auto& entry : speed_profile) {
        const auto& [description, linear, angular] = entry;
        digitalWrite(LED_BUILTIN, toggle);
        toggle = !toggle;

        Serial.println(description);
        drive_system.set_speed(linear, angular);

        delay(1000);
        Serial.println(); 
    }
}