

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
#include "Stopwatch.cpp"
#include <Vector.h>

// For the Adafruit shield, these are the default.
#define TFT_CS 7
#define TFT_RST 8
#define TFT_DC 9
#define TFT_MOSI 10
#define TFT_CLK 11
#define TFT_MISO 12 
#define sensorPin 2
typedef Vector<String> Lines;

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

int sensorLastValue = 0;
int sensor = -1;
int rCount = 0;
unsigned int rpm = 0;

Stopwatch runtimeSW;
Stopwatch counterSW;
Stopwatch displaySW;
String arrLines[2];
Lines lines;


void setup() 
{
  // Initialize
  runtimeSW = Stopwatch();
  counterSW = Stopwatch();
  displaySW = Stopwatch();
  runtimeSW.Start();
  displaySW.Start();
  lines.setStorage(arrLines);

  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

  // Connect
  tft.begin();
  
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);

  // Set constant text
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(3);

  lines.push_back("Runtime: ");
  lines.push_back("RPM: ");

  for (String line : lines)
  {
    if (line != NULL && line.length() > 0)
    {
      tft.println(line);
    }
  }
}

void loop(void) 
{
  // Read sensor state
  sensor = digitalRead(sensorPin);
  
  if (sensor == 0 && sensor != sensorLastValue)
  {
    rCount++;

    if (!counterSW.IsRunning())
    {
      counterSW.Start();
      Serial.println("RPM Counter Started!");
    }
  }
    // Update last value
    sensorLastValue = sensor;

  if (counterSW.Elapsed() >= 3000)
  {
      rpm = (rCount/(float)(counterSW.Elapsed()/1000))*60;
      Serial.print("counted: "); Serial.println(rCount);
      rCount = 0;
      counterSW.Restart();

      UpdateDisplayRPM();
  }

  if (displaySW.Elapsed() >= 1000)
  {
    UpdateDisplayTime();
    displaySW.Restart();
  }

  delay(5);
}

void SetCursorAfter(int lineNumber, int size = 3)
{
  int ySize = 8 * size;
  int xSize = 6 * size;
  int posY = ySize * lineNumber;
  int posX = lines[lineNumber].length() * xSize;
  tft.setCursor(posX, posY);
}

void UpdateDisplayTime() 
{
  SetCursorAfter(0);
  tft.print(runtimeSW.Elapsed()/1000); tft.println("s");
}

void UpdateDisplayRPM() 
{
  SetCursorAfter(1);
  tft.print(rpm); tft.println("   ");
}
