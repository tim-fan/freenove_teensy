#include <Arduino.h>
#include <Adafruit_I2CDevice.h>

void setup() {
  Serial.begin(9600); // Start serial communication
  while (!Serial && millis() < 5000); // Wait for serial port to connect. Needed for native USB port only.
  Serial.println("\nI2C Scanner");

  // Initialize the I2C bus
  Wire.begin();
  Wire.setClock( 10000UL);
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Wire.endTransmission to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 2) {
      // nack, no device found, continue
      continue;
    }

    Serial.print("0x");
    if (address < 16) {
      Serial.print("0");
    }
    Serial.print(address, HEX);
    Serial.print(": ");

    if (error == 0) {
      Serial.println("Device found");
      nDevices++;
    } else {
      Serial.print("Error ");
      Serial.println(error);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.print("Found ");
    Serial.print(nDevices);
    Serial.println(" devices\n");
  }

  delay(5000); // Wait 5 seconds for next scan
}