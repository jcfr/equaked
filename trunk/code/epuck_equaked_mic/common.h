
/* 
* This file is part of Equaked.
*
* Equaked is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* any later version.
*
* Equaked is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _COMMON_H_
#define _COMMON_H_

#include "p30f6014a.h"
#include "stdio.h"
#include "string.h"

#include "./motor_led/e_init_port.h"
#include "./motor_led/e_epuck_ports.h"
#include "./a_d/e_accelerometer.h"
#include "./motor_led/e_led.h"
#include "./motor_led/e_motors.h"
#include "./uart/e_uart_char.h"
#include "./a_d/e_ad_conv.h"

// Waits for a certain amount of time
// Note that the effective waiting time is not always the same (because of possible interrupts).
void wait(unsigned long num);

void init_ad_scan(void);

void switch_2_sync_mode();
void switch_2_detection_mode();

void init_sys(void);

//void calculate_average(int current_sample);
int check_for_ls_event(void);
int check_for_eq_event(void);
//int check_for_event(void);

//int get_sample(void);

int get_selector();


#endif //_COMMON_H_
