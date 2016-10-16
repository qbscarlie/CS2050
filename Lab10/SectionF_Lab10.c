/***
  Carlie Procell
  LCPN87
  Section F
  Lab10

  plz have mercy this lab was hard :(
  ***/

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<ctype.h>

#define PLEN 13
#define DLEN 9
#define ELEN 30

//function prototypes
int isPhoneNumber(char *token);
int isDate(char* token);
int isEmail(char* token);

int main(int argc, char* argv[])
{
	/**
    //valid #
    assert(isPhoneNumber("(123)456-7890") == 1);
    //not valid #
    assert(isPhoneNumber("123-456-7890") == 0);
    assert(isPhoneNumber("1234567890") == 0);
    assert(isPhoneNumber("(123) 456-7890") == 0);
    assert(isPhoneNumber("Hello World") == 0);
    assert(isPhoneNumber("")        == 0);
	**/
	FILE* fp = fopen(argv[1], "r");
	if(argv[1]==NULL)
	{
		printf("\nerror opening file");
		return 0;
	}
	//int isPhone = isPhoneNumber(argv[1]);
	//if(isPhone == 1)
	//{
		char phone[PLEN];
		fgets(phone, PLEN, fp);
		printf("\nPhone Number: %s", phone);
	//}

	fclose(fp);
    return 0;
}

int isPhoneNumber(char *token)
{
    int i;

    char format[PLEN];
    memset(format, 0, sizeof(char)*PLEN);
    format[0] = '(';
    format[4] = ')';
    format[8] = '-';

    if(strlen(token) != PLEN)
	return 0;

    for(i = 0; i< strlen(token); i++)
    {
/*	if( i == 0)
	{
	    if( token[i] != '(')
		return 0;
	}

	else if( i == 4)
	{
	    if(token[i] != ')')
		return 0;
	}

	else if( i == 8)
	{
	    if(token[i] != '-')
		return 0;
	}
*/
	if( i == 0 || i == 4 || i == 8) {
	    if( token[i] != format[i])
		return 0;
	}
	else
	{  
	    if( isdigit(token[i]) == 0)
		    return 0;
	}

    }	
    return 1;
}

int isDate(char* token)
{
	int x, month, length;
	length=strlen(token);
	if(length!=10)
		return 0;
	for(x=0;x<10;x++)
	{
		switch(x)
		{
			case 0:
			case 1:
				if(isdigit(token[x])==0)
						return 0;
				if(token[0] != 0)
					month=token[0] + 10 + token[1];
				else
					month =token[1];
				if(month<1 || month>12)
					return 0;
				break;
			case 2:
				if(token[x] != '/')
					break;
			case 3:
			case 4:
				/**if(isdigit(token[x]==0))
						return 0;
				if(token[3]!=0)
					day = token[3] + 10 + token[4];
				else
					day = token[4];
				answer = checkday(month,day);
				if(answer==0)
					return 0;
				break;**/
			case 5:
				if(token[x] != '/')
					return 0;
			case 6:
			case 7:
			case 8:
			case 9:
				if(isdigit(token[x])==0)
					return 0;
				break;

		}
	}
	return 1;
}

int isEmail(char* token)
{
	int i;
	char format[ELEN];
	memset(format, 0, sizeof(char)*ELEN);
	for(i=0; i<strlen(token); i++)
	{
		if(format[i] == '@')
		//	if(format[i] == '.com')
				return 1;
	}
	return 0;
}
