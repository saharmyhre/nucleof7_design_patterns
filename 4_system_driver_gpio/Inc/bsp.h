#ifndef __BSP_H__
#define __BSP_H__

#include <stdint.h>
#include <stdbool.h>

void led_init(void);
void led_on(void);
void led_off(void);
void button_init(void);
bool get_button_state(void);

#endif  // __BSP_H__
