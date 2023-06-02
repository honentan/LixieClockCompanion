#ifndef FZYT_FONTS_H_
#define FZYT_FONTS_H_

#include <Arduino.h>

#define FZYT_FONT_NUMBER 19

typedef struct
{
  int weight;
  int height;
  String dict[FZYT_FONT_NUMBER];
  unsigned char bits[FZYT_FONT_NUMBER][4 * 30];
} FzytFont3030;

extern const FzytFont3030 fzyt_font30;

#endif
