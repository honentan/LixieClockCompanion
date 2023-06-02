#ifndef WL_FRAME_H_
#define WL_FRAME_H_

#include "OLEDDisplayUi.h"
#include "fzyt_fonts.h"
#include "lishu_fonts.h"
#include "weather_fonts.h"
#include "number_fonts.h"
#include "api.h"

// 定义各元素（字体）尺寸
#define HZ_WEIGHT 30
#define HZ_HEIGHT 30
#define NUMBER_L_WEIGHT 36
#define NUMBER_L_HEIGHT 60
#define NUMBER_S_WEIGHT 18
#define NUMBER_S_HEIGHT 30
#define WEATHER_L_WEIGHT 48
#define WEATHER_L_HEIGHT 48
#define WEATHER_S_WEIGHT 30
#define WEATHER_S_HEIGHT 30

#define GET_ALIGN_STRING_LEN(len) ((len + 3) & ~3) // 按对齐4字节读取FLASH

/*
enum FontType
{
  FZYT,
  LISHU,
};
*/

enum FontSize
{
  LARGE,
  SMALL,
};

class WL_FRAME
{
private:
  LunarCalendar lunar_calendar;
  WeatherData weather_now, weather_3d[2];
  
  WeatherIcon4848 w_icon48;
  WeatherIcon3030 w_icon30[2];
  SolarFont3030 solar_font[2];
  
  void updateSolarFontBits();
  int8_t solarFontIndex(const char* solar_term);

  void updateWeatherIconBits(FontSize font_size, const char *icon_id0, const char *icon_id1);
  int8_t weatherIconIndex(const char* icon_id);

  void showSolarTerm(OLEDDisplay *display, int16_t x, int16_t y);
  int hzFontIndex(String c_str, const String dict[], int dict_length);
  const unsigned char *digitBits(int number, FontSize font_size, bool if_reverse);
  const unsigned char *hzFontBits(String c_str, bool if_reverse);
  const unsigned char *weatherIconBits(String icon_id, FontSize font_size);
  void reverseAllBits(unsigned char *desc_bits, const unsigned char *source_bits, int weight, int height);
  const unsigned char *reverseHzBits(const unsigned char *source_bits);
  const unsigned char *reverseDigitBits(const unsigned char *source_bits, FontSize font_size);
  void showWeatherIcon(String icon_id, FontSize font_size,
                       OLEDDisplay *display, int16_t x, int16_t y);
  void show2Digits(int number, FontSize font_size,
                   OLEDDisplay *display, int16_t x, int16_t y);
  void showHzStr(String hz_str,
                 OLEDDisplay *display, int16_t x, int16_t y, bool if_reverse);
  void showMMDD(String date_str,
                OLEDDisplay *display, int16_t x, int16_t y);

public:
  WL_FRAME();

  void updateLunar(LunarCalendar l_lunar);
  void updateWeather3d(WeatherData* weather_data);
  void drawWeather3d(OLEDDisplay *display, int16_t x, int16_t y);
  void updateWeatherNow(WeatherData weather_data);
  void drawWeatherNow(OLEDDisplay *display, int16_t x, int16_t y);
  void weather3d(WeatherData *weather_data,
                 OLEDDisplay *display, int16_t x, int16_t y);
  void digitalClock(struct tm *p,
                    OLEDDisplay *display, int16_t x, int16_t y);
  void drawLunarCalendar(OLEDDisplay *display, int16_t x, int16_t y);
};

#endif
