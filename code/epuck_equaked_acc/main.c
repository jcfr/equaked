
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

#include "common.h"

//EQUAKED: equake detection
//VELOCITY: analyse medium velocity

#include "runequaked.h"


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
  //char buffer[80];

  // Initialize system and sensors
  e_init_uart1();
  e_init_port();
  e_init_motors();
  init_ad_scan();

  // Reset if Power on (some problem for few robots)
  if (RCONbits.POR) {
    RCONbits.POR = 0;
    __asm__ volatile ("reset");
  }

  run_equaked();

  while(1);

  return 0;
}
