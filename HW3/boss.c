/**
  Carlie Procell
  LCPN87
  Section F
  HW3
  **/

#include "game.h"

//Knock yourself out boys and girls. 

/**This will be the controller for all the boss
  loading. The boss will have all the basic stats
  as if it's a hero, but it will have a decision
  tree for its AI. This tree will have nodes that
  have a health floor and health ceiling. Having
  the boss's current health lie in between those
  two values will determine if that node will be 
  selected. Once the appropriate node is found, 
  a pointer inside the node will lead to a linked
  list of decisions that the boss will take in 
  order. **/

Boss* loadBoss()
{
	FILE* fp=fopen("Boss.txt", "r");
	if(fp==NULL)
	{
		printf("\ncan't open file");
		fclose(fp);
		return NULL;
	}
	Boss* boss = malloc(sizeof(Boss));
	//DecisionTreeNode* root = malloc(sizeof(DecisionTreeNode));
	fscanf(fp, "%s | %d | %d | %d | %d\n", boss->name, &boss->health, &boss->baseDefense, &boss->baseAttack, &boss->baseSpeed);
	fclose(fp);
	return boss;
}

/**This function is for the linked list that is 
  connected to its corresponding tree node.
  Starting from the head of the list, it will
  tack on the new node at the end of the list
  each time it is called.**/

ActionNode* addActionToList(ActionNode* front, ActionNode* newAction)
{
	if(newAction==NULL || front ==NULL)
	{
		printf("\nnode is nullz\n");
		exit(0);
	}
	newAction->next=NULL;
	if(front->next==NULL)
	{
		front->next=newAction;
	}
	else
	{
		while(front->next != NULL)
		{
			front=front->next;
		}
		front->next=newAction;
	}
	return front;
}

/**This function is for dealing with each of the 
  nodes once the linked list is built for it and
  attached. Add the node to the tree as the same
  way you have built BSTs before. Keep in mind
  that each node covers a range of values: if the
  node's range is lower than the range of the root,
  put it on the left side of the tree. If the range
  is above the range of the root, put it on the right.
  **/

DecisionTreeNode* addNodeToTree(DecisionTreeNode* root, DecisionTreeNode* newNode)
{
	if(newNode==NULL)
	{
		printf("\nnew node is null");
		exit(0);
	}
	if(root==NULL)
	{
		root=malloc(sizeof(DecisionTreeNode));
		root->left=newNode;
	}
	else if((newNode->healthCeiling - newNode->healthFloor)<(root->healthCeiling - root->healthFloor))
		root->left = newNode;
	else if((newNode->healthCeiling - newNode->healthFloor)>(root->healthCeiling - root->healthFloor))
		root->right = newNode;
	return root;
}

/**As described, search for the node in the BST that
  has the health range that contains the boss's current
  health. Once found, return the head of the linked list
  found inside the node.**/

ActionNode* fetchNewList(Boss* boss, DecisionTreeNode* root)
{
	if(root==NULL)
	{
		printf("\nnode is null");
		exit(0);
	}
	if(boss->health <= root->healthCeiling && boss->health >= root->healthFloor)
		return root->FirstAction;
	fetchNewList(boss, root->left);
	fetchNewList(boss, root->right);
	return NULL;
}

/**Free the entire tree. Remember: freeing the nodes
  isn't good enough. Each node leads to a linked list,
  so you have to free that first! **/

void freeBossTree(DecisionTreeNode* root)
{
	if(root==NULL)
	{
		exit(0);
	}
	freeBossTree(root->left);
	freeBossTree(root->right);
	free(root);
	exit(0);
}

/**Call this function in freeBossTree(). This will
  be used in conjunction to free the linked list
  connected to the node before freeing the node
  itself.**/

void freeActionListInNode(ActionNode* head)
{
	if(head==NULL)
	{
		exit(0);
	}
	freeActionListInNode(head->next);
	free(head);
	exit(0);
}
