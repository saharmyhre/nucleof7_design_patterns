#ifndef __TIMEBASE__H
#define __TIMEBASE__H

#include <stdint.h>

void timebase_init(void);
uint32_t get_ticks(void);
void delay(uint32_t delay);

#endif // __TIMEBASE_H
