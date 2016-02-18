#include <p30f6014A.h> 
#include <stdlib.h>//for random numbers 
#include <stdio.h>//for random numbers 
#include "a_d/advance_ad_scan/e_prox.h"
#include "motor_led/e_init_port.h"
#include "motor_led/e_epuck_ports.h"
#include "motor_led/advance_one_timer/e_motors.h"
#include "motor_led/advance_one_timer/e_agenda.h"
#include "a_d/advance_ad_scan/e_ad_conv.h"
#include "runBreitenberg_adv.h"
#include "string.h"
#include "math.h" 
#include <uart/e_uart_char.h>

void finding_light (void) {

	e_start_agendas_processing();

	int value0_A, value1_A, value2_A, value3_A, value4_A, value5_A, value6_A, value7_A, averageLight;
	long k;
	//char bufferDebug[40];
	e_init_port();
  	e_init_ad_scan(ALL_ADC);
	e_init_motors();
	LED7 = LED6 = LED0 = LED2 = LED4 = LED1 = LED3 = LED5 = 1;
	
	value0_A = e_get_ambient_light(0);
	value1_A = e_get_ambient_light(1);
	value2_A = e_get_ambient_light(2);
	value3_A = e_get_ambient_light(3);
	value4_A = e_get_ambient_light(4);
	value5_A = e_get_ambient_light(5);
	value6_A = e_get_ambient_light(6);
	value7_A = e_get_ambient_light(7);
	
	averageLight = (value0_A+value1_A+value2_A+value3_A+value4_A+value5_A+value6_A+value7_A)/8-200;
	for(k=0;k<20000;k++){}
	while (1) {
		
		value0_A = e_get_ambient_light(0);
		value1_A = e_get_ambient_light(1);
		value2_A = e_get_ambient_light(2);
		value3_A = e_get_ambient_light(3);
		value4_A = e_get_ambient_light(4);
		value5_A = e_get_ambient_light(5);
		value6_A = e_get_ambient_light(6);
		value7_A = e_get_ambient_light(7);
		if ((value0_A+value7_A)/2 < averageLight-100) {
			LED0 = LED7 = 1;
			LED1 = LED2 = LED3 = LED4 = LED5 = LED6 = 0;
			e_set_speed_left(800);
			e_set_speed_right(800);
			for(k=0; k<100000; k++) {}
		}
		else if ((value0_A+value1_A)/2 < averageLight) {
			LED0 = LED1 = 1;
			LED1 = LED3 = LED4 = LED5 = LED6 = LED7 = 0;
			e_set_speed_left(800);
			e_set_speed_right(400);
			for(k=0; k<100000; k++) {}
		}
		else if ((value1_A+value2_A)/2 < averageLight) {
			LED1 = LED2 = 1;
			LED0 = LED3 = LED4 = LED5 = LED6 = LED7 = 0;
			e_set_speed_left(400);
			e_set_speed_right(-400);
			for(k=0; k<100000; k++) {}
		}
		else if ((value2_A+value3_A)/2 < averageLight) {
			LED2 = LED3 = 1;
			LED0 = LED1 = LED4 = LED5 = LED6 = LED7 = 0;
			e_set_speed_left(600);
			e_set_speed_right(-600);
			for(k=0; k<100000; k++) {}
		}
		else if ((value3_A+value4_A)/2 < averageLight) {
			LED3 = LED4 = 1;
			LED0 = LED1 = LED2 = LED5 = LED6 = LED7 = 0;
			e_set_speed_left(800);
			e_set_speed_right(-800);
			for(k=0; k<100000; k++) {}
		}
		else if ((value7_A+value6_A)/2 < averageLight) {
			LED7 = LED6 = 1;
			LED0 = LED1 = LED2 = LED3 = LED4 = LED5 = 0;
			e_set_speed_left(400);
			e_set_speed_right(800);
			for(k=0; k<100000; k++) {}
		}
		else if ((value6_A+value5_A)/2 < averageLight) {
			LED6 = LED5 = 1;
			LED0 = LED1 = LED2 = LED3 = LED4 = LED7 = 0;
			e_set_speed_left(-400);
			e_set_speed_right(400);
			for(k=0; k<100000; k++) {}
		}
		else if ((value5_A+value4_A)/2 < averageLight) {
			LED5 = LED4 = 1;
			LED0 = LED1 = LED2 = LED3 = LED6 = LED7 = 0;
			e_set_speed_left(-600);
			e_set_speed_right(600);
			for(k=0; k<100000; k++) {}
		}
		else {
			LED7 = LED6 = LED0 = LED2 = LED4 = LED1 = LED3 = LED5 = 1;
			e_set_speed_left(0);
			e_set_speed_right(0);
			for(k=0; k<100000; k++) {}
		}		
	}
}
