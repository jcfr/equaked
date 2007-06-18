
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
#include "p30f6014a.h"
#include "stdio.h"
#include "string.h"

#include "./codec/e_sound.h"
#include "./motor_led/e_init_port.h"
#include "./motor_led/e_led.h"
#include "./motor_led/e_motors.h"
#include "./uart/e_uart_char.h"
#include "./a_d/advance_ad_scan/e_acc.h"
#include "./a_d/advance_ad_scan/e_prox.h"
#include "./a_d/advance_ad_scan/e_ad_conv.h"


/***********************************************************
 * Earthquake detection via multilateration with EPucks    *
 *  Main shell....                                         *
 *                                                         *
 *    Swarm Intelligence Project - Fall 2006               *
 *                                                         *
 *    Nathan Evans                                         *
 *    Jean-Christophe Fillion-Robin                        *
 ***********************************************************/

// Main program
int main() {
  char buffer[80];
  int accx = 0, accy = 0, accz = 0;

  // Running mode
  e_init_port();    // configure port pins
  //e_start_agendas_processing();
  e_init_motors();
  e_init_uart1();   // initialize UART to 115200 Kbaud
  e_init_ad_scan();

  // Reset if Power on (some problem for few robots)
  if (RCONbits.POR) {
    RCONbits.POR = 0;
    __asm__ volatile ("reset");
  }

   sprintf(buffer, "accelerometer detection ON\r\n");
   e_send_uart1_char(buffer, strlen(buffer));

  
    while(1){
	accx=e_get_acc(0);
	accy=e_get_acc(1);
	accz=e_get_acc(2);
    	sprintf(buffer, "%d %d %d\r\n", accx, accy, accz);
    	e_send_uart1_char(buffer, strlen(buffer));
    }

  return 0;
}
