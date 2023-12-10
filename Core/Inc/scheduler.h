/*
 * scheduler.h
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "global.h"

#define SCH_MAX_TASKS 40

typedef void (*CALLBACK)(void);

void SCH_Init();
uint32_t SCH_Add_Task(CALLBACK callback, uint16_t Delay, uint16_t Period);
void SCH_Update();
void SCH_Dispatch_Tasks();
void SCH_Delete_Task(uint32_t taskID);

#endif /* INC_SCHEDULER_H_ */d
