/*
 * global.h
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "button.h"
#include "fsm.h"
#include "led_display.h"
#include "SLL.h"
#include "scheduler.h"

#define TUNNING_RED 2
#define TUNNING_YLW 3
#define TUNNING_GRN 4

typedef enum {
	GREEN_1,
	YELLOW_1,
	GREEN_2,
	YELLOW_2
} TrafficState;

extern TrafficState trafficstate;

#define INIT 	0
#define MODE_1	1
#define MODE_2	2
#define MODE_3	3
#define MODE_4	4

extern uint8_t led7state;
extern uint8_t red_counter;
extern uint8_t green_counter;
extern int mode;

#endif /* INC_GLOBAL_H_ */
