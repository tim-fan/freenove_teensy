#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50); 

  Serial.begin(9600);

  
}

int loop_count = 0;
void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  loop_count++;
  Serial.print("loop ");
  Serial.println(loop_count);

  Serial.print("readPrescale: ");
  Serial.println(pwm.readPrescale());
  for (uint8_t pwmnum=0; pwmnum < 2; pwmnum++) {
    // pwm.setPWM(pwmnum, 0, 4096 );
    pwm.setPWM(pwmnum, 4096, 0 );
    delay(100);
  }

  // wait for a second
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);

  for (uint8_t pwmnum=0; pwmnum < 2; pwmnum++) {
    pwm.setPWM(pwmnum, 0, 4096 );
  }

   // wait for a second
  delay(1000);
}



// #include <Arduino.h>
// #include <Wire.h> // Include the I2C library

// void setup() {
//   Serial.begin(9600); // Start serial communication
//   while (!Serial && millis() < 5000); // Wait for serial port to connect. Needed for native USB port only.
//   Serial.println("\nI2C Scanner");

//   // Initialize the I2C bus
//   pinMode(18, INPUT_PULLUP);
//   pinMode(19, INPUT_PULLUP);
//   Wire.begin();
//   Wire.setClock( 10000UL);
// }

// void loop() {
//   byte error, address;
//   int nDevices;

//   Serial.println("Scanning...");

//   nDevices = 0;
//   for (address = 1; address < 127; address++) {
//     // The i2c_scanner uses the return value of
//     // the Wire.endTransmission to see if
//     // a device did acknowledge to the address.
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();

//     if (error == 0) {
//       Serial.print("I2C device found at address 0x");
//       if (address < 16) {
//         Serial.print("0");
//       }
//       Serial.print(address, HEX);
//       Serial.println("  !");
//       nDevices++;
//     } else {
//       Serial.print("Error ");
//       Serial.print(error);
//       Serial.print(" at address 0x");
//       if (address < 16) {
//         Serial.print("0");
//       }
//       Serial.println(address, HEX);
//     }
//   }
//   if (nDevices == 0) {
//     Serial.println("No I2C devices found\n");
//   } else {
//     Serial.println("done\n");
//   }

//   delay(5000); // Wait 5 seconds for next scan
// }