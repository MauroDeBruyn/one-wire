#include <Wire.h>

void setup() {
  Wire.begin(8);                // Join I2C bus with address 8
  Wire.onReceive(receiveEvent); // Register event
  Serial.begin(9600);           // Start serial for output
}

void loop() {
  delay(100);
}

// Function to handle received data
void receiveEvent(int bytes) {
  while (Wire.available()) { // While data is available to receive
    float fixedNumber; // Variable to store the received fixed number
    Wire.readBytes((uint8_t*)&fixedNumber, sizeof(fixedNumber)); // Read the incoming fixed number
    Serial.print("Received fixed number from sensor: ");
    Serial.println(fixedNumber);
  }
}
