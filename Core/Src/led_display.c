/*
 * led_display.c
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#include "led_display.h"

uint8_t LED[10] = {0x3F,		//decode for 0
				0x06, 			//decode for 1
				0x5B, 			//decode for 2
				0x4F, 			//decode for 3
				0x66, 			//decode for 4
				0x6D, 			//decode for 5
				0x7D, 			//decode for 6
				0x07, 			//decode for 7
				0x7F, 			//decode for 8
				0x6F};			//decode for 9

void display7SEG(uint8_t num){
	HAL_GPIO_WritePin(GPIOB, A_Pin, !((LED[num]>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB, B_Pin, !((LED[num]>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB, C_Pin, !((LED[num]>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB, D_Pin, !((LED[num]>>3)&0x01));
	HAL_GPIO_WritePin(GPIOB, E_Pin, !((LED[num]>>4)&0x01));
	HAL_GPIO_WritePin(GPIOB, F_Pin, !((LED[num]>>5)&0x01));
	HAL_GPIO_WritePin(GPIOB, G_Pin, !((LED[num]>>6)&0x01));
}

void resetLED(){
	HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, SET);
	HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, SET);
	HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, SET);
	HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, SET);
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
}

void clearAllLED(){
	HAL_GPIO_WritePin(GPIOB, EN0_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, EN1_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, EN2_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, EN3_Pin, SET);
}

void control7SEG(uint8_t led7state, uint8_t cnt1, uint8_t cnt2){
	clearAllLED();
	switch(led7state){
	case 0:
		display7SEG(cnt1/10);
		HAL_GPIO_WritePin(GPIOB, EN0_Pin, RESET);
		break;
	case 1:
		display7SEG(cnt1%10);
		HAL_GPIO_WritePin(GPIOB, EN1_Pin, RESET);
		break;
	case 2:
		display7SEG(cnt2/10);
		HAL_GPIO_WritePin(GPIOB, EN2_Pin, RESET);
		break;
	case 3:
		display7SEG(cnt2%10);
		HAL_GPIO_WritePin(GPIOB, EN3_Pin, RESET);
		break;
	}
};


