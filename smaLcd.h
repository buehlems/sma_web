/*

sma_web

Latest version found at https://github.com/buehlems/sma_web
Licence
Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
http://creativecommons.org/licenses/by-nc-sa/3.0/

You are free:
    to Share - to copy, distribute and transmit the work
    to Remix - to adapt the work
Under the following conditions:
    Attribution - You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work).
    Noncommercial - You may not use this work for commercial purposes.
    Share Alike - If you alter, transform, or build upon this work, you may distribute the resulting work only under the same or similar license to this one.

Work is copyright Markus Buehler, (c)2014.
*/


#ifndef SMALCD_H
#define SMALCD_H

#include <LiquidCrystal.h>
#include "bt.h"

class smaLcd : public LiquidCrystal {
 public:
  smaLcd(uint8_t rs, uint8_t rw, uint8_t enable,
	 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) : 
    LiquidCrystal(rs, rw, enable, d0, d1, d2, d3)
    {}
    void printConnected(void);
    void printStatus(char c);
    void printTotal(unsigned long total_kwh);
    void printDay(unsigned long day_kwh);
    void printCurrent(unsigned long spot_ac);
    void printCountdown(long n);
 private:
    unsigned long div(unsigned long v, unsigned long d); // divides and rounds
    void prepare(int x, int y, int l); // set cursor and clear reserved space
    void fillLeadingBlanks(unsigned long v, int digits);

};

#endif /* SMALCD_H */
