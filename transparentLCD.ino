// transparent LCD from Crystalfontz 128x64px ST7565 with Arduino UNO

#include <Arduino.h>
#include <U8g2lib.h>  // u8g2 library is used for drawing graphics on the display
#include <SPI.h>

#include "images.h"  // this file includes generated c-style arrays for all the screenshots (images generated using https://javl.github.io/image2cpp/)

/********** BOARD PIN STUFF ***********/
// ARD    | LCD  | Color
// -------+------+----------------------
// 3v3    | 3v3  |  Red
// GND    | GND  |  Black - ground
// D8     | DC   |  Green - data/command
// D9     | RES  |  Blue - reset
// D10    | CS   |  Purple - chip select
// D11    | D7   |  Gray - SPI data
// D13    | D6   |  Orange - SPI clock
/**************************************/

// display initilization
U8G2_ST7565_64128N_F_4W_HW_SPI u8g2(U8G2_R2, /*cs*/ 10, /*dc*/ 8, /*reset*/ 9);

constexpr unsigned short DISPLAY_W = 128;
constexpr unsigned short DISPLAY_H = 64;

constexpr unsigned short refreshRateMS = 50;

void setup(void) {
  Serial.begin(9600);
  u8g2.begin();  // begin function is required for u8g2
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightAll();  	/* this will add some extra space for the text inside the buttons */
  u8g2.setDisplayRotation(U8G2_R0);
}

// Main drawing loop
void drawFrame(int frameToDraw) {
  static int val = 0;
  if(Serial.available()) val = Serial.read();
  u8g2.drawStr(15, 15, String(val * 347).c_str());
  Serial.println(val);
}

void loop(void) {
  static int counter = 0;
  
  u8g2.clearBuffer();                                          // clear the internal memory
  drawFrame(counter++);
  u8g2.sendBuffer();                                           // transfer internal memory to the display
  delay(refreshRateMS);
}