#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTC.h"
#include "secrets.h"

#define BATTERY_100 100
#define BATTERY_80 80
#define BATTERY_60 60
#define BATTERY_40 40
#define BATTERY_20 20
#define BATTERY_05 5

extern const char * SSID;
extern const char * PSWD;

// Global timer
unsigned long startMillis;

// OLED screen
const uint8_t screenWidth = 128;
const uint8_t screenHeight = 64;
int level = BATTERY_100;
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, -1);

void displayBatteryLevel(void) {
  if (level < BATTERY_05) {
    // First bar
    display.drawFastVLine(4, 4, 8, SSD1306_BLACK);
    display.drawFastVLine(5, 4, 8, SSD1306_BLACK);
    display.drawFastVLine(6, 4, 8, SSD1306_BLACK);
  } else if (level < BATTERY_20) {
    // Second bar
    display.drawFastVLine( 8, 4, 8, SSD1306_BLACK);
    display.drawFastVLine( 9, 4, 8, SSD1306_BLACK);
    display.drawFastVLine(10, 4, 8, SSD1306_BLACK);
  } else if (level < BATTERY_40) {
    // Third bar
    display.drawFastVLine(12, 4, 8, SSD1306_BLACK);
    display.drawFastVLine(13, 4, 8, SSD1306_BLACK);
    display.drawFastVLine(14, 4, 8, SSD1306_BLACK);
  } else if (level < BATTERY_60) {
    // Fourth bar
    display.drawFastVLine(16, 4, 8, SSD1306_BLACK);
    display.drawFastVLine(17, 4, 8, SSD1306_BLACK);
    display.drawFastVLine(18, 4, 8, SSD1306_BLACK);
  } else if (level < BATTERY_80) {
    // Fifth bar
    display.drawFastVLine(20, 4, 8, SSD1306_BLACK);
    display.drawFastVLine(21, 4, 8, SSD1306_BLACK);
    display.drawFastVLine(22, 4, 8, SSD1306_BLACK);
  } else {
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
  }
}

void displayTimeClock(void) {
  display.drawFastHLine(35, 2, 60, SSD1306_WHITE);
  display.fillRect(35, 5, 60, 8, SSD1306_BLACK);
  display.setCursor(35, 5);

  RTCTime currentTime;
  RTC.getTime(currentTime);

  if (currentTime.getHour() < 10) display.print("0");
  display.print(currentTime.getHour());
  display.print(":");
  if (currentTime.getMinutes() < 10) display.print("0");
  display.print(currentTime.getMinutes());
  display.print(":");
  if (currentTime.getSeconds() < 10) display.print("0");
  display.print(currentTime.getSeconds());
}


void setup() {
  // Time
  RTC.begin();
  RTCTime savedTime;
  RTC.getTime(savedTime);

  if (!RTC.isRunning()) {
    if (savedTime.getYear() == 2000) {
      RTCTime startTime(22, Month::JULY, 2024, 16, 52, 00, DayOfWeek::MONDAY, SaveLight::SAVING_TIME_ACTIVE);
      RTC.setTime(startTime);
    } else {
      RTC.setTime(savedTime);
    }    
  }

  // OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  startMillis = millis();
}

/*
 * Yellow dimensions: 0 (top) - 15 (top) so 16 lines of yellow
 * Blue dimensions: 16 (top) - 63 (bottom) so 48 lines of blue
 */
void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currMillis = millis();

  if (currMillis - startMillis >= 1000) {
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

    displayBatteryLevel(); 

    level -= 5;

    if (level < 0) { level = BATTERY_100; }

    startMillis = currMillis;
  }

  displayTimeClock();
  display.display();
}
