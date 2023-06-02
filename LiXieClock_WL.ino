// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include "led_rainbow.h"
#include "WeatherLunar.h"

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN   15

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 120
#define LED_GROUP_COUNT 6
#define LOOP_DELAY 20
#define MAX_VOLUME_VAL 64.0
#define NORMAL_BRIGHTNESS 160

const int analogInPin = A0;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

uint32_t group_colors[LED_GROUP_COUNT];
LED_RAINBOW LEDRainbow = LED_RAINBOW(LED_GROUP_COUNT, &strip, group_colors);
int8_t time_digits[LED_GROUP_COUNT * 2];
int sensorValue = 0;

extern time_t now;

// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  /* 1. 初始化串口通讯波特率为115200 */
  Serial.begin(115200);
  Serial.printf("setup0 free heap: %d\n", ESP.getFreeHeap());
  
  weather_lunar_setup();

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------
void loop() {
  struct tm *p = nowTimeStruct();
  LEDRainbow.rainbowStep();
  showLEDTime(p);
  
  sensorValue = analogRead(analogInPin);
  if (sensorValue > MAX_VOLUME_VAL)
    sensorValue = MAX_VOLUME_VAL;
  
  weather_lunar_loop();
  
  delay(LOOP_DELAY);
}

void showLEDTime(struct tm *p) {
  time2LEDPos(p);

  for (int8_t i = 0; i < LED_COUNT; i++)
	  strip.setPixelColor(i, 0);

  //for (int8_t i = 0; i < LED_GROUP_COUNT * 2; i++) {
  //  Serial.printf("time_digits[%d]=%d ", i, time_digits[i]);
  //}
  //Serial.printf("sensorValue: %d,%d\n", sensorValue, int(sensorValue / MAX_VOLUME_VAL * 255.0));
  for (int8_t i = 0; i < LED_GROUP_COUNT; i++) {
    if (p->tm_hour % 2 == 0) {
      strip.setPixelColor(time_digits[i * 2], group_colors[0]);
      strip.setPixelColor(time_digits[i * 2 + 1], group_colors[0]);
    } else {
      strip.setPixelColor(time_digits[i * 2], group_colors[i]);
      strip.setPixelColor(time_digits[i * 2 + 1], group_colors[i]);
    }
  }
  if (p->tm_hour % 2 == 0)
	  strip.setBrightness(int(sensorValue / MAX_VOLUME_VAL * 255));
  else
    strip.setBrightness(NORMAL_BRIGHTNESS);
  strip.show();
}

// 时间转换为led位置
void time2LEDPos(struct tm *p) {
  const int8_t led_sn[] = {9, 4, 8, 3, 7, 2, 6, 1, 5, 0};

  time_digits[0] = led_sn[int(p->tm_hour / 10)];
  time_digits[1] = led_sn[int(p->tm_hour / 10)] + 10;
  time_digits[2] = led_sn[p->tm_hour % 10] + 20;
  time_digits[3] = led_sn[p->tm_hour % 10] + 30;
  time_digits[4] = led_sn[int(p->tm_min / 10)] + 40;
  time_digits[5] = led_sn[int(p->tm_min / 10)] + 50;
  time_digits[6] = led_sn[p->tm_min % 10] + 60;
  time_digits[7] = led_sn[p->tm_min % 10] + 70;
  time_digits[8] = led_sn[int(p->tm_sec / 10)] + 80;
  time_digits[9] = led_sn[int(p->tm_sec / 10)] + 90;
  time_digits[10] = led_sn[p->tm_sec % 10] + 100;
  time_digits[11] = led_sn[p->tm_sec % 10] + 110;
}
