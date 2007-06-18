
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
#include "common.h"

/*****************************
 *
 * Common functionality between capturing velocity and detection of
 * earthquakes. Note that this initialization code is largely based
 * off of the locate_sound project (in order to set the onboard sampling
 * rates, etc.
 *
 *****************************/


/* defines used in ad_conv_int.c */
//#define ACC_SAMP_NB 600		// number of accelerometer samples to store
//#define LS_SAMP_NB 100		// number of light sensor samples to store

/* defines used in main.c                          */
#define MEAN_MAX_SAMPL 100		// Length of the mean_table
#define MEAN_MAX_SAMPL_INV 0.01	// Inversed value of MEAN_MAX
#define PERCENT 0.1		// Defines range to distinguish between noise an signal


//int acc_samps[ACC_SAMP_NB];	// Array to store the acc values
//int ls_samps[LS_SAMP_NB];	// Array to store the ls values
int new_sample;
unsigned int last_sample_value = 0;	 //sample value of last A/D scan 

float mean_table[MEAN_MAX_SAMPL];
int mean_nb;
float mean;
float signal_max, signal_min;

unsigned int mode = 0; // 0: scyn mode (light peak detection)
                       // 1: detection mode (accelerometer peak detection)


/* 
 * Waits for a certain amount of time
 *  Note that the effective waiting time is not always the same 
 *  (because of possible interrupts).
 */
void wait(unsigned long num) {
  while (num > 0) {num--;}
}

/**********************************************************************
 * Initialize ADC settings... (sample rate, etc)
 * Set up the different ADC register to process the AD conversion
 * by scanning the used AD channels. Each value of the channels will
 * be stored in a different AD buffer register and an inturrupt will
 * occur at the end of the scan.
 *
 * @param  void
 * @return void
 * 
 *  
 **********************************************************************/
void init_ad_scan(void)
{
	ADCON1 = 0;					//reset to default value
	ADCON2 = 0;					//reset to default value
	ADCON3 = 0;					//reset to default value
	ADCHS = 0;					//reset to default value

	// ADPCFGbits.PCFGx 
	// = 0 for Analog input mode, 
	// = 1 for digital input mode (default)
	ADPCFGbits.PCFG0 = 1;   // Debugger 
	ADPCFGbits.PCFG1 = 1;   // Debugger 
	ADPCFGbits.PCFG2 = 0;   // micro 0
	ADPCFGbits.PCFG3 = 0;   // micro 1
	ADPCFGbits.PCFG4 = 0;   // micro 2
	ADPCFGbits.PCFG5 = 0;   // axe x acc
	ADPCFGbits.PCFG6 = 0;   // axe y acc
	ADPCFGbits.PCFG7 = 0;   // axe z acc
	ADPCFGbits.PCFG8 = 0;   // ir0
	ADPCFGbits.PCFG9 = 0;   // ir1
	ADPCFGbits.PCFG10 = 0;  // ir2
	ADPCFGbits.PCFG11 = 0;  // ir3
	ADPCFGbits.PCFG12 = 0;  // ir4
	ADPCFGbits.PCFG13 = 0;  // ir5
	ADPCFGbits.PCFG14 = 0;  // ir6
	ADPCFGbits.PCFG15 = 0;  // ir7

	//specifie the channels to be scanned
	ADCSSLbits.CSSL0 = 0;   // Debugger
	ADCSSLbits.CSSL1 = 0;   // Debugger
	ADCSSLbits.CSSL2 = 0;   // micro 0
	ADCSSLbits.CSSL3 = 0;   // micro 1
	ADCSSLbits.CSSL4 = 0;   // micro 2
	ADCSSLbits.CSSL5 = 0;   // axe x acc
	ADCSSLbits.CSSL6 = 0;   // axe y acc
	ADCSSLbits.CSSL7 = 0;   // axe z acc
	ADCSSLbits.CSSL8 = 0;   // ir0
	ADCSSLbits.CSSL9 = 0;   // ir1

	ADCON1bits.FORM = 0;	//output = unsigned int
	ADCON1bits.ASAM = 1;	//automatic sampling on
	ADCON1bits.SSRC = 7;	//automatic convertion mode

	ADCON2bits.SMPI = 3-1;	//interupt on sample
	ADCON2bits.CSCNA = 1;	//scan channel input mode on
	
	ADCON3bits.SAMC = 1;	//number of cycle between acquisition and conversion
	ADCON3bits.ADCS = 19;	//ADC conversion clock, see dsPIC30F60* technical specs p139

	IFS0bits.ADIF = 0;	//Clear the A/D interrupt flag bit
	IEC0bits.ADIE = 1;	//Set the A/D interrupt enable bit

	ADCON1bits.ADON = 0;	//enable AD conversion
}

