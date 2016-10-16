/***
Carlie Procell
LCPN87
Section F
Lab 9 
***/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct node_ {
	int data;
	struct node_* left;
	struct node_* right;
} Node;

//function prototypes
Node* buildBalancedTree(int array[], int low, int high);
Node* new(int data);
void printTree(Node* root, int depth);
void padding(int depth);
void quicksort(int a[], int low, int high);
void preorder(Node* root);
void inorder(Node* root);
void postorder(Node* root);
void freeTree(Node*root);
int height(Node*root);
void printEveryPath(Node* root, int* path, int depth);


int main(int argc, char* argv[]) {
	int i,array[10];
	srand(time(NULL));
	for(i=0; i<11; i++)
	{
		array[i]=rand() % 100;
	}
	//int array[] = {1, 2, 3, 4, 5, 6, 7};
	quicksort(array, 0, 10);
	Node* root = buildBalancedTree(array, 0, 9);
	printf("\nHeight of the tree is %d\n", height(root));
	//printTree(root, height(root));
	printf("\npreorder \n");
	preorder(root);
	//printTree(root, height(root));
	printf("\ninorder \n");
	inorder(root);
	//printTree(root, height(root));
	printf("\npostorder \n");
	postorder(root);
	//printTree(root, height(root));
	printf("\nBonus\n");
	//int* path = array;
	printEveryPath(root, array, 0);
	freeTree(root);
	return 0;
}

Node* buildBalancedTree(int array[], int low, int high)
{
	if(low>high)
		return NULL;
	int mid = (low+high)/2;
	Node* root = new(array[mid]);
	root->left = buildBalancedTree(array, low, mid-1);
	root->right = buildBalancedTree(array, mid+1, high);

	return root;
}

Node* new(int data)
{
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void printTree(Node* root, int depth) {
	if (root == NULL) {
		padding(depth);
		printf("~\n");
	} else {
		printTree(root->right, depth + 1);
		padding(depth);
		printf("%d ", root->data);
		printTree(root->left, depth + 1);
	}
}

void padding(int depth) {
	int i;
	for (i = 0; i < depth; i++) {
		putchar('\t');
	}
}

void quicksort(int a[], int low, int high)
{
	int pivot, j, temp, i;
	if(low < high)
	{
		pivot = low;
		i=low;
		j=high;
		while(i<j)
		{
			while(a[i] <= a[pivot]&&high)
				i++;
			while(a[j]>a[pivot])
				j--;
			if(i<j)
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
		temp=a[pivot];
		a[pivot]=a[j];
		a[j]=temp;
		quicksort(a, low, j-1);
		quicksort(a, j+1, high);
	}
}

void preorder(Node* root)
{
	if(root != NULL)
	{
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(Node* root)
{
	if(root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void postorder(Node* root)
{
	if(root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

void freeTree(Node* root)
{
	if(root==NULL)
		exit(0);
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

int height(Node* root)
{
	if(root==NULL)
		return 0;
	else
	{
		int lheight = height(root->left);
		int rheight = height(root->right);
		if(lheight > rheight)
			return(lheight+1);
		else
			return(rheight+1);
	}
}

void printEveryPath(Node* root, int* path, int depth)
{
	if(root==NULL)
		return;
	path[depth++]=root->data;
	if((root->left == NULL) && (root->right == NULL))
	{
		int i = 0;
		for(i=0; i<depth; i++)
		{
			printf("%d ", path[i]);
		}
		printf("\n");
		return;
	}
	printEveryPath(root->left, path, depth);
	printEveryPath(root->right, path, depth);
}
