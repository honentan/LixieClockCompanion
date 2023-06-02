#ifndef LISHU_FONTS_H_
#define LISHU_FONTS_H_

#include <Arduino.h>

#define LISHU_FONT_NUMBER 29
#define LISHU_FONT_LENGTH 120 // 4*30
#define LISHU_FONT_WEIGHT 30
#define LISHU_FONT_HEIGHT 30

#define UTF8_HZ_LENGTH 3

typedef struct
{
  //int weight;
  //int height;
  char solar_term[UTF8_HZ_LENGTH + 1]; // utf-8汉字
  int8_t index;
  unsigned char bits[LISHU_FONT_LENGTH];
} SolarFont3030;

extern const char lishu_font_3030[LISHU_FONT_NUMBER][LISHU_FONT_LENGTH];
extern const char lishu_font_ids[LISHU_FONT_NUMBER][UTF8_HZ_LENGTH + 1]; // utf-8汉字

#endif
