#include <p30f6014A.h> 
#include <stdlib.h>//for random numbers 
#include <a_d/e_prox.h>
#include <motor_led/e_init_port.h>
#include <motor_led/e_motors.h>
#include <a_d/e_ad_conv.h>
#include "string.h"
#include "math.h" 
#include <motor_led/e_epuck_ports.h>
#include <motor_led/e_led.h>
#include <uart/e_uart_char.h>

void finding_light (void) {

	int value0_A, value1_A, value2_A, value3_A, value4_A, value5_A, value6_A, value7_A, 
		value0, value1, value2, value3, value4, value5, value6, value7;
	long k;
	char buffer[1];

	e_init_port();
  	e_init_prox();
	e_init_motors();
	
	while (1) {
	
		value0 = e_get_prox(0);
		value1 = e_get_prox(1);
		value2 = e_get_prox(2);
		value3 = e_get_prox(3);	
		value4 = e_get_prox(4);	
		value5 = e_get_prox(5);
		value6 = e_get_prox(6);
		value7 = e_get_prox(7);
		
		value0_A = e_get_ambient_light(0);
		value1_A = e_get_ambient_light(1);
		value2_A = e_get_ambient_light(2);
		value3_A = e_get_ambient_light(3);
		value4_A = e_get_ambient_light(4);
		value5_A = e_get_ambient_light(5);
		value6_A = e_get_ambient_light(6);
		value7_A = e_get_ambient_light(7);

		if (value6 > 1000 && value7 > 1000) {

				e_set_speed_right(-200);
				e_set_speed_left(200);
				for(k=0; k<30000; k++) { asm("nop"); }

		} else if (value2 > 1000 || value0 > 1000 || value1 > 1000 || value7 > 1000) {	
					
				e_set_speed_right(200);
				e_set_speed_left(-200);
				for(k=0; k<30000; k++) { asm("nop"); }

		} else if (value5 > 1000 || value6 > 1000) {

				e_set_speed_right(-200);
				e_set_speed_left(200);
					
				for(k=0; k<30000; k++) { asm("nop"); }
			
		} else if (value2 < 1000 && value0 < 1000 && value1 < 1000 && value7 < 1000 && value5 < 1000 && value6 < 1000) {

				if ( ((value1_A < 4000) || (value2_A < 4000)) && ((value0_A < 4000) || (value7_A < 4000)) ) {
		
						LED0 = LED7 = 1;
						LED1 = LED2 = LED3 = LED4 = LED5 = LED6 = 0;
						e_set_speed_left(800);
						e_set_speed_right(800);
						for(k=0; k<1000000; k++) { asm("nop"); }

				} else if ( (value1_A < 4000) || (value2_A < 4000) ) {
						LED0 = LED7 = LED3 = LED4 = LED5 = LED6 = 0;
						LED1 = LED2 = 1;
						e_set_speed_left(500);
						e_set_speed_right(-500);
						for(k=0; k<1000000; k++) { asm("nop"); }
		
				} else if ( (value3_A < 3000) || (value4_A < 3000) ) {
						LED0 = LED7 = LED1 = LED2 = LED5 = LED6 = 0;
						LED3 = LED4 = 1;
						e_set_speed_left(500);
						e_set_speed_right(-500);
						for(k=0; k<1000000; k++) { asm("nop"); }				
		
				} else if ((value5_A < 4000) || (value6_A < 4000) ) {
						LED0 = LED7 = LED3 = LED4 = LED1 = LED2 = 0;
						LED5 = LED6 = 1;
						e_set_speed_left(-500);
						e_set_speed_right(500);
						for(k=0; k<1000000; k++) { asm("nop"); }
		
				} else if ( (value0_A < 4000) || (value7_A < 4000) ) {
						LED0 = LED7 = 1;
						LED1 = LED2 = LED3 = LED4 = LED5 = LED6 = 0;
						e_set_speed_left(800);
						e_set_speed_right(800);
						for(k=0; k<1000000; k++) { asm("nop"); }

				} else if ( (value0_A < 6000) || (value1_A < 6000) || (value2_A < 7000) || (value3_A < 7000) || (value4_A < 7000) || (value7_A < 7000) || (value5_A < 7000) || (value6_A < 7000)) {
						LED7 = LED6 = LED0 = LED2 = LED4 = LED1 = LED3 = LED5 = 1;
						e_set_speed_left(800);
						e_set_speed_right(-800);
						for(k=0; k<1000000; k++) { asm("nop"); }

				} else {
		
				}
		} else {
				// for completion
		}	
	
	}
}










 