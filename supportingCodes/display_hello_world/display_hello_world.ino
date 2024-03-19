// include TFT and SPI libraries
#include <TFT.h>  
#include <SPI.h>

// pin definition for Arduino UNO
#define cs   10
#define dc   9
#define rst  8


// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

void setup() {

  //initialize the library
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);
  //set the text size
  TFTscreen.setTextSize(1);
}

void loop() {
  // set font color
  TFTscreen.stroke(255, 255, 255);
  
  // print Hello, World! in the middle of the screen
  TFTscreen.text(" Onewire \n Timestamp", 0, 6);
}