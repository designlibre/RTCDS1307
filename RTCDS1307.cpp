#include <RTCDS1307.h>

// Public Domain code by JeeLabs http://news.jeelabs.org/code/
// Code was trimmed but not modified by DesignLibre.

// Simple general-purpose date/time class (no TZ / DST / leap second handling!)


// RTC based on the DS1307 chip connected via I2C and the Wire library



////////////////////////////////////////////////////////////////////////////////
// RTCDS1307 implementation


int i = 0; //The new wire library needs to take an int when you are sending for the zero register

static uint8_t bcd2bin (uint8_t val) { return val - 6 * (val >> 4); }
static uint8_t bin2bcd (uint8_t val) { return val + 6 * (val / 10); }

uint8_t RTCDS1307::begin(void) 
{
  return 1;
}
uint8_t RTCDS1307::isrunning(void) 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(i);	
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 1);
  uint8_t ss = Wire.read();
  return !(ss>>7);
}
void RTCDS1307::adjust(const DateTime& dt) 
{
    Wire.beginTransmission(DS1307_ADDRESS);
    Wire.write(i);
    Wire.write(bin2bcd(dt.second()));
    Wire.write(bin2bcd(dt.minute()));
    Wire.write(bin2bcd(dt.hour()));
    Wire.write(bin2bcd(0));
    Wire.write(bin2bcd(dt.day()));
    Wire.write(bin2bcd(dt.month()));
    Wire.write(bin2bcd(dt.year() - 2000));
    Wire.write(i);
    Wire.endTransmission();
}
DateTime RTCDS1307::now() 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(i);	
  Wire.endTransmission();
  
  Wire.requestFrom(DS1307_ADDRESS, 7);
  uint8_t ss = bcd2bin(Wire.read() & 0x7F);
  uint8_t mm = bcd2bin(Wire.read());
  uint8_t hh = bcd2bin(Wire.read());
  Wire.read();
  uint8_t d = bcd2bin(Wire.read());
  uint8_t m = bcd2bin(Wire.read());
  uint16_t y = bcd2bin(Wire.read()) + 2000;
  
  return DateTime (y, m, d, hh, mm, ss);
}





