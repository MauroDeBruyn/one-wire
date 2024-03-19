#include <RTClib.h>
#include <OneWire.h>
#include <TFT.h>  
#include <SPI.h>

// pin definition for display
#define cs   10
#define dc   9
#define rst  8

OneWire  ds(5);  // Connect 1-wire sensor to pin 5

TFT TFTscreen = TFT(cs, dc, rst); // create an instance of the library

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
  TFTscreen.text("Date & Time: \n", 0, 0);
  TFTscreen.text(String(now.day(), DEC).c_str(), 0, 10);
  TFTscreen.text("/", 0, 10);
  TFTscreen.text(String(now.month(), DEC).c_str(), 0, 10);
  TFTscreen.text("/", 0, 10);
  TFTscreen.text(String(now.year(), DEC).c_str(), 0, 10);
  TFTscreen.text(" (", 0, 10);
  TFTscreen.text(daysOfTheWeek[now.dayOfTheWeek()], 0, 10);
  TFTscreen.text(") ", 0, 10);
  TFTscreen.text(String(now.hour(), DEC).c_str(), 0, 10);
  TFTscreen.text(":", 0, 10);
  TFTscreen.text(String(now.minute(), DEC).c_str(), 0, 10);
  TFTscreen.text(":", 0, 10);
  TFTscreen.text(String(now.second(), DEC).c_str(), 0, 10);

  delay(1000); // delay 1 second
}




void logIButton(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  while(ds.search(addr)) {
    Serial.print("\n\n\n");

    Serial.print("\n\Address:\n\r");

    analogWrite(8, 255); //Led on

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
    delay(1000); //scan time incraments
    analogWrite(8, 0); //Led off
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

  pinMode(8, OUTPUT); // Set the LED pin as an output

   //initialize the library
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);
  //set the text size
  TFTscreen.setTextSize(1);
}

void loop() {
  //Serial.print("Present I-Button...\n\r");
  logIButton();

    // set font color
  TFTscreen.stroke(255, 255, 255);
  
  // print Hello, World! in the middle of the screen
  //TFTscreen.text(" Onewire \n Timestamp", 0, 6);


}
