/***
  Carlie Procell
  LCPN87
  Section F
  Lab 7

  sup aj whats good
  ***/
#include <stdlib.h>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct node_ { 
	int data;
	struct node_* next;
} Node;


Node* enqueue(Node* head, int data);
int dequeue(Node** frontPtr);
void printQueue(Node* front);
void freeQueue(Node* front);

int main(void) {
	Node* queue = NULL;
	int choice, choice2;
	printf("Enter 1 to enqueue\nEnter 2 to Dequeue\nEnter 3 to quit\n");
	scanf("%d", &choice);
	while(choice >0 && choice <4)
	{
		switch(choice)
		{
			case 1:
				printf("\nEnter a number to enqueue: ");
				scanf("%d", &choice2);
				queue  = enqueue(queue, choice2);
				printQueue(queue);
				printf("> ");
				scanf("%d", &choice);
				break;
			case 2:
				printf("\n%d was dequeued", dequeue(&queue));
				printf("\n> ");
				scanf("%d", &choice);
				break;
			case 3:
				freeQueue(queue);
				return 0;
		}
	}
	return 0;
}

//this is da enqueue function
Node* enqueue(Node* head, int data)
{
	Node *newNode, *nodePtr;
	newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	if (!head)
   	{
		return newNode;
	}
	nodePtr = head;
	while (nodePtr->next)
   	{
		nodePtr = nodePtr->next;
	}
	nodePtr->next = newNode;
	return head;
}

//this is da dairy queen function
int dequeue(Node** frontPtr)
{
	Node* curr = *frontPtr;
	*frontPtr = curr -> next;
	int temp = curr -> data;
	free(curr);
	return temp;
}

//this prints da queue
void printQueue(Node* front)
{
	Node* node = NULL;
	node = front;
	while(node != NULL)
	{
		printf("%d->", node->data);
		node = node->next;
	}
	printf("NULL\n");
}

//this be the free queue function
void freeQueue(Node* front)
{
	Node* node;
	while(front != NULL)
	{
		node = front;
		front = front->next;
		free(node);
	}
}
