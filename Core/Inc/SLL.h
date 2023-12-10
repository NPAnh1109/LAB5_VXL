/*
 * SLL.h
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#ifndef INC_SLL_H_
#define INC_SLL_H_

#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef void (*CALLBACK)(void);

typedef struct{
	CALLBACK callback;

	uint16_t Delay;

	uint16_t Period;

	uint8_t Runme;

	uint32_t taskID;

}Task_TypeDef_t;

struct Node{
	Task_TypeDef_t data;
	struct Node* nextNode;
};

struct Node* createNode(Task_TypeDef_t data);
void addTask(struct Node** head, Task_TypeDef_t data);
void deleteTask(struct Node** head);
void deleteTaskID(struct Node** head, uint32_t taskID);
void clearList(struct Node* head);


#endif /* INC_SLL_H_ */
