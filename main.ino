#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Global timer
unsigned long currMillis;

// OLED screen
const uint8_t screenWidth = 128;
const uint8_t screenHeight = 64;
int level = 4;
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, -1);

void drawBatteryLevel(void) {
  switch(level) {
    case 0: {
      // First bar
      Serial.println("First level off");
      break;
    }
    case 1: {
      // Second bar
      Serial.println("Second level off");
      break;
    }
    case 2: {
      // Third bar
      Serial.println("Third level off");
      break;
    }
    case 3: {
      // Fourth bar off
      Serial.println("Fourth level off");
      break;
    }
    default: {
      // First bar
      display.drawFastVLine(4, 4, 8, SSD1306_WHITE);
      display.drawFastVLine(5, 4, 8, SSD1306_WHITE);
      display.drawFastVLine(6, 4, 8, SSD1306_WHITE);

      // Second bar
      display.drawFastVLine( 8, 4, 8, SSD1306_WHITE);
      display.drawFastVLine( 9, 4, 8, SSD1306_WHITE);
      display.drawFastVLine(10, 4, 8, SSD1306_WHITE);

      // Third bar
      display.drawFastVLine(12, 4, 8, SSD1306_WHITE);
      display.drawFastVLine(13, 4, 8, SSD1306_WHITE);
      display.drawFastVLine(14, 4, 8, SSD1306_WHITE);

      // Fourth bar
      display.drawFastVLine(16, 4, 8, SSD1306_WHITE);
      display.drawFastVLine(17, 4, 8, SSD1306_WHITE);
      display.drawFastVLine(18, 4, 8, SSD1306_WHITE);

      // Fifth bar
      display.drawFastVLine(20, 4, 8, SSD1306_WHITE);
      display.drawFastVLine(21, 4, 8, SSD1306_WHITE);
      display.drawFastVLine(22, 4, 8, SSD1306_WHITE);
      Serial.println("All levels on");
    }
  }
}

void setup() {
  Serial.begin(9600);

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

  display.drawFastHLine( 2,  2, 23, SSD1306_WHITE); // Battery top side
  display.drawFastHLine( 2, 13, 23, SSD1306_WHITE); // Battery bottom side
  display.drawFastVLine( 2,  3, 11, SSD1306_WHITE); // Battery left side
  display.drawFastVLine(24,  3, 11, SSD1306_WHITE); // Battery right side
  display.drawFastVLine(25,  4,  8, SSD1306_WHITE); // Battery positive terminal side
  display.drawFastVLine(26,  6,  4, SSD1306_WHITE);
  drawBatteryLevel();

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
  level -= 1;
  delay(2000);

  if (level < 0) {
    level = 4;
    Serial.println();
  }

  Serial.print(level);
  Serial.print(' ');
}
