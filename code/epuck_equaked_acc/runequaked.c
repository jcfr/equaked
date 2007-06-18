
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
#include "runequaked.h"



#include "common.h"


/***********************************************************
 * Earthquake detection via multilateration with EPucks    *
 *    Swarm Intelligence Project - Fall 2006               *
 *                                                         *
 *    Nathan Evans                                         *
 *    Jean-Christophe Fillion-Robin                        *
 ***********************************************************/

/*****
 * Waits for a certain amount of time
 * Note that the effective waiting time is not always the same 
 * (because of possible interrupts).
 */
 
 extern int last_sample_value;
 extern int new_sample;
 
 int ls_value = 4000;
 
 #define PREWINDOW_SIZE 800
 #define POSTWINDOW_SIZE 1800

 unsigned int pre_window[PREWINDOW_SIZE];
 unsigned int pwidx = 0;
 unsigned int post_window[POSTWINDOW_SIZE];
 
 int start_transfer = 0;



// Main program
void run_equaked() {
  	char buffer[80];
	int not_event;
	
	unsigned int count_idx = 0;
	unsigned int count[100];
	int i;
	char order = '0';
	
	for (i=0; i<10; i++) count[i] = 0;
	for (i=0; i<PREWINDOW_SIZE; i++) pre_window[i] = 0;
	for (i=0; i<POSTWINDOW_SIZE; i++) post_window[i] = 0;
	
	//init i
	i = 0;
	
	
	sprintf(buffer, "System is synchronizing ... \n");
    	e_send_uart1_char(buffer, strlen(buffer));
	wait(10000);
	
	switch_2_sync_mode();
	
	//enable A/D conversion
  	ADCON1bits.ADON = 1;
	
  	//init_sys();
	
	e_set_led(1, 1);
  
  
	//allow to scynchronize the event checking loop
 	new_sample = 1;
	while(new_sample); 		// wait until a new sample has been taken
  	new_sample = 1;    		// reset the value to 1
	
	///sync mode
	not_event = 1;
	while (not_event)   	// do this loop until an event has occured
	{
		//new_sample = 1;
		while(new_sample); 		// wait until a new sample has been taken
  		new_sample = 1;
		
		//check last sample value
		//not_event = check_for_ls_event();
		not_event = last_sample_value > 100;
	}
	
	ls_value = last_sample_value;
	
	
	switch_2_detection_mode();
	
	//turn on led 2
	e_set_led(2, 1);
	
	
	//enable A/D conversion
	ADCON1bits.ADON = 1;
	
	//wait a sample, and then start allow to scynchronize the event checking loop
 	new_sample = 1;
	while(new_sample); 		// wait until a new sample has been taken
  	new_sample = 1;    		// reset the value to 1
	
	not_event = 1;
	while (not_event)   	// do this loop until an event has occured
	{
		//new_sample = 1;
		while(new_sample); 		// wait until a new sample has been taken
  		new_sample = 1;
		
		if(count[count_idx]==65535) count_idx++;
		count[count_idx]++;
		//not_event = check_for_event();
		not_event = last_sample_value < 3500;
		
		pre_window[pwidx] = last_sample_value;
		
		//circular use of memory
		if (pwidx<PREWINDOW_SIZE-1) {
			pwidx++;
		} else {
			pwidx = 0;
		}
	}

	while(i < POSTWINDOW_SIZE){
		while(new_sample); // wait until a new sample has been taken
  		new_sample = 1;
		
		post_window[i] = last_sample_value;
		i++;
	}
	
	ADCON1bits.ADON = 0; //enable A/D conversion
	
	IFS0bits.ADIF = 0; //Clear the A/D interrupt flag bit
	
	e_set_led(3, 1); //turn on led 3
	
	//sprintf(buffer, "EQ detected :-), ls_value:%d, eq_value:%d, pwidx:%u\r\n", ls_value, last_sample_value, pwidx);
    	//e_send_uart1_char(buffer, strlen(buffer));
	
	while (order!='1')
		while(e_getchar_uart1(&order)==0);

	/*
	//check selector state (LEFT => send data)
	while (!start_transfer){
        	switch (get_selector()) {
        		case 0: // selector is forced to the right
                		break;
        		case 8: // selector is forced to the left
				start_transfer = 1;
                		break;
        		case 12: // normal operation
				break;
			default:
				break;
		}
	}
	*/

	
	
	sprintf(buffer, "[PREW %u count_idx:%u, count_value:%u]\n", pwidx, count_idx, count[count_idx]);
    	e_send_uart1_char(buffer, strlen(buffer));
	
	for (i=0;i<PREWINDOW_SIZE;i++){
		sprintf(buffer, "%u\n", pre_window[i]);
		//sprintf(buffer, "Light detected :-), value:%d \r\n", last_sample_value);
    		e_send_uart1_char(buffer, strlen(buffer));
	}
	
	e_set_led(6, 1); //turn on led 6
	
	wait(1000);
	
	sprintf(buffer, "[POSTW]\n");
    	e_send_uart1_char(buffer, strlen(buffer));
	
	
	for (i=0;i<POSTWINDOW_SIZE;i++){
		sprintf(buffer, "%u\n", post_window[i]);
		//sprintf(buffer, "Light detected :-), value:%d \r\n", last_sample_value);
    		e_send_uart1_char(buffer, strlen(buffer));
	}
	
	e_set_led(7, 1); //turn on led 7
	
}
