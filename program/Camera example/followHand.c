#include "motor_led/e_init_port.h"
#include "motor_led/e_epuck_ports.h"
#include "a_d/advance_ad_scan/e_prox.h"
#include "motor_led/advance_one_timer/e_motors.h"
#include "motor_led/advance_one_timer/e_agenda.h"
#include "a_d/advance_ad_scan/e_ad_conv.h"
#include "uart/e_uart_char.h"
#include "camera/fast_2_timer/e_poxxxx.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "./findRed.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

char hbuffer[160];
int hnumbuffer[80];
char debugBuffer[80];
long isHandVisable;


//custom cam picture load
void hgetImage(){
	e_poxxxx_launch_capture((char *)hbuffer);
    while(!e_poxxxx_is_img_ready()){};
}

double RGB2Hue(int r, int g, int b){
	double red = ((double)r)/255, green = ((double)g)/255, blue = ((double)b)/255,
		maxv = MAX(MAX(red, green), blue),
		minv = MIN(MIN(red, green), blue),
		h = 0, d = maxv-minv;
	if(d!=0){
		if(maxv == red){
			h = 60.0*((green - blue)/d + (g < b ? 6 : 0));
		} else if(maxv == green){
			h = 60.0*((blue - red)/d + 2);
		} else{
			h = 60.0*((red - green)/d + 4);
		}
	}
	return h;
}
// Image processing removes useless information
void hImage(){	
	long i;
	int green, red, blue, vis;
	for(i=0; i<80; i++){
		//RGB turned into an integer value for comparison
		red = (hbuffer[2*i] & 0xF8);
		green = (((hbuffer[2*i] & 0x07) << 5) | ((hbuffer[2*i+1] & 0xE0) >> 3));
		blue = ((hbuffer[2*i+1] & 0x1F) << 3);
		// convert to RGB to Hue
		double hue = RGB2Hue(red, green, blue);
		if(hue> 6 && hue<38){
			hnumbuffer[i] = 1;
			vis +=1;
		}else{
			hnumbuffer[i] = 0;
		}
		if(vis>0){
			isHandVisable = 1;
		}else{
			isHandVisable = 0;
		}
	}	
}

//Decide which way to turn based on the number of true pixels.
int hturnDirection(){
	int sumL = 0;
	int sumR = 0;
	int i;
	for(i=0;i<40;i++){
		sumL += hnumbuffer[i];
		sumR += hnumbuffer[i+40];
	}
	if(sumL<sumR){ 
		return 1;
	}else{
		return 0;
	}
}
//Function to deal with turning.
void hturn(void) {
	if(hturnDirection()){
		e_set_speed_left (500);
		e_set_speed_right(-500);
	}else{
		e_set_speed_left (-500);
		e_set_speed_right(500);
	}
}
void hforward(void){
	e_set_speed_left (500);
	e_set_speed_right(500);
}
//Main function of follower
void followHand(void){
	int value0, value1, value2, value3,
		value4, value5, value6, value7;
	long i;
	//basic set up for the camera and 
	e_init_ad_scan(ALL_ADC);
	e_calibrate_ir();
	e_poxxxx_init_cam();
	e_poxxxx_config_cam(0,(ARRAY_HEIGHT - 4)/2,640,4,8,4,RGB_565_MODE);
	e_poxxxx_set_mirror(1,1);
	e_poxxxx_write_cam_registers(); 
	
	e_start_agendas_processing();
	int centreValue;

	while(1){
		value0 = e_get_calibrated_prox(0);
		value1 = e_get_calibrated_prox(1);
		value2 = e_get_calibrated_prox(2);
		value3 = e_get_calibrated_prox(3);	
		value4 = e_get_calibrated_prox(4);	
		value5 = e_get_calibrated_prox(5);
		value6 = e_get_calibrated_prox(6);
		value7 = e_get_calibrated_prox(7);
		if(value0>100 || value7>100){
			hgetImage();
			hImage();
			//Take a section of the center, this means if there is an error with one it won't effect it as a whole.
			centreValue = 0;
			for(i=20; i<60; i++){
				centreValue +=hnumbuffer[i];
			}
			//centreValue = hnumbuffer[38] + hnumbuffer[39] + hnumbuffer[40] + hnumbuffer[41] + hnumbuffer[42] + hnumbuffer[43]; // removes stray 
			if(centreValue > 15){
				e_destroy_agenda(hturn);
				if(value1>value6+50){
					e_set_speed_left (800);
					e_set_speed_right(400);
				}
				else if(value6>value1+50){
					e_set_speed_left (400);
					e_set_speed_right(800);
				}
				else{
					hforward();
				}
			}
		}
		else if(value2>100 || value3>100){
			e_destroy_agenda(hturn);
			e_set_speed_left (800);
			e_set_speed_right(-800);
		}
		else if(value5>100 || value6>100){
			e_destroy_agenda(hturn);
			e_set_speed_left (-800);
			e_set_speed_right(800);
		}
		else{
			e_destroy_agenda(hturn);
			e_set_speed_left(0);
			e_set_speed_right(0);
		}
	}
}

