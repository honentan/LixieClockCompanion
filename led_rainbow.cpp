#include <Arduino.h>

#include "led_rainbow.h"

LED_RAINBOW::LED_RAINBOW(int8_t led_group_number, Adafruit_NeoPixel *strip, uint32_t* group_colors) {
  led_groups = led_group_number;
  firstPixelHue = 0;
  color_groups = group_colors;
  strip = strip;
}


LED_RAINBOW::~LED_RAINBOW() {
}


void LED_RAINBOW::rainbowStep() {
  for(int i=0; i<led_groups; i++) { // For each pixel in strip...
    // Offset pixel hue by an amount to make one full revolution of the
    // color wheel (range of 65536) along the length of the strip
    // (strip.numPixels() steps):
    int pixelHue = firstPixelHue + (i * 65536L / led_groups);
    // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
    // optionally add saturation and value (brightness) (each 0 to 255).
    // Here we're using just the single-argument hue variant. The result
    // is passed through strip.gamma32() to provide 'truer' colors
    // before assigning to each pixel:
	  color_groups[i] = strip->gamma32(strip->ColorHSV(pixelHue));
  }

  firstPixelHue += 256;
  if (firstPixelHue >=  5*65536)
	firstPixelHue = 0;
}
