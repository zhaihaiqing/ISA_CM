#ifndef __THREAD_ENTRY_H
#define __THREAD_ENTRY_H
#include "main.h"





extern struct rt_semaphore oled_refresh_sem;


int scs_thread_init(void);





void oled_thread_entry(void *par);


void led_thread_entry(void *par);


#endif


























