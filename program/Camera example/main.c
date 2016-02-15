#include "p30f6014A.h"
#include "stdio.h"
#include "string.h"

#include "uart/e_uart_char.h"
#include "motor_led/e_init_port.h"
#include "motor_led/e_epuck_ports.h"
#include "motor_led/advance_one_timer/e_motors.h"
#include "motor_led/advance_one_timer/e_agenda.h"
#include "finding_Light.h"
#include "avoidlight.h"
#include "imageCapture.h"
#include "findRed.h"
#include "followGreen.h"
#include "followHand.h"
#include "runBreitenberg_adv.h"

int getselector() {
	return SELECTOR0 + 2*SELECTOR1 + 4*SELECTOR2 + 8*SELECTOR3;
}

int main() {
//	char bufferDebug[80];
	int selector;
//init
	e_init_port();
	e_init_uart1();
	e_init_motors();

	selector=getselector();
	
	if (selector==0) {
		run_breitenberg_follower();
	} else if (selector==1) {
		finding_light();
	} else if (selector==2) {
		avoid_light();
	} else if (selector==3) {
		run_breitenberg_shocker();
	} else if (selector==4) {
		followHand();
	} else if (selector==5) {
	} else if(selector==6){
	}else{
	
	}

	
	while(1);
}

