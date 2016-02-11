#include "p30f6014A.h"
#include "stdio.h"
#include "string.h"

#include "uart/e_uart_char.h"
#include "motor_led/e_init_port.h"
#include "motor_led/e_epuck_ports.h"
#include "motor_led/advance_one_timer/e_motors.h"
#include "motor_led/advance_one_timer/e_agenda.h"
#include "finding_Light.h"
#include "imageCapture.h"
#include "findRed.h"
#include "followGreen.h"
#include "followHand.h"

int getselector() {
	return SELECTOR0 + 2*SELECTOR1 + 4*SELECTOR2 + 8*SELECTOR3;
}

int main() {
	char bufferDebug[80];
	int selector;
//init
	e_init_port();
	e_init_uart1();
	e_init_motors();

	selector=getselector();
	
	if (selector==0) {
	} else if (selector==1) {
		//sprintf(bufferDebug, "img Cap\n\r");
		//e_send_uart1_char(bufferDebug,strlen(bufferDebug));
		imageCapture();
	} else if (selector==2) {
		//sprintf(bufferDebug, "Red\n\r");
		//e_send_uart1_char(bufferDebug,strlen(bufferDebug));
		findRed();
	} else if (selector==3) {
		//sprintf(bufferDebug, "Green\n\r");
		//e_send_uart1_char(bufferDebug,strlen(bufferDebug));
		followGreen();
	} else if (selector==4) {
		followHand();
	} else if (selector==5) {
		finding_light();
	} else if(selector==6){
		avoid_light();
	}else{
	
	}

	
	while(1);
}

