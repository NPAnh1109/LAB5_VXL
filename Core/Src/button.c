/*
 * button.c
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#include "button.h"

static int KeyReg0[NUM_OF_BUTTONS];
static int KeyReg1[NUM_OF_BUTTONS];
static int KeyReg2[NUM_OF_BUTTONS];
static int KeyReg3[NUM_OF_BUTTONS];
static GPIO_TypeDef* BUTTON_PORT[NUM_OF_BUTTONS] = {BT1_GPIO_Port, BT2_GPIO_Port, BT3_GPIO_Port};
static uint16_t BUTTON_PIN[NUM_OF_BUTTONS] = {BT1_Pin, BT2_Pin, BT3_Pin};
static int TimeOutForKeyPress[NUM_OF_BUTTONS];
static int button_flag[NUM_OF_BUTTONS];


void buttonInit(){
	for(int i = 0; i < NUM_OF_BUTTONS; i++){
		KeyReg0[i] = NORMAL_STATE;
		KeyReg1[i] = NORMAL_STATE;
		KeyReg2[i] = NORMAL_STATE;
		KeyReg3[i] = NORMAL_STATE;

		TimeOutForKeyPress[i] =  500;
		button_flag[i] = 0;
	}
}

int isButtonPressed(int index){
	if(index >= NUM_OF_BUTTONS){
		return NORMAL_STATE;
	}
	if(button_flag[index] == 1){
		button_flag[index] = 0;
		return PRESSED_STATE;
	}
	return NORMAL_STATE;
}

void subKeyProcess(int index){
	button_flag[index] = 1;
}

void getKeyInput(){
	for(int i = 0; i < NUM_OF_BUTTONS; i++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
		//Add your button here
		KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);

		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg2[i] != KeyReg3[i]){
			  KeyReg3[i] = KeyReg2[i];

			  if (KeyReg3[i] == PRESSED_STATE){
				TimeOutForKeyPress[i] = 500;
				subKeyProcess(i);
			  }
			}
			else {
			   TimeOutForKeyPress[i] --;
				if (TimeOutForKeyPress[i] == 0){
					TimeOutForKeyPress[i] = 500;
					subKeyProcess(i);
				}
			}
		}
	}
}
