#include <string.h>
#include <util.h>
#include "sma.h"
#include "sma_web.h"
#include "smaLcd.h"

extern int readyPin=A1;

#define SECONDS(n)  (n * 1000)



void bt_clear(void) {
  char c;
  util::msgln("bt_clear");
    while (Serial3.available()) {
        c=Serial3.read();
	util::msg("%c",c);
        delay(10);
    }
    util::msgln("end bt_clear");
}

bool bt_wait_string(char *str, int len, unsigned long ms) {
    char *p = str;
    char last = 0;
    char last_prior = 0;
    unsigned long timeout = millis() + ms;
    
    util::msgln("bt_wait_string");

    while (millis() <= timeout) {
        while (Serial3.available()) {
            last = *p++ = Serial3.read();
	    util::msg("%.2x ",last);
            if (last == '\n' && last_prior == '\r') {
                *(p - 2) = 0;
		util::msgln("");
		util::msgln(str); // print string again as string
		util::msgln("bt_wait_string end: new line");
                return p - 2 - str;
            }
            last_prior = last;

            if (p - str == len - 1) {
                *p = 0;
		util::msgln("bt_wait_string end: buffer overflow");
                return true;
            }
            timeout = millis() + ms;
        }
    }
    *p = 0;
    util::msgln("bt_wait_string end: timeout ");
    return p - str;
}

void bt_send(const char *str) {

  util::msgln("bt_send: ");
    util::msg("\\r\\n+");
    util::msg(str);
    util::msgln("\\r\\n");

    Serial3.write("\r\n+");
    Serial3.write((char*)str);
    Serial3.write("\r\n");
}

char wait_state(void) {
    char state = -1;
    char str[128] = { 0 };

    /*
     * XXX Don't need to test the entire string - just wait
     * for BTSTATE: and get the first character after that.
     * XXX These strings should go in flash.
     */
    if (bt_wait_string(str, sizeof(str), SECONDS(5))) {
      util::msgln("rcvd: %s",str);
      if (!strncmp(str, "+BTSTATE:0", 10)) {
	state = 0;
      } else if (!strncmp(str, "+BTSTATE:1", 10)) {
            state = 1;
        } else if (!strncmp(str, "+BTSTATE:2", 10)) {
            state = 2;
        } else if (!strncmp(str, "+BTSTATE:3", 10)) {
            state = 3;
        } else if (!strncmp(str, "+BTSTATE:4", 10)) {
            state = 4;
        } else if (!strncmp(str, "+RTINQ=0,80,25,8,C3,2A", 22)) {    /* XXX include this from sma.ino */
            state = 5;
        } else if (!strncmp(str, "~", 1)) { /* getting data packets */
            state = 4;
        }
    }
    util::msgln("State found: 0x%.2x",state);
    return state;
}

bool bt_connected(void) {
  int status=analogRead(readyPin);
  // util::msgln("bt_connected: status=%#.2x",status);
  return(status > 300); // if connected, status=660-720
}

bool pair(void) {
    char state = -1;
    unsigned long timeout;

    bt_clear();

    /*
     * Wait for device to settle before doing anything. Retain
     * the last state that we achieved - if we timeout then we
     * should be in a known state.
     */
    for (timeout = millis() + SECONDS(5); millis() < timeout; ) {
        state = wait_state();
    }

    if (state == -1) {
        /*
         * Nothing in timeout period. We are either already
         * connected and the inverter is waiting for us, or
         * we're in command mode.
         */
        if (bt_connected()) {
          util::msgln("pair: already connected");
            return true;
        }

        /*
         * Assume we're in command mode.
         */
        state = 1;
    }

    timeout = millis() + SECONDS(10);
    while (millis() < timeout) {
        switch (state) {
            case 1:
                bt_send("INQ=1");
                timeout = millis() + SECONDS(30);
                break;

            case 4:
                return true;

            case 5:
                bt_send("CONN=0,80,25,8,C3,2A");    /* XXX include this from sma.ino */
                timeout = millis() + SECONDS(10);
                break;

            default:
                break;
        }

        state = wait_state();
    }

    /*
     * So we aren't receiving data messages, no response
     * from command messages either, or we didn't get any
     * thing at all from the inverter or BT module. I
     * think we can consider that a fail.
     */
    return false;
}

bool bt_init() {
  // bt_send("STWMOD=1");//set the bluetooth work in master mode
  // bt_send("STNA=SeeedBTMaster");//set the bluetooth name as "SeeedBTMaster"
  // bt_send("STAUTO=0");// Auto-connection is forbidden here 
  
  bool status=false;

  // in first loop try 

  int trial;

  for(trial=0; trial<2 && status==false; trial++){
    // during first trial pair and init only if not connected
    if(!bt_connected() && trial==0){
      util::println("Starting pair");
      lcd.printStatus('P'); // Pair
      status=pair();
      util::msgln("pair=%#x",status);
      if(!status){
	util::msgln("(I) bt_init: pairing has failed. Try initSMA anyway\n");
	// return false; try connect anyway
      }

      util::println("Starting initialise");
      lcd.printStatus('I'); // initialize
      status=initialiseSMAConnection();
      util::msgln("initialiseSMAConnection=%#x",status);
      if(!status){
	util::println("(E) bt_init: init has failed.\n");
	if(trial>0) 
	  return false;
      }
    }
  
    util::println("Starting logon SMA");
    lcd.printStatus('L'); // Logon
    status=logonSMAInverter();
    util::msgln("logonSMAInverter=%#x",status);
  }
  return status;
}

bool bt_get_status(unsigned long *total_kwh, unsigned long *day_kwh, unsigned long *spot_ac, unsigned long *time) {

  bool status=false;

  util::println("Starting getInstantACPower");
  lcd.printStatus('C'); // current power
    *spot_ac = getInstantACPower();
    if(*spot_ac != SMA_ERROR){
      status=true;
      util::println("done get Instant AC Power");
      util::msgln("Instant AC Power: %lu",*spot_ac);
    }else{
      util::println("(E) getInstantACPower has failed");
    }

    util::println("Starting getTotalPowerGeneration");
    lcd.printStatus('T'); // total power generation
    *total_kwh = getTotalPowerGeneration();
    if(*total_kwh!= SMA_ERROR){
      status=true;
      util::println("done get total power generation");
      util::msgln("Total generation: %lu",*total_kwh);
    }else{
      util::println("(E) getTotalPowerGeneration has failed");
    }

    util::println("Starting getDayPowerGeneration");
    lcd.printStatus('D'); // today's power generation
    *day_kwh = getDayPowerGeneration();
    if(*day_kwh!= SMA_ERROR){
      status=true;
      util::println("done getDayPowerGeneration");
      util::msgln("Today's generation: %lu",*day_kwh);
    }else{
      util::println("(E) getDayPowerGeneration has failed");
    }

    util::println("Starting getLastDateTime");
    lcd.printStatus('Z'); // Time
    *time = getLastDateTime();
    util::println("getLastDateTime done");
    util::msgln("Last Time: %lu, millis=%lu",*time, millis());
    if(!*time) util::println("(E) getLastDateTime has failed");

    return status;
}
