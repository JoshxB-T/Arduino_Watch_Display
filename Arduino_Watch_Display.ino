#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTC.h"
#include "secrets.h"

#define ONE_MILLISECOND 1000

#define BATTERY_100 100
#define BATTERY_080 80
#define BATTERY_060 60
#define BATTERY_040 40
#define BATTERY_020 20
#define BATTERY_005 5
#define BATTERY_FRST_X 4
#define BATTERY_SCND_X 8
#define BATTERY_THRD_X 12
#define BATTERY_FRTH_X 16
#define BATTERY_FFTH_X 20
#define BATTERY_COORD_Y 5
#define BATTERY_LEVEL_WIDTH 3
#define BATTERY_LEVEL_HEIGHT 7

#define CLOCK_COORD_X 75

extern const char * SSID;
extern const char * PSWD;

// Global timer
unsigned long startMillis;

// OLED screen
const uint8_t screenWidth = 128;
const uint8_t screenHeight = 64;
int battery_level = BATTERY_100;
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, -1);

void displayBatteryLevel(void) {
  if (battery_level < BATTERY_005)      { display.fillRect(BATTERY_FRST_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_BLACK); }
  else if (battery_level < BATTERY_020) { display.fillRect(BATTERY_SCND_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_BLACK); }
  else if (battery_level < BATTERY_040) { display.fillRect(BATTERY_THRD_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_BLACK); }
  else if (battery_level < BATTERY_060) { display.fillRect(BATTERY_FRTH_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_BLACK); }
  else if (battery_level < BATTERY_080) { display.fillRect(BATTERY_FFTH_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_BLACK); }
  else { 
    display.fillRect(BATTERY_FRST_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_WHITE);
    display.fillRect(BATTERY_SCND_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_WHITE);
    display.fillRect(BATTERY_THRD_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_WHITE);
    display.fillRect(BATTERY_FRTH_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_WHITE);
    display.fillRect(BATTERY_FFTH_X, BATTERY_COORD_Y, BATTERY_LEVEL_WIDTH, BATTERY_LEVEL_HEIGHT, SSD1306_WHITE);
  }
}

void displayTimeClock(void) {
  display.fillRect(CLOCK_COORD_X + 2, 5, 48, 8, SSD1306_BLACK);
  display.setCursor(CLOCK_COORD_X + 2, 5);

  RTCTime currentTime;
  RTC.getTime(currentTime);

  if (currentTime.getHour() < 10) { display.print("0"); }
  display.print(currentTime.getHour());
  display.print(":");
  if (currentTime.getMinutes() < 10) { display.print("0"); }
  display.print(currentTime.getMinutes());
  display.print(":");
  if (currentTime.getSeconds() < 10) { display.print("0"); }
  display.print(currentTime.getSeconds());
}

void setup() {
  // Time
  RTC.begin();
  RTCTime savedTime;
  RTC.getTime(savedTime);

  if (!RTC.isRunning()) {
    if (savedTime.getYear() == 2000) {
      RTCTime startTime(22, Month::JUNE, 2026, 23, 59, 00, DayOfWeek::MONDAY, SaveLight::SAVING_TIME_ACTIVE);
      RTC.setTime(startTime);
    } else {
      RTC.setTime(savedTime);
    }    
  }

  // OLED init
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  // Upper outline (yellow)
  display.drawFastHLine(  0,  1, 128, SSD1306_WHITE);
  display.drawFastVLine(  0,  2,   3, SSD1306_WHITE);
  display.drawFastVLine(127,  2,   3, SSD1306_WHITE);
  display.drawFastHLine(  0, 15, 128, SSD1306_WHITE);
  display.drawFastVLine(  0, 12,   3, SSD1306_WHITE);
  display.drawFastVLine(127, 12,   3, SSD1306_WHITE);

  // Lower outline (blue)
  display.drawFastHLine(  0, 16, 128, SSD1306_WHITE);
  display.drawFastVLine(  0, 17,   3, SSD1306_WHITE);
  display.drawFastVLine(127, 17,   3, SSD1306_WHITE);
  display.drawFastHLine(  0, 63, 128, SSD1306_WHITE);
  display.drawFastVLine(  0, 60,   3, SSD1306_WHITE);
  display.drawFastVLine(127, 60,   3, SSD1306_WHITE);

  // Battery outline
  display.drawRect(2, 3, 23, 11, SSD1306_WHITE);
  display.drawFastVLine(25,  5,  7, SSD1306_WHITE); // Positive terminal side (and line below)
  display.drawFastVLine(26,  7,  3, SSD1306_WHITE);

  // Clock outline
  display.drawRect(CLOCK_COORD_X, 3, 51, 11, SSD1306_WHITE);

  startMillis = millis();
}

/*
 * Yellow dimensions: 0 (top) - 15 (top) so 16 lines of yellow
 * Blue dimensions: 16 (top) - 63 (bottom) so 48 lines of blue
 */
void loop() {
  unsigned long currMillis = millis();

  if (currMillis - startMillis >= ONE_MILLISECOND) {
    displayBatteryLevel(); 

    battery_level -= 5;

    if (battery_level < 0) { battery_level = BATTERY_100; }

    startMillis = currMillis;
  }

  displayTimeClock();
  display.display();
}
