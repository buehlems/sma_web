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


#ifndef SMARELAY_H
#define SMARELAY_H

// #define BT_RN  // Bluetooth shield with /r/n
#define BT_AT  // Bluetooth shield with AT

#include <avr/pgmspace.h>
#include <Time.h>

/*
 * Pins.
 */
// #define RX_BTBEE    6   /* Normal serial port */
// #define TX_BTBEE    7   /* Normal serial port */
#define CD_BTBEE    A1   /* connect to pio1 to detect connection status */
// #define POWER_BTBEE 5   /* turn on / off BT (Stalker v2.0) */
// #define DISCONNECT_BTBEE 13 /* connect to pio0; high will disconnect */

#define MASTER HIGH
#define SLAVE LOW

#define HOST_LED    8

#include "bt.h"

#endif