void switch_2_sync_mode(){
	ADCON1bits.ADON = 0;	//disable AD conversion
	IFS0bits.ADIF = 0;	//Clear the A/D interrupt flag bit
	ADCSSLbits.CSSL7 = 0;   // axe z acc
	ADCSSLbits.CSSL8 = 1;   // ir0
}

void switch_2_detection_mode(){
	ADCON1bits.ADON = 0;	//disable AD conversion
	IFS0bits.ADIF = 0;	//Clear the A/D interrupt flag bit
	ADCSSLbits.CSSL7 = 1;   // axe z acc
	ADCSSLbits.CSSL8 = 0;   // ir0

}

/**********************************************************************
 * Save the AD buffer registers in differents arrays
 *
 * @param  void
 * @return void
 **********************************************************************/
void __attribute__((__interrupt__)) _ADCInterrupt(void)
{
	//volatile unsigned int * adcPtr;
	//static unsigned int j = 0, i = 0; // ID of the next acc and ls scan 
  
	//Clear the A/D Interrupt flag bit or else the CPU will
	//keep vectoring back to the ISR
	IFS0bits.ADIF = 0;

	//////////////////////////////////////
	//  Copy of the buffer regs in the  //
	//  approprieted array              //
	//////////////////////////////////////
	//adcPtr = &ADCBUF0;

	//last_sample_value = *adcPtr;
	last_sample_value = ADCBUF0;

	new_sample = 0; // indicate a new sample taken
}


void init_sys(void){

  //int j;

  //mean_nb = 0;			// start to fill up the table from position 0
  new_sample = 1;		// no sample has been taken

  while(new_sample); 		// wait until a new sample has been taken
  new_sample = 1;    		// reset the value to 1

  // initialize the table of average values
  // save signal level
  //mean=(float)last_sample_value;     // start at a given average value

  //for (j=0; j<MEAN_MAX_SAMPL; j++){      // fill the mean_table with predefined values
  //  mean_table[j]= mean * MEAN_MAX_SAMPL_INV;
  //}
      
  //signal_min = mean - PERCENT * mean;	// predefine level for eventdetecting
  //signal_max = mean + PERCENT * mean;

}

/*
void calculate_average(int current_sample)
{
	
	while(new_sample); 				// wait until a new sample has been taken
	new_sample = 1;    				// reset the value to 1
	
	
	mean = mean - mean_table[mean_nb];
	mean_table[mean_nb] = MEAN_MAX_SAMPL_INV * (float)current_sample;
	mean += mean_table[mean_nb];
				
	// adapt treshold to detect an event
	signal_min = mean - PERCENT * mean;
	signal_max = mean + PERCENT * mean;
	
	// ensure a circular memory usage
	if (mean_nb<MEAN_MAX_SAMPL-1)
		mean_nb++;
	else
		mean_nb = 0;
}
*/

int check_for_ls_event(void){
	return last_sample_value > 100;
}

int check_for_eq_event(void){
	return last_sample_value < 3050;
}

/*
int check_for_event(void)
{
	int not_event;  
	int current_sample;
	
	// get one single sample
	current_sample=last_sample_value;

	// Detect event on any of the 3 microphones
	not_event = ( current_sample<signal_max && current_sample>signal_min ); 
	
	// dynamically calculates the new average value of the noise
	calculate_average(current_sample);

	return not_event;   // if no event, return 1 
	                    // if event, return 0
}
*/

// Returns the position of the selector
int get_selector() {
        return SELECTOR0 + 2*SELECTOR1 + 4*SELECTOR2 + 8*SELECTOR3;
}





