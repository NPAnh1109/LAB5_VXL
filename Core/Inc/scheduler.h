/*
 * scheduler.h
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "global.h"

typedef void (*CALLBACK)(void);

void SCH_Init();
void SCH_Add_Task(CALLBACK callback, uint16_t Delay, uint16_t Period);
void SCH_Update();
void SCH_Dispatch_Tasks();

#endif /* INC_SCHEDULER_H_ */d
