/*
 * scheduler.c
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#include "scheduler.h"

#define MAX_OF_TASKS		40
static uint8_t idx = 0;
char delay[50];
static struct Node* head = NULL;

void SCH_Init(){
	clearList(head);
	head = NULL;
	idx = 0;
};

void SCH_Add_Task(CALLBACK callback, uint16_t Delay, uint16_t Period){
	Task_TypeDef_t data;
	data.callback = callback;
	data.Delay = Delay;
	data.Period = Period;
	data.Runme = 0;
	data.taskID = idx++;
	addTask(&head, data);
};

void SCH_Update(){
	if(head == NULL) return;
	if(head->data.Delay <= 0){
		head->data.Runme = 1;
	}else{
		head->data.Delay--;
	}
};

void SCH_Dispatch_Tasks(){
	if(head == NULL) return;
	if(head->data.Runme == 1){
		(*head->data.callback)();
		Task_TypeDef_t reNewTask;
		reNewTask.Delay = head->data.Period;
		reNewTask.Period = head->data.Period;
		reNewTask.Runme = 0;
		reNewTask.callback = head->data.callback;
		reNewTask.taskID = head->data.taskID;
		deleteTask(&head);
		addTask(&head, reNewTask);
	}

};
