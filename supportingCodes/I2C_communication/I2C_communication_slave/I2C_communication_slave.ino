#include <Wire.h>

#define SENSOR_ADDRESS 0x12 // Address of the sensor device

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // Fixed number to be sent
  float fixedNumber = 42.0;
  
  // Send the fixed number over I2C
  Wire.beginTransmission(8); // Address of the Arduino Uno
  Wire.write((uint8_t*)&fixedNumber, sizeof(fixedNumber));
  Wire.endTransmission();
  
  Serial.print("Sent fixed number: ");
  Serial.println(fixedNumber);
  
  delay(1000); // Wait for a second before sending again
}
