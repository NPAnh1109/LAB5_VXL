/*
 * button.h
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define NUM_OF_BUTTONS 3
extern int button1_flag[NUM_OF_BUTTONS];


void getKeyInput();
int isButtonPressed(int index);

#endif /* INC_BUTTON_H_ */
