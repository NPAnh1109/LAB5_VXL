/*
 * led_display.h
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "global.h"

void resetLED();
void clearAllLED();
void display7SEG(uint8_t num);
void enable7SEG(uint8_t index);
void control7SEG(uint8_t led7state, uint8_t sec_1, uint8_t sec_2);

#endif /* INC_LED_DISPLAY_H_ */
