#ifndef LED_RAINBOW_H_
#define LED_RAINBOW_H_

#include <Adafruit_NeoPixel.h>

class LED_RAINBOW
{
private:
  int8_t led_groups;
  long firstPixelHue;
  Adafruit_NeoPixel *strip;
  uint32_t* color_groups;

public:
  LED_RAINBOW(int8_t led_group_number, Adafruit_NeoPixel *strip, uint32_t* group_colors);
  ~LED_RAINBOW();
  
  void rainbowStep();
};

#endif
