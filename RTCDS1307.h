#ifndef RTCDS1307_h
#define RTCDS1307_h

#include <Wire.h>
#include <avr/pgmspace.h>
#include <DateTime.h>
#include <Arduino.h> 

#define DS1307_ADDRESS 0x68




// Public Domain code by JeeLabs http://news.jeelabs.org/code/
// Code was trimmed but not modified by DesignLibre.

// Simple general-purpose date/time class (no TZ / DST / leap second handling!)


// RTC based on the DS1307 chip connected via I2C and the Wire library
class RTCDS1307 
{
public:
  static uint8_t begin(void);
    static void adjust(const DateTime& dt);
    uint8_t isrunning(void);
    static DateTime now();
};


#endif