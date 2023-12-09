/*
 * SLL.c
 *
 *  Created on: Nov 27, 2023
 *      Author: 84977
 */

#include "SLL.h"

struct Node* createNode(Task_TypeDef_t data){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	if(!newNode){
	}
	newNode->data.callback = data.callback;
	newNode->data.Delay = data.Delay;
	newNode->data.Period = data.Period;
	newNode->data.Runme = data.Runme;
	newNode->data.taskID = data.taskID;
	newNode->nextNode = NULL;
	return newNode;
};

void addTask(struct Node** head, Task_TypeDef_t data){
	struct Node* newNode = createNode(data);
	if(*head == NULL){
		*head = newNode;
		return;
	}
	struct Node* temp = *head;
	if( newNode->data.Delay < temp->data.Delay){
		temp->data.Delay -= newNode->data.Delay;
		newNode->nextNode = temp;
		*head = newNode;
		return;
	}

	newNode->data.Delay -= temp->data.Delay;
	while(temp->nextNode != NULL && newNode->data.Delay >= temp->nextNode->data.Delay){
		temp = temp->nextNode;
		newNode->data.Delay -= temp->data.Delay;
	}
	if(temp->nextNode == NULL){
		temp->nextNode = newNode;
	}else{
		newNode->nextNode = temp->nextNode;
		temp->nextNode = newNode;
	}
};

void deleteTask(struct Node** head){
	if(head == NULL) return;
	struct Node* temp = *head;
	*head = temp->nextNode;
	free(temp);
};

void clearList(struct Node* head){
	if(head == NULL) return;
	clearList(head->nextNode);
	free(head);
	head = NULL;
}

void deleteTaskID(struct Node** head, uint8_t taskID){
	struct Node* temp = *head;
	if(temp == NULL) return;
	if(temp->data.taskID == taskID) deleteTask(head);
	while(temp->nextNode != NULL && temp->nextNode->data.taskID != taskID){
		temp = temp->nextNode;
	}
	if(temp->nextNode == NULL) return;
	struct Node* deleteNode = temp->nextNode;
	temp->nextNode = temp->nextNode;
	free(deleteNode);
}
