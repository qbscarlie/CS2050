/***
Carlie Procell
Section F
HW2
LCPN87
***/

#include "game.h"

//function to load the shop
Shop* loadShop()
{
    Shop* shop=malloc(sizeof(Shop));
    FILE* fp=fopen("Items.txt", "r");
    if(fp==NULL)
    {
        printf("\nCan't open shop\n");
        return 0;
    }
    Shield* newShield;
    Shield* shieldPtr;
    newShield = shieldPtr = NULL;
    Sword* newSword;
    Sword* swordPtr;
    newSword = swordPtr = NULL;
    
    newShield=malloc(sizeof(Shield));
    fscanf(fp, "%s | %d | %d", newShield->name, &newShield->cost, &newShield->defense);
    newShield->prevShield = newShield->nextShield = NULL;
    shieldPtr = newShield;
    int i;
    while(shieldPtr==NULL)
    {
        printf("\nerror reading shields\n");
        return 0;
    }
    for(i=1;i<NUMSHIELDS;i++)//iterates thru to load shields
    {
        shieldPtr->nextShield=malloc(sizeof(Shield));
        fscanf(fp, "%s | %d | %d", shieldPtr->nextShield->name, &shieldPtr->nextShield->cost, &shieldPtr->nextShield->defense);
        shieldPtr->nextShield->prevShield=shieldPtr;
        shieldPtr->nextShield->nextShield=NULL;
        shieldPtr=shieldPtr->nextShield;
    }
    
    newSword=malloc(sizeof(Sword));
    fscanf(fp, "%s | %d | %d", newSword->name, &newSword->cost, &newSword->attack);
    newSword->prevSword = newSword->nextSword = NULL;
    swordPtr = newSword;
    while(swordPtr==NULL)
    {
        printf("\nerror reading swords\n");
        return 0;
    }
    for(i=1;i<NUMSWORDS;i++)//iterates thru to load swords
    {
        swordPtr->nextSword=malloc(sizeof(Sword));
        fscanf(fp, "%s | %d | %d", swordPtr->nextSword->name, &swordPtr->nextSword->cost, &swordPtr->nextSword->attack);
        swordPtr->nextSword->prevSword=swordPtr;
        swordPtr->nextSword->nextSword=NULL;
        swordPtr=swordPtr->nextSword;
    }
    shop->headSword=newSword;
    shop->headShield=newShield;
    fclose(fp);
    return shop;
}

void destroyShop(Shop* shop)
{
    Shield* shieldPtr1=NULL;
    shieldPtr1=shop->headShield;
    while(shieldPtr1 != NULL)//frees shields
    {
        Shield* shieldPtr2=malloc(sizeof(Shield));
        shieldPtr2=shieldPtr1;
        shieldPtr1=shieldPtr1->nextShield;
        free(shieldPtr2);
    }
    Sword* swordPtr1=NULL;
    swordPtr1=shop->headSword;
    while(swordPtr1 != NULL)//frees swords
    {
        Sword* swordPtr2=malloc(sizeof(Sword));
        swordPtr2=swordPtr1;
        swordPtr1=swordPtr1->nextSword;
        free(swordPtr2);
    }
    free(shop);//frees the whole shop
}


void sortShields(Shield** shields)
{
    int n;
    Shield*cur; 
    cur=*shields;
    if(cur->nextShield != NULL)
    {
        cur=cur->nextShield;
        Shield* ptr;
        Shield* tmp;
        while(cur != NULL)
        {
            n=0;//initializes to 0 at beginning to sort
            ptr=cur;
            tmp=cur->prevShield;
            while(tmp != NULL && tmp->cost > ptr->cost)
            {
                n++;//increments
                tmp=tmp->prevShield;
            }
            if(n>0)
            {
                ptr->prevShield->nextShield=ptr->nextShield;
                if(ptr->nextShield != NULL)
                {
                    ptr->nextShield->prevShield=ptr->prevShield;
                }
                if(tmp == NULL)//sorts using next and prev pointers
                {
                    tmp = *shields;
                    ptr->prevShield=NULL;
                    ptr->nextShield=tmp;
                    ptr->nextShield->prevShield=ptr;
                    *shields=ptr;
                }
                else
                { 
                    tmp=tmp->nextShield;
                    tmp->prevShield->nextShield=ptr;
                    ptr->prevShield=tmp->prevShield;
                    tmp->prevShield=ptr;
                    ptr->nextShield=tmp;
                }
            }
            cur=cur->nextShield;
        }
    }
}

