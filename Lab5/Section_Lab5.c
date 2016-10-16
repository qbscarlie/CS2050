/***
Carlie Procell
Section F
Lab 5
 ***/
#include <stdio.h>
#include <stdlib.h>

//Types of coins
typedef enum {
	PENNY	= 1,
	NICKEL	= 5,
	DIME	= 10,
	QUARTER	= 25,
} Denomination;

//How many coins they got
typedef struct
{
	Denomination denomination;
	int quantity;
} Coin;

typedef Coin *PiggyBank;

//function prototypes
PiggyBank loadBank(const char*, int*);
int totalMoney(PiggyBank, int);
char* enumToString(Denomination denomination);
void printBankToScreen(PiggyBank bank, int length);
void sortByQuantity(PiggyBank bank, int length);
void writeToFile(const char* filename, PiggyBank bank, int length);

int main (int argc, char **argv)
{
	printf("\n");
	if (argc != 3) {
		printf("Invalid input. Must be three arguments.\n\n");
		return 0;
	}
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL)
   	{
		printf("Error opening file.\n\n");
		return 0;
	}
	int length;
	int *lenPtr = &length;
	fscanf(fp, "%d", &length);
	PiggyBank bank = malloc(sizeof(Coin)*length);
	bank = loadBank(argv[1], lenPtr);
	printf("You have %d cents.\n\n", totalMoney(bank, length));
	printBankToScreen(bank,length);
	writeToFile(argv[2], bank, length);
	free(bank);
	fclose(fp);
	return 1;
}

PiggyBank loadBank(const char *filename, int *lenPtr)
{
	int temp, i;
	PiggyBank bank = malloc(sizeof(Coin)* *lenPtr);
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
   	{
		printf("Error opening file.\n\n");
		return NULL;
	}
	fscanf(fp, "%d", &temp);
	for (i = 0; i < *lenPtr; i++)
   	{
		fscanf(fp, "%u %d", &bank[i].denomination, &bank[i].quantity);
	}
	fclose(fp);
	return bank;
}

int totalMoney(PiggyBank bank, int length)
{
	int i, sum = 0;
	for (i = 0; i < length; i++)
   	{
		sum += bank[i].denomination * bank[i].quantity;
	}
	return sum;
}

char* enumToString(Denomination denomination)
{
	char* coinType;
	switch(denomination)
	{
		case 1:
			coinType="penny";
			return coinType;
			break;
		case 5:
			coinType="nickel";
			return coinType;
			break;
		case 10:
			coinType="dime";
			return coinType;
			break;
		case 25:
			coinType="quarter";
			return coinType;
			break;
		default:
			return 0;
	}
} 

void printBankToScreen(PiggyBank bank, int length)
{
	int i;
	sortByQuantity(bank, length);
	for(i=0; i<length; i++)
	{
		printf("%s %d\n", enumToString(bank[i].denomination), bank[i].quantity); 
	}
}

void sortByQuantity(PiggyBank bank, int length)
{
	int i, j;
	Coin temp;
	for(i=0; i<length; i++)
	{
		temp = bank[i];
		j=i-1;
			while((temp.quantity<bank[j].quantity)&&(j>=0))
			{
				bank[j+1]= bank[j];
				j=j-1;
			}
			bank[j+1]=temp;
	}
}

void writeToFile(const char* filename, PiggyBank bank, int length)
{
	FILE* fp=fopen(filename, "w");
	fprintf(fp, "%d\n", length);
	int i;
	sortByQuantity( bank, length);
	for(i=0; i<length; i++)
	{
		fprintf(fp, "%d %d\n", bank[i].denomination, bank[i].quantity);
	}
	fclose(fp);
}
