/*
 * fsm.c
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#include "fsm.h"

static int time_1 = 0;
static int time_2 = 0;
static int preCnt = 0;

void fsmRun(void){
	switch (mode){
	case INIT:
		resetLED();
		mode = MODE_1;
		trafficstate = GREEN_1;
		time_1 = green_counter;
		time_2 = red_counter;
		break;
	case MODE_1:
		autoMode();
		if(isButtonPressed(0) == PRESSED_STATE){
			resetLED();
			mode = MODE_2;
			preCnt = red_counter;
		}
		break;
	case MODE_2:
		configTime(mode);
		if(isButtonPressed(0) == PRESSED_STATE){
			resetLED();
			mode = MODE_3;
			preCnt = red_counter-green_counter;
		}
		break;
	case MODE_3:
		configTime(mode);
		if(isButtonPressed(0) == PRESSED_STATE){
			resetLED();
			mode = MODE_4;
			preCnt = green_counter;
		}
		break;
	case MODE_4:
		configTime(mode);
		if(isButtonPressed(0) == PRESSED_STATE){
			resetLED();
			mode = INIT;
		}
		break;
	}
}


void autoMode(void){
	switch (trafficstate){
		case GREEN_1:
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, SET);
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, RESET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, RESET);
			if(time_1 <= 0){
				trafficstate = YELLOW_1;
				time_1 = red_counter-green_counter;
			}
			break;
		case YELLOW_1:
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, SET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, RESET);
			if(time_1 <= 0 || time_2 <= 0){
				trafficstate = GREEN_2;
				time_1 = red_counter;
				time_2 = green_counter;
			}
			break;
		case GREEN_2:
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, SET);
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED2_Pin, SET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, RESET);
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, RESET);
			if(time_1 <= 0 || time_2 <= 0){
				trafficstate = YELLOW_2;
				time_2 = red_counter-green_counter;
			}
			break;
		case YELLOW_2:
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, SET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, RESET);
			if(time_1 <= 0 || time_2 <= 0){
				trafficstate = GREEN_1;
				time_1 = green_counter;
				time_2 = red_counter;
			}
			break;
	}

	control7SEG(led7state, time_1, time_2);
	led7state++;
	if(led7state > 3){
		led7state = 0;
		time_1--;
		time_2--;
	}
}


void configTime(int color){
	switch(color){
	case MODE_2:
		HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
		HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);
		led7state++;
		if(led7state > 3){
			led7state = 0;
		}
		control7SEG(led7state, color, preCnt);
		if(isButtonPressed(1) == PRESSED_STATE){
			preCnt++;
			if(preCnt >= 100) preCnt = 0;
		}
		if(isButtonPressed(2) == PRESSED_STATE){
			red_counter = preCnt;
		}
		break;
	case MODE_3:
		HAL_GPIO_TogglePin(YLW1_GPIO_Port, YLW1_Pin);
		HAL_GPIO_TogglePin(YLW2_GPIO_Port, YLW2_Pin);
		led7state++;
		if(led7state > 3){
			led7state = 0;
		}
		control7SEG(led7state, color, preCnt);
		if(isButtonPressed(1) == PRESSED_STATE){
			preCnt++;
			if(preCnt >= 100) preCnt = 0;
		}
		if(isButtonPressed(2) == PRESSED_STATE){
			red_counter = preCnt + green_counter;
		}
		break;
	case MODE_4:
		HAL_GPIO_TogglePin(GRN1_GPIO_Port, GRN1_Pin);
		HAL_GPIO_TogglePin(GRN2_GPIO_Port, GRN2_Pin);
		led7state++;
		if(led7state > 3){
			led7state = 0;
		}
		control7SEG(led7state, color, preCnt);
		if(isButtonPressed(1) == PRESSED_STATE){
			preCnt++;
			if(preCnt >= 100) preCnt = 0;
		}
		if(isButtonPressed(2) == PRESSED_STATE){
			green_counter = preCnt;
		}
		break;
	default:
		break;
	}
}
