#include <RTClib.h>
#include <OneWire.h>

OneWire  ds(3);  // Connect 1-wire sensor to pin 3
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

void timeStamp(void){
  DateTime now = rtc.now();
  Serial.print("Date & Time: \n");
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

  delay(1000); // delay 1 seconds
}

void logPerson(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  //Serial.print("Looking for 1-Wire devices...\n\r");
  while(ds.search(addr)) {
    Serial.print("\n\n\n");
    Serial.print("\n\Address:\n\r");
    for( i = 0; i < 8; i++) {
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(" ");
      }
    }
    Serial.print("\n\n");
    timeStamp();
    //Serial.print("\n\n\n");

    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("CRC is not valid!\n");
        return;
    }
    delay(2000); //scan time incraments
  }
  ds.reset_search();
  return;
}

void setup() {
  Serial.begin(9600);

  //TimeStamp
  // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }

  // automatically sets the RTC to the date & time on PC this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // manually sets the RTC with an explicit date & time, for example to set
  // January 21, 2021 at 3am you would call:
  // rtc.adjust(DateTime(2021, 1, 21, 3, 0, 0));

  //IButtonRead
}

void loop() {
  logPerson();

}
