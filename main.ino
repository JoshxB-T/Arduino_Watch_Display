#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Global timer
unsigned long currMillis;

// OLED screen
unsigned long faceTimer = 0;
uint16_t facePeriod = 5;
unsigned long faceTimer2 = 0;
const uint16_t facePeriod2 = 5000;
bool smiling = true;
int8_t eyeHeight = 20;
bool faceReverse = false;
const uint8_t screenWidth = 128;
const uint8_t screenHeight = 64;
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, -1);

// make robot face smile
void drawSmile() {
  drawMouth(15, 40, 64, 50, true);
  display.display();
}

// make robot face frown
void drawFrown() {
  drawMouth(16, 40, 64, 65, false);
  display.display();
}

// draw robot eyes based on eyeHeight
// simulates a blinking effect as eyeHeight changes
void drawEyes() {
  display.fillRoundRect(20, 10, 22, eyeHeight, 4, WHITE);
  display.fillRoundRect(86, 10, 22, eyeHeight, 4, WHITE);
}

// algorithm to draw the mouth based on parameters
void drawMouth(int height, int width, int originx, int originy, bool smile) {
  int hh = height * height;
  int ww = width * width;
  int hhww = hh * ww;
  int x0 = width;
  int dx = 0;

  for (int x = -width; x <= width; x++) {
    display.drawPixel(originx + x, originy, WHITE);
  }

  for (int y = 1; y <= height; y++) {
    int x1 = x0 - (dx - 1);
    for ( ; x1 > 0; x1--) {
      if (x1*x1*hh + y*y*ww <= hhww) break;
    }

    dx = x0 - x1;
    x0 = x1;

    for (int x = -x0; x <= x0; x++) {
      int yNew = smile ? originy + y : originy - y;
      display.drawPixel(originx + x, yNew, WHITE);
    }
  }
}

// handle the robot's facial expression as well as the blinking
void handleFace() {
  // every 5 seconds, there's a 20% chance of switching facial expression
  if (currMillis - faceTimer2 >= facePeriod2) {
    if ((rand() % 100) < 20) smiling = !smiling;  

    faceTimer2 = currMillis;
  }

  // blink in constant intervals
  if (currMillis - faceTimer >= facePeriod) {
    facePeriod = 5;
    display.clearDisplay();
    drawEyes();

    // redraw smile or frown because of clearDisplay
    if (smiling) drawSmile();
    else drawFrown();
    
    // update eye parameters for next iteration of loop()
    if (!faceReverse) eyeHeight -= 8;
    else eyeHeight += 8;
    
    // just blinked, wait 3 seconds
    if (eyeHeight > 26) {
      eyeHeight = 20;
      faceReverse = false;
      facePeriod = 3000;
    }

    // in the middle of blinking (eye is closed)
    if (eyeHeight < 0) {
      faceReverse = true;
      facePeriod = 100;
    }

    faceTimer = currMillis;
  }
}

void setup() {
  // put your setup code here, to run once:

  // OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  //drawSmile();
}

/*
 * Yellow dimensions: 0 (top) - 15 (top) so 16 lines of yellow
 * Blue dimensions: 16 (top) - 63 (bottom) so 48 lines of blue
 */
void loop() {
  // put your main code here, to run repeatedly:
  currMillis = millis();

  //handleFace(); // make robot blink and handle facial expressions
  // Yellow top segment
  display.drawFastHLine(  0,  0, 128, SSD1306_WHITE);
  display.drawFastVLine(  0,  1,   3, SSD1306_WHITE);
  display.drawFastVLine(127,  1,   3, SSD1306_WHITE);

  // Battery top side
  display.drawFastHLine(2, 2, 26, SSD1306_WHITE);
  // First bar
  display.drawFastVLine(2, 2, 12, SSD1306_WHITE);
  display.drawFastVLine(7, 2, 12, SSD1306_WHITE);
  // Second bar
  display.drawFastVLine(9, 2, 12, SSD1306_WHITE);
  display.drawFastVLine(14, 2, 12, SSD1306_WHITE);
  // Third bar
  display.drawFastVLine(16, 2, 12, SSD1306_WHITE);
  display.drawFastVLine(21, 2, 12, SSD1306_WHITE);
  // Fourth bar
  display.drawFastVLine(23, 2, 12, SSD1306_WHITE);
  display.drawFastVLine(28, 2, 12, SSD1306_WHITE);
  display.drawFastVLine(29, 4, 8, SSD1306_WHITE);
  display.drawFastVLine(30, 6, 4, SSD1306_WHITE);
  // Battery bottom side
  display.drawFastHLine(2, 13, 26, SSD1306_WHITE);

  // Yellow bottom segment
  display.drawFastHLine(  0, 15, 128, SSD1306_WHITE);
  display.drawFastVLine(  0, 12,   3, SSD1306_WHITE);
  display.drawFastVLine(127, 12,   3, SSD1306_WHITE);

  display.drawFastHLine(  0, 16, 128, SSD1306_WHITE);
  display.drawFastVLine(  0, 17,   3, SSD1306_WHITE);
  display.drawFastVLine(127, 17,   3, SSD1306_WHITE);
  display.drawFastHLine(  0, 63, 128, SSD1306_WHITE);
  display.drawFastVLine(  0, 60,   3, SSD1306_WHITE);
  display.drawFastVLine(127, 60,   3, SSD1306_WHITE);

  display.display();
}
