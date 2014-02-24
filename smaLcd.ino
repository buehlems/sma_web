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


#include "smaLcd.h"

unsigned long smaLcd::div(unsigned long v, unsigned long d){
  return((v+(d>>2))/d);
}

void smaLcd::fillLeadingBlanks(unsigned long v, int digits){
  int n=1;

  // how many digits does v have?
  while(v>9){
    v/=10;
    n++;
  }
  for(digits=digits-n; digits>0; digits--){
    print(' ');
  }
}

void smaLcd::printConnected(void){
  setCursor(14, 1);
  if(bt_connected()){
    print("C");
  }else{
    print("-");
    }
}

void smaLcd::printStatus(char c){
  setCursor(15, 1);
  print(c);
}

void smaLcd::prepare(int x, int y, int l){
  setCursor(x,y);
  // clear space;
  for(int i=0; i<l; i++){
    print(' ');
  }
  setCursor(x,y); // set cursor at beginning
}

void smaLcd::printTotal(unsigned long value){
  prepare(0,0,9); // 9 characters at 0,0: 234'567kWh
  value=div(value,1000);
  fillLeadingBlanks(value,6);
  print(value);
  print("kWh");
}

void smaLcd::printDay(unsigned long value){
  unsigned long vint;
  prepare(0,1,7); // 7 characters at 0,1: 99.9kWh
  value=div(value,100);
  vint=value/10;
  fillLeadingBlanks(vint,2);
  print(vint);
  print('.');
  print(value%10);
  print("kWh");
}

void smaLcd::printCurrent(unsigned long value){
  prepare(8,1,5); // 5 characters at 0,1: 1000W
  fillLeadingBlanks(value,4);
  print(value);
  print("W");
}

void smaLcd::printCountdown(long n){
  prepare(13,0,3);
  if(n>=0){
    fillLeadingBlanks(n,3);
  }else{
    fillLeadingBlanks(-n,2);
  }
  print(n);
}