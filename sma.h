#ifndef SMA_H
#define SMA_H

#include <limits.h>

#define SMA_ERROR (ULONG_MAX)

// plausibility values
#define MAXTOTAL 1000000000L
#define MAXDAY 50000L
#define MAXSPOT 10000L

bool initialiseSMAConnection(void);
bool logonSMAInverter(void);
unsigned long getInstantACPower(void);
unsigned long getTotalPowerGeneration(void);
unsigned long getLastDateTime(void); // returns seconds since 2000

#endif