void sortSwords(Sword** swords)
{
    int n;
    Sword*cur; 
    cur=*swords;
    if(cur->nextSword != NULL)
    {
        cur=cur->nextSword;
        Sword* ptr;
        Sword* tmp;
        while(cur != NULL)
        {
            n=0;//initialize to 0 at beginning of every iteration
            ptr=cur;
            tmp=cur->prevSword;
            while(tmp != NULL && tmp->cost > ptr->cost)
            {
                n++;//increments
                tmp=tmp->prevSword;
            }
            if(n>0)
            {
                ptr->prevSword->nextSword=ptr->nextSword;
                if(ptr->nextSword != NULL)
                {
                    ptr->nextSword->prevSword=ptr->prevSword;
                }
                if(tmp == NULL)//sorts using next and prev pointers
                {
                    tmp = *swords;
                    ptr->prevSword=NULL;
                    ptr->nextSword=tmp;
                    ptr->nextSword->prevSword=ptr;
                    *swords=ptr;
                }
                else
                { 
                    tmp=tmp->nextSword;
                    tmp->prevSword->nextSword=ptr;
                    ptr->prevSword=tmp->prevSword;
                    tmp->prevSword=ptr;
                    ptr->nextSword=tmp;
                }
            }
            cur=cur->nextSword;
        }
    }
}

void printShields(Shield* shields)//prints out list of shields
{
    Shield* shieldPtr=NULL;
    shieldPtr=shields;
    int i=1;
    while(shieldPtr==NULL)//check for null
    {
        printf("\nerror printing shields\n");
    }
    while(shieldPtr!=NULL)
    {
        printf("%d - %s\n    Cost: %d\n    Defense: %d\n",i++, shieldPtr->name, shieldPtr->cost, shieldPtr->defense);
        shieldPtr=shieldPtr->nextShield;
    }
    printf("\nsorted using both directional pointers\n");
}

void printSwords(Sword* swords)//prints out list of swords
{
    Sword* swordPtr=NULL;
    swordPtr=swords;
    int i=1;
    while(swordPtr==NULL)//check for null
    {
        printf("\nerror printing swords\n");
    }
    while(swordPtr!=NULL)
    {
        printf("%d - %s\n    Cost: %d\n    Defense: %d\n",i++, swordPtr->name, swordPtr->cost, swordPtr->attack);
        swordPtr=swordPtr->nextSword;
    }
    printf("\nsorted using both directional pointers\n");
}

Shield* removeShieldFromList(Shield** shields, int choice)
{
    int i;
    Shield* ptr1;
    Shield* ptr2;
    ptr2=*shields;
    ptr1=ptr2;
    if(choice == 1) 
    {
	   ptr2=ptr2->nextShield;
	   ptr2->prevShield=NULL;
    }
    else//removes shields from list
    {
	   for(i=1;i<choice;i++)
	   {
           ptr1=ptr1->nextShield;
	   }
        if(ptr1->nextShield != NULL)
        {
            ptr1->nextShield->prevShield=ptr1->prevShield;
        }
        ptr1->prevShield->nextShield=ptr1->nextShield;
    }
    *shields=ptr2;
    return ptr1;
}

Sword* removeSwordFromList(Sword** swords, int choice)
{
    int i;
    Sword* ptr1;
    Sword* ptr2;
    ptr2=*swords;
    ptr1=ptr2;
    if(choice == 1) 
    {
	   ptr2=ptr2->nextSword;
	   ptr2->prevSword=NULL;
    }
    else//removes swords from list
    {
	   for(i=1;i<choice;i++)
	   {
           ptr1=ptr1->nextSword;
	   }
        if(ptr1->nextSword != NULL)
        {
            ptr1->nextSword->prevSword=ptr1->prevSword;
        }
        ptr1->prevSword->nextSword=ptr1->nextSword;
    }
    *swords=ptr2;
    return ptr1;
}

/***************************START OF FUNCTIONS GIVEN TO YOU**********************************/

void freeHeroesAndItems(Hero* heroes)
{
	int i;
	for(i = 0; i < NUMCHOSENHEROES; i++)
	{
		if(heroes[i].heroSword != NULL)
		{
			free(heroes[i].heroSword);
		}
		if(heroes[i].heroShield != NULL)
		{
			free(heroes[i].heroShield);
		}
	}
	free(heroes);
}

