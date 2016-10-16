/***
Carlie Procell
Lab 8 
Section F
LCPN87
***/

#include <stdlib.h>
#include <stdio.h>

typedef struct node_ {
	int data;
	struct node_* left;
	struct node_* right;
} Node;


void printTree(Node* root, int depth);
Node* insert(Node* root, int data);
void padding(int depth);
Node* buildTree(char* filename);
int min(Node* root);
Node* delete(Node* root, int data);
void freeTree(Node* root);
Node* flipTree(Node* root);

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("\nu need an inpt file fam\n");
		return 0;
	}
	Node* bst =  buildTree(argv[1]);
	printTree(bst, 0);
	int num;
	printf("\nEnter a number to delete: ");
	scanf("%d", &num);
	printTree(delete(bst,num), 0);
	printf("\n under this be a flipped tree:\n");
	bst = (flipTree(bst));
	printTree(bst, 0);
	freeTree(bst);
	return 0;
}

//function to insert nodes into binary tree
Node* insert(Node* root, int d) {
	if(root==NULL)
	{
		root = malloc(sizeof(Node));
		root->data = d;
		root->left=NULL;
		root->right=NULL;
	}
	else if(d < root->data)
		root->left = insert(root->left,d);
	else if(d > root->data)
		root->right = insert(root->right,d);
	return root;
}

//function to make tree pretty
void padding(int depth) {
	int i;
	for (i = 0; i < depth; i++) {
		putchar('\t');
	}
}

//function to print out tree
void printTree(Node* root, int depth) {
	if (root == NULL) {
		padding(depth);
		printf("~\n");
	} else {
		printTree(root->right, depth + 1);
		padding(depth);
		printf("%d\n", root->data);
		printTree(root->left, depth + 1);
	}
}

//function to build tree
Node* buildTree(char* filename)
{
	FILE* fp = fopen(filename, "r");
	if(fp==NULL)
	{
		printf("\ni cant read ur file :(");
		return 0;
	}
	Node* bst = NULL;
	int num;
	while(fscanf(fp, "%d", &num) != EOF)
	{
		bst = insert(bst, num);
	}
	fclose(fp);
	return bst;
}

//function to find minimum value in tree
int min(Node* root)
{
	Node* current = root;
	while(current->left != NULL)
	{
		current = current->left;
	}
	return(current->data);
}

//function to delete node from tree
Node* delete(Node* root, int data)
{
	if(root==NULL)
		return root;

	if(data < root->data)
		root->left = delete(root->left, data);
	else if(data > root->data)
		root->right = delete(root->right, data);
	else
	{
		if(root->left == NULL)
		{
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			Node* temp = root->left;
			free(root);
			return temp;
		}
		int temp = min(root->right);
		root->data = temp;
		root->right = delete(root->right, temp);
	}
	return root;
}

//function to free tree
void freeTree(Node* root)
{
	if(root==NULL)
		exit(0);
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

//function to inverse tree values
Node* flipTree(Node* root)
{
	if(root==NULL)
	{
		return 0;
	}
	else
	{
		Node* temp;
		temp = root->right;
		root->right = root->left;
		root->left = temp;
		flipTree(root->right);
		flipTree(root->left);
	}
	return root;
}
