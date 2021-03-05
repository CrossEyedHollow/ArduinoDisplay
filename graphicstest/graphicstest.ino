/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  *************************************************/

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_CS 7
#define TFT_RST 8
#define TFT_DC 9
#define TFT_MOSI 10
#define TFT_CLK 11
#define TFT_MISO 12 
#define sensorPin 2

int sensor = 0;

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() 
{
  // Initialize
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

  // Connect
  tft.begin();
  
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
}

void loop(void) 
{
  unsigned long start = millis();

  sensor = digitalRead(sensorPin);
  testText();
  delay(50);
}
unsigned long testText() 
{
  unsigned long start = micros();
  //Clear
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);

  tft.setTextSize(3);
  tft.print("Time  start: ");
  tft.print(millis()/1000); tft.println("s");
  tft.print("Sensor: ");
  tft.println((sensor == 1) ? "HIGH" : "LOW ");
  
  return micros() - start;
}