void goShopping(Hero* heroes, Shop* shop)
{

	printf("\n\nNow, you will select a sword and shield for your heroes.\n");

	int firstPass = 1; 

	int bank = STARTINGBANKVALUE;

	while(1)
	{
		printf("Which would you like to look at?\n");
		printf("1: Swords\n2: Shields\n3: Continue to fight\n");
		printf("> ");
		int choice; 
		scanf("%d", &choice);
		while(choice < 1 || choice > 3)
		{
			printf("Invalid choice. Select again: \n");
			printf("> ");
			scanf("%d", &choice);
		}

		if(choice == 3)
		{
			if(firstPass == 1)
			{
				printf("Are you sure you don't want to buy anything?\n");
				printf("1: yes\n2: no\n");
				printf("> ");
				scanf("%d", &choice);
				while(choice < 1 || choice > 2)
				{
					printf("Invalid choice. Select again: \n");
					printf("> ");
					scanf("%d", &choice);
				}
			}
			else
			{
				choice = 1;
			}

			if(choice == 1)
			{
				destroyShop(shop);
				return;
			}
		}
		else if(choice == 2)
		{
			printf("Do you want it sorted (1) or unsorted? (2)\n");
			printf(">");
			int sortChoice;
			scanf("%d", &sortChoice);
			while(sortChoice != 1 && sortChoice != 2)
			{
				printf("Invalid choice, choose again: ");
				printf(">");
				scanf("%d", &sortChoice);
			}

			if(sortChoice == 1)
			{
				sortShields(&(shop->headShield));
			}
			

			while(1)
			{
				printShields(shop->headShield);
				
				while(1)
				{
					printf("\nBudget: %d\n", bank);
					printf("Select a shield (-1 to go back): \n");
					printf("> ");
					scanf("%d", &choice);
	
					while((choice < 1 || choice > NUMSHIELDS) && choice != -1)
					{
						printf("Invalid choice. Select again: \n");
						printf("> ");
						scanf("%d", &choice);
					}
				
					if(choice != -1)
					{
						if(findShieldPrice(shop->headShield, choice) > bank)
						{
							printf("You don't have enough money for that!\n");
						}
						else break;
					}
					else break;
				}

				if(choice == -1)
				{
					break;
				}
				else
				{
					int heroChoice; 

					while(1)
					{
						printHeroes(heroes, NUMCHOSENHEROES);
						printf("Which hero do you want to have the item? (-1 to go back): \n");
						printf("> ");
						scanf("%d", &heroChoice);

						while((heroChoice < 1 || heroChoice > NUMCHOSENHEROES) && heroChoice != -1)
						{
							printf("Invalid choice. Select again: \n");
							printf("> ");
							scanf("%d", &heroChoice);
						}

						if(heroChoice == -1)
						{
							break;
						}

						if(heroes[heroChoice - 1].heroShield != NULL)
						{
							printf("That hero already has a shield. Choose again.\n");
						}
						else
						{
							break;
						}

					}
					

					if(heroChoice == -1)
					{
						break;
					}
					else
					{
						Shield* item = removeShieldFromList(&(shop->headShield), choice);
						heroes[heroChoice - 1].heroShield = item;
						bank -= item->cost;
						firstPass = 0;
					}
				}
			}
		}
		else if(choice == 1)
		{
			printf("Do you want it sorted (1) or unsorted? (2)\n");
			printf(">");
			int sortChoice;
			scanf("%d", &sortChoice);
			while(sortChoice != 1 && sortChoice != 2)
			{
				printf("Invalid choice, choose again: ");
				printf(">");
				scanf("%d", &sortChoice);
			}

			if(sortChoice == 1)
			{
				sortSwords(&(shop->headSword));
			}
			
			while(1)
			{
				printSwords(shop->headSword);
				
				while(1)
				{
					printf("\nBudget: %d\n", bank);
					printf("Select a sword (-1 to go back): \n");
					printf("> ");
					scanf("%d", &choice);
	
					while((choice < 1 || choice > NUMSWORDS) && choice != -1)
					{
						printf("Invalid choice. Select again: \n");
						printf("> ");
						scanf("%d", &choice);
					}
				
					if(choice != -1)
					{
						if(findSwordPrice(shop->headSword, choice) > bank)
						{
							printf("You don't have enough money for that!\n");
						}
						else break;
					}
					else break;
				}

				if(choice == -1)
				{
					break;
				}
				else
				{
					int heroChoice; 

					while(1)
					{
						printHeroes(heroes, NUMCHOSENHEROES);
						printf("Which hero do you want to have the item? (-1 to go back): \n");
						printf("> ");
						scanf("%d", &heroChoice);

						while((heroChoice < 1 || heroChoice > NUMCHOSENHEROES) && heroChoice != -1)
						{
							printf("Invalid choice. Select again: \n");
							printf("> ");
							scanf("%d", &heroChoice);
						}

						if(heroChoice == -1)
						{
							break;
						}

						if(heroes[heroChoice - 1].heroSword != NULL)
						{
							printf("That hero already has a sword. Choose again.\n");
						}
						else
						{
							break;
						}
					}
					if(heroChoice == -1)
					{
						break;
					}
					else
					{
						Sword* item = removeSwordFromList(&(shop->headSword), choice);
						heroes[heroChoice - 1].heroSword = item;
						bank -= item->cost;
						firstPass = 0;
					}
				}
			}
		}
	}
}

int findSwordPrice(Sword* swords, int choice)
{
	int i = 1;
	while(i < choice)
	{
		swords = swords->nextSword;
		i++;
	}
	return swords->cost;
}

int findShieldPrice(Shield* shields, int choice)
{
	int i = 1;
	while(i < choice)
	{
		shields = shields->nextShield;
		i++;
	}
	return shields->cost;
}
