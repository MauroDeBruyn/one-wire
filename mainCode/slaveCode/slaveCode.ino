#include <ArduinoJson.h>

#define LED 2

void setup() {
   Serial.begin(9600);
   Serial2.begin(115200);
   pinMode(LED, OUTPUT);
}

void loop() {
  Serial2.write('1'); 
  digitalWrite(LED, HIGH); 
  StaticJsonDocument<200> doc;

  delay(1000); 

  if (Serial2.available() >= 1) {
    char buffer[200];
    Serial2.readBytesUntil('\n', buffer, 200);

    DeserializationError error = deserializeJson(doc, buffer);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    const int sensorId = doc["Id"];
    const char* number = doc["Number"];
    const int colornumber = doc["ColorNumber"];

    Serial.print("Id: ");
    Serial.println(sensorId);
    Serial.print("Colornumber: ");
    Serial.println(number);
    Serial.print("ColorNumber: ");
    Serial.println(colornumber);
  }

  Serial2.write('0');
  digitalWrite(LED, LOW);

  delay(1000); 
}