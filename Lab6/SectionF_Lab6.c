/**
  Carlie Procell
  Section F
  Lab 6
  **/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define assert_with_msg(expression, msg) { \
	if (!(expression)) { \
		printf("\x1b[31m%s", msg);\
		assert(expression);\
	}\
}

typedef struct node_ {
	int data;
	struct node_* next;
} Node;

//function parameters
Node* build_list(const char* filename);
void print_list(Node* head);
void multiply_by(Node* head, int val);
void free_list(Node* head);
Node* reverse_list(Node* head);

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("\n u need an input file fam\n");
		return 0;
	}
	const char* filename = argv[1];
	FILE* fp = fopen(filename, "r");
	if(fp==NULL)
	{
		printf("\n error opening file :| \n");
		return 0;
	}
	fclose(fp);
	Node* head = build_list(filename);
	print_list(head);
	int value;
	printf("\nEnter a value to multiply by please: ");
	scanf("%d", &value);
	multiply_by(head, value);
	//print_list(head);
	reverse_list(head);
	//print_list(reverse);
	free_list(head);	
	return 0;
}

Node* build_list(const char* filename)
{
	FILE* fp;
	fp = fopen(filename,"r");
	Node* firstNode;
	Node* nextNode;
	Node* newNode;
	firstNode = malloc(sizeof(Node));
	firstNode->next = NULL;
	
	nextNode = firstNode;
	
	while (1)
	{
		fscanf(fp, "%d", &nextNode->data);	
		//printf("%d\n", nextNode->data);
		if(nextNode->data == 6)	
		{										
			break;
		}
		newNode = malloc(sizeof(Node));		
		newNode->next = nextNode;				
		nextNode = newNode;					
	}
	
	fclose(fp);
	
	return nextNode;
}

void print_list(Node* head)
{
	Node* node = NULL;
	node = head;
	while(node !=NULL)
	{
		printf("%d->", node->data);
		node = node->next;
	}
	printf("NULL");
}

void multiply_by(Node* head, int val)
{
	Node* node = NULL;
	node = head;
	while(node !=NULL)
	{
		printf("%d->", node->data * val);
		node = node->next;
	}
	printf("NULL\n");
}

void free_list(Node* head)
{
	Node* node;
	while(head != NULL)
	{
		node = head;
		head = head->next;
		free(node);
		printf("\n");
		//print_list(head);
	}
}

Node* reverse_list(Node* head)
{
	Node *p, *q, *r;
	p=q=r=head;
	p=p->next->next;
	q=q->next;
	r->next = NULL;
	q->next=r;
	while(p != NULL)
	{
		r=q;
		q=p;
		p=p->next;
		q->next=r;
	}
	head = q;
	print_list(head);
	return head;
}
