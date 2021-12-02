/**
 * Copyright (c) 2021 WIZnet Co.,Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _TIMER_H_
#define _TIMER_H_

/**
  * ----------------------------------------------------------------------------------------------------
  * Macros
  * ----------------------------------------------------------------------------------------------------
  */
/* Timeout */
#define RECV_TIMEOUT (1000 * 10) // 10 seconds

/**
  * ----------------------------------------------------------------------------------------------------
  * Functions
  * ----------------------------------------------------------------------------------------------------
  */
/* Timer */
void wizchip_1ms_timer_initialize(void (*callback)(void));
bool wizchip_1ms_timer_callback(struct repeating_timer *t);

/* Delay */
void wizchip_delay_ms(uint32_t ms);

#endif /* _TIMER_H_ */
