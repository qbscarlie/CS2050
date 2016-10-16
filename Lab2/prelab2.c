/***
  Carlie Procell
  Prelab 2
  Section F
  ***/

#include <stdio.h>
#include <stdlib.h>

typedef struct song {
	char* name;
	int rating;
	int numTimesPlayed;
} Song;

#define MAXNAMESIZE 20

//function prototypes
Song* readAlbum(const char* filename, int* lenPtr);
void printAlbum(Song* album, int len);

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		printf("Insufficient arguments.\n");
		return 0;
	}
	int length;
	Song* album = readAlbum(argv[1],&length);
	printAlbum(album, length);
   	int i;
	for(i=0; i<length; i++)
	{
		free(album[i].name);
	}
	free(album);
}

Song* readAlbum(const char* filename, int* lenPtr)
{
	FILE* input=fopen(filename, "r");
	if(input==NULL)
	{
		return NULL;
	}
	fscanf(input, "%d", lenPtr);
	Song* album=malloc(sizeof(Song)* *lenPtr);
	int i;
	for(i=0; i<*lenPtr; i++)
	{
		album[i].name = malloc(sizeof(char)* MAXNAMESIZE);
		fscanf(input, "%s %d %d", album[i].name, &album[i].rating, &album[i].numTimesPlayed);
	}
	return album;
}

void printAlbum(Song* album, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("%s %d %d", album[i].name, album[i].rating, album[i].numTimesPlayed);
		printf("\n");
	}
}
