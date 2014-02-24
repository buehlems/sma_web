#ifndef BT_H
#define BT_H

extern int readyPin;

bool bt_init();
bool bt_connected();
bool bt_get_status(unsigned long *total_kwh, unsigned long *day_kwh, unsigned long *spot_ac, unsigned long *now);

#endif
