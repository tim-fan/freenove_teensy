#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <Motor.h>

Adafruit_PWMServoDriver pwm_driver = Adafruit_PWMServoDriver();

Motor motor(pwm_driver, 1, 0); // right rear

void setup() {
  Serial.begin(9600); // Start serial communication
  while (!Serial && millis() < 5000); // Wait for serial port to connect. Needed for native USB port only.
  Serial.println("\n Single Motor test");

  setup_pwm_driver(pwm_driver);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    Serial.println("loop");

    motor.set_speed(0);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    motor.set_speed(0.1);
    delay(400);
    motor.set_speed(0.4);
    delay(400);
    motor.set_speed(-0.4);
    delay(400);

}