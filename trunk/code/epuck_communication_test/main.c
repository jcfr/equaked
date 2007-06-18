
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
/***********************************************************
 * Earthquake detection via multilateration with EPucks    *
 *  Main shell....                                         *
 *                                                         *
 *    Swarm Intelligence Project - Fall 2006               *
 *                                                         *
 *    Nathan Evans                                         *
 *    Jean-Christophe Fillion-Robin                        *
 ***********************************************************/

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


#define uart_send_static_text(msg) do { e_send_uart1_char(msg,sizeof(msg)-1); while(e_uart1_sending()); } while(0)
#define uart_send_text(msg) do { e_send_uart1_char(msg,strlen(msg)); while(e_uart1_sending()); } while(0)
    
// Main program
int main() {
  char buffer[80];
  int i=0;
  char order=NULL;

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


  //send 10 lines + 1
  for (i=0;i<10;i++){
  	sprintf(buffer, "is the %d little genius in the bottle?\r\n", i);
	uart_send_text(buffer);
 	//e_send_uart1_char(buffer, strlen(buffer));
  }

  uart_send_static_text("HIT (1), (2) or any other key\r\n");

  //wait for data
  while (e_getchar_uart1(&order)==0);

  //check order
  switch(order){
  	case '1':
		uart_send_static_text("1) Catch the genius\r\n");
		break;
	case '2':
		uart_send_static_text("2) Fake the genius\r\n");
		break;
	default:
		uart_send_static_text("*) Ask the widget behind the big chair!");
		break;	
  }
  
  while(1);

  return 0;
}
