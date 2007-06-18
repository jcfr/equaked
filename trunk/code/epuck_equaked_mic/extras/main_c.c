#include "p30f6014A.h"
#include "stdio.h"
#include "string.h"

#include "./codec/e_sound.h"
#include "./motor_led/e_init_port.h"
#include "./a_d/e_accelerometer.h"
#include "./motor_led/e_led.h"
#include "./motor_led/e_motors.h"
#include "./uart/e_uart_char.h"
#include "./a_d/e_ad_conv.h"
#include "./a_d/e_prox.h"
#include "math.h"
#include "ComModule.h"
#include "./I2C/e_I2C_protocol.h"
#include "runcollaboration.h"
#include "runaccelerometer.h"
#include "runbreitenberg.h"
#include "runlocatesound.h"
#include "runwallfollow.h"
#include "runacclive.h"
#include "utility.h"

#define PI 3.14159265358979

int main() {
	char buffer[80];
	int selector;

	//system initialization 
	e_init_port();
	e_init_uart1();

	//Reset if Power on (some problem for few robots)
	if (RCONbits.POR) {
		RCONbits.POR=0;
		__asm__ volatile ("reset");
	}

	// Decide upon program
	selector=getselector();
	sprintf(buffer, "Starting with selector pos %d\r\n", selector);
	e_send_uart1_char(buffer, strlen(buffer));
	if (selector==0) {
		run_accelerometer();
	} else if (selector==1) {
		run_locatesound();
	} else if (selector==2) {
		run_wallfollow();
	} else if ((selector==11) || (selector==12) || (selector==13)) {
		run_collaboration();
	} else {
		run_breitenberg();
	}

	while(1);
	return 0;
}

