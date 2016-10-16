/***
  Carlie Procell
  Lab 2
  Section F
  ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song {
	char* name;
	int rating;
	int numTimesPlayed;
} Song;

#define MAXNAMESIZE 20

//function prototypes
Song* readAlbum(const char* filename, int* lenPtr);
void printAlbum(Song* album, int len);
int changeRating(char* title, int rating, Song* album, int len);
int listenToSong(char* title, Song* album, int len);

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
	int choice = 3;
	char* title=malloc(sizeof(char)* MAXNAMESIZE);
	while(choice!=0)
	{	
		printf("\nEnter 1 to listen to a song\nEnter 2 to change a rating\nEnter 0 to quit\n");
		scanf("%d", &choice);
		if(choice==1)
		{
			printf("\nEnter a title: ");
			scanf("%s", title);
			int listen;
			listen = listenToSong(title, album, length);
		}
		if(choice==2)
		{
			printf("\nEnter a title: ");
			scanf("%s", title);
			int rating;
			printf("\nEnter a new rating: ");
			scanf("%d", &rating);
			int change;
			change = changeRating(title, rating, album, length);
		}
	}
	if(choice==0)
	{
		int i;
		for(i=0; i<length; i++)
		{
			free(album[i].name);
		}
		free(album);
	}
	return 0;
}

//function to read album
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
	fclose(input);
	return album;
}

//function to print album
void printAlbum(Song* album, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("%s %d %d", album[i].name, album[i].rating, album[i].numTimesPlayed);
		printf("\n");
	}
}

//function to change rating
int changeRating(char* title, int rating, Song* album, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		if(strcmp(album[i].name, title)==0)
		{
			album[i].rating=rating;
			printf("%s %d %d", album[i].name, album[i].rating, album[i].numTimesPlayed);
			return i;
		}
	}
	printf("\nUnable to find song");
	return -1;
}

//function to listen to song
int listenToSong(char* title, Song* album, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		if(strcmp(album[i].name, title)==0)
		{
			album[i].numTimesPlayed++;
			printf("%s %d %d", album[i].name, album[i].rating, album[i].numTimesPlayed);
			return i;
		}
	}
	printf("\nUnable to find song");
	return -1;
}
