#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Global timer
unsigned long currMillis;

// OLED screen
const uint8_t screenWidth = 128;
const uint8_t screenHeight = 64;
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, -1);

void setup() {
  // put your setup code here, to run once:

  // OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

/*
 * Yellow dimensions: 0 (top) - 15 (top) so 16 lines of yellow
 * Blue dimensions: 16 (top) - 63 (bottom) so 48 lines of blue
 */
void loop() {
  // put your main code here, to run repeatedly:
  currMillis = millis();

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

  // Blue top segment
  display.drawFastHLine(  0, 16, 128, SSD1306_WHITE);
  display.drawFastVLine(  0, 17,   3, SSD1306_WHITE);
  display.drawFastVLine(127, 17,   3, SSD1306_WHITE);

  // Blue bottom segment
  display.drawFastHLine(  0, 63, 128, SSD1306_WHITE);
  display.drawFastVLine(  0, 60,   3, SSD1306_WHITE);
  display.drawFastVLine(127, 60,   3, SSD1306_WHITE);

  display.display();
}
