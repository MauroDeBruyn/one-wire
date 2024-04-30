#include <Wire.h>
#include <Arduino_LSM9DS1.h>
#include <Arduino_HTS221.h>

float x, y, z;
int degreesX = 0;
int degreesY = 0;

float old_temp = 0;
float old_hum = 0;

#define SENSOR_ADDRESS 0x12 // Address of the sensor device

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
   if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
}

struct SensorData {
  float temperature;
  float humidity;
  float x;
  float y;
  float z;
};


void loop() {


  float temperature = HTS.readTemperature(); //read
  float humidity    = HTS.readHumidity(); //read

 if (abs(old_temp - temperature) >= 0.5 || abs(old_hum - humidity) >= 1 )
  {
    old_temp = temperature;
    old_hum = humidity;
    // print each of the sensor values
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Humidity    = ");
    Serial.print(humidity);
    Serial.println(" %");
    Serial.println();
  }

   Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");

  // print an empty line
  Serial.println();

  delay(1000);

float waardeIMU = IMU.readAcceleration(x, y, z);
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

  }

  if (x > 0.1) {
    x = 100 * x;
    degreesX = map(x, 0, 97, 0, 90);
    Serial.print("Tilting up ");
    Serial.print(degreesX);
    Serial.println("  degrees");
  }
  if (x < -0.1) {
    x = 100 * x;
    degreesX = map(x, 0, -100, 0, 90);
    Serial.print("Tilting down ");
    Serial.print(degreesX);
    Serial.println("  degrees");
  }
  if (y > 0.1) {
    y = 100 * y;
    degreesY = map(y, 0, 97, 0, 90);
    Serial.print("Tilting left ");
    Serial.print(degreesY);
    Serial.println("  degrees");
  }
  if (y < -0.1) {
    y = 100 * y;
    degreesY = map(y, 0, -100, 0, 90);
    Serial.print("Tilting right ");
    Serial.print(degreesY);
    Serial.println("  degrees");
  }

    // Send the fixed number over I2C
  Wire.beginTransmission(8); // Address of the Arduino Uno
  Wire.write((uint8_t*)&temperature, sizeof(temperature));
  delay(1000);
  Wire.write((uint8_t*)&humidity, sizeof(humidity));
  delay(1000);
  Wire.write((uint8_t*)&x, sizeof(x));
  delay(1000);
  Wire.write((uint8_t*)&y, sizeof(y));
  delay(1000);
  Wire.write((uint8_t*)&z, sizeof(z));
  delay(1000);

  Wire.endTransmission();

  Serial.println(temperature);
  Serial.println(humidity);
  Serial.println(waardeIMU);


}