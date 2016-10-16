#include "game.h"

//If you haven't knocked yourself out in boss.c, do it here.
//Otherwise, knock yourself out again. 

//From instruction file:
/** These functions are identical except for one line:
  the defense value vs the attack value. The file pointer
  passed into the function is pointing at the next line
  in the file to be read. You will have to get that line 
  and, from that, fill the shield/sword with its info.
  DO NOT USE FSCANF! A suggestion would be to start w/
  fgets(), since you can specify the max number of 
  characters to read from the line. This way, you
  can guarantee to read the entire line that you
  need to parse.  
  **/

void ParseShieldInfo(Shield* s, FILE* fp)
{
	//definitions
	char line[100];
    char name[50];
    char cost[10];
    char defense[10];
    char description[100];
    int i;
    
    //getting the info
	fgets(line, sizeof(line), fp); 
    
    //bar #1
	char *special = strchr(line, '|'); 
	int iName = (int)(special - line); 
	for (i = 0; i < iName; i++) 
    {
		name[i] = *(line+i); 
	}
	name[i] = '\0'; 
	strcpy(s->name, name);

    //bar #2
	special = strchr(&line[iName+1], '|'); 
	int iCost = (int)(special - line);
	for (i = 0; i < iCost-iName; i++) 
    { 
		cost[i] = *(line+iName+1+i);
	}
	cost[i] = '\0';
	s->cost = atoi(cost);

    //bar #3
	special = strchr(&line[iCost+1], '|'); 
	int iDefense = (int)(special - line); 
	for (i = 0; i < iDefense-iCost; i++) 
    {
		defense[i] = *(line+iCost+1+i);
	}
	defense[i] = '\0';
	s->defense = atoi(defense);

    //definition
	for (i = 0; *(line+i) != '\n'; i++) 
    {
		description[i] = *(line+iDefense+2+i);
	}
	description[i] = '\0';
	strcpy(s->description, description);
	return;
}

void ParseSwordInfo(Sword* s, FILE* fp)
{
	//definitions
	char line[100];
    char cost[10];
    char name[50];
    char attack[10];
    char description[100];
    int i;
    
    //getting the info
	fgets(line, sizeof(line), fp); 
    
    //bar #1
	char *special = strchr(line, '|'); 
	int iName = (int)(special - line); 
	for (i = 0; i < iName; i++) 
    {
		name[i] = *(line+i); 
	}
	name[i] = '\0'; 
	strcpy(s->name, name);

    //bar #2
	special = strchr(&line[iName+1], '|'); 
	int iCost = (int)(special - line);
	for (i = 0; i < iCost-iName; i++) 
    { 
		cost[i] = *(line+iName+1+i);
	}
	cost[i] = '\0';
	s->cost = atoi(cost);

    //bar #3
	special = strchr(&line[iCost+1], '|'); 
	int iAttack = (int)(special - line); 
	for (i = 0; i < iAttack-iCost; i++) 
    {
		attack[i] = *(line+iCost+1+i);
	}
	attack[i] = '\0';
	s->attack = atoi(attack);

    //definition
	for (i = 0; *(line+i) != '\n'; i++) 
    {
		description[i] = *(line+iAttack+2+i);
	}
	description[i] = '\0';
	strcpy(s->description, description);
	return;
}
