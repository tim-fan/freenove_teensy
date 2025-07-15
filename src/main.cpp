// main.cpp
// Exposes a serial interface to control the robot.
//  Simply takes strings over serial of form "<forward_val>,<turn_val>\n"
// where forward_val and turn_val specify signed floats.
// A bit inefficient to encode via strings, but quick and easy.


#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <Motor.h>
#include <DriveSystem.h>
#include <cmath>

#define DEG2RAD M_PI/180.f
#define HWSERIAL Serial1  // rx pin 0, tx pin 1

#define SERIAL_TIMEOUT 1000  // stop robot if no serial received in this many milliseconds 

unsigned long last_receive_time;

Adafruit_PWMServoDriver pwm_driver = Adafruit_PWMServoDriver();

DriveSystem drive_system(
    Motor(pwm_driver, 1, 0), // right rear
    Motor(pwm_driver, 2, 3), // right front
    Motor(pwm_driver, 5, 4), // left front
    Motor(pwm_driver, 7, 6) // left rear
);

void setup() {
  Serial.begin(9600); // debug port
  HWSERIAL.begin(9600);
  setup_pwm_driver(pwm_driver);
  pinMode(LED_BUILTIN, OUTPUT);
  drive_system.set_speed(0,0);
  Serial.println("\n Exposing serial interfact to control robot");
}

void loop() {

  if (HWSERIAL.available()) {
    digitalWrite(LED_BUILTIN, HIGH);
    String command = HWSERIAL.readStringUntil('\n'); // Read until newline
    command.trim();
    Serial.println(String("Received command: ") + command);
    int comma_index = command.indexOf(',');
    if (comma_index != -1) {
      String forwards_str = command.substring(0, comma_index);
      String turn_str = command.substring(comma_index + 1);

      float forwards_value = forwards_str.toFloat(); 
      float turn_value = turn_str.toFloat();

      Serial.print("Received: Forwards = " + String(forwards_value, 2) + ", Turn = " + String(turn_value, 2) + "\n");
      drive_system.set_speed(forwards_value, turn_value);
      last_receive_time = millis();
    }
  } else if ((millis() - last_receive_time) > SERIAL_TIMEOUT){
    drive_system.set_speed(0,0);
    Serial.println("Timeout receiving command, set speed to 0");
    last_receive_time = millis();
  }
  digitalWrite(LED_BUILTIN, LOW);
}