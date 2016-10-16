#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	PaperBack,
	HardBack,
} Type;

typedef struct book {
	char* name;
	char* author;
	int rating;
	Type type;
} Book;

typedef Book* Library;

Library loadLibrary(const char* filename, int* lenPtr);
void sortLibrary(Library library,  int length);
void printLibrary(Library library, int length);
void writeLibrary(Library library, int length, const char* filename);

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Incorrect Usage\n");
		printf("%s <input file> <output file>\n", argv[0]);
		return 0;
	}

	int* length;
	Library library = loadLibrary(argv[1], length);
	//printf("LordOfTheRings Tolkein 3 HardBack\n");
	//printf("11-22-63 StevenKing 4 HardBack\n");
	//printf("TheMartian AndyWeir 4 PaperBack\n");
	//printf("ToKillAMockingBird HarperLee 5 PaperBack\n");


	sortLibrary(library, *length);
	printLibrary(library, *length);
	writeLibrary(library, *length, argv[2]);

	free(library);
	
	int i;
	for (i = 0; i < *length; i++)
	{	
		free(library[i].name);
		free(library[i].author);
	}

	return 0;
}

Library loadLibrary(const char* filename, int* lenPtr) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Failed to open file %s\n", filename);
		//*lenPtr = 0;
		return NULL;
	}

	fscanf(fp, "%d", lenPtr);
	Library library = malloc(sizeof(Book) * *lenPtr);

	int i;
	for (i = 0; i < *lenPtr; i++) {
		library[i].name = malloc(sizeof(char)* 30);
		library[i].author = malloc(sizeof(char)* 30);
		fscanf(fp, "%s %s %d %u", library[i].name, library[i].author, &library[i].rating, &library[i].type);
	}
	fclose(fp);
	return library;
}

void sortLibrary(Library library,  int length) {
	int i;

	for (i = 1; i < length; i++) {
		int j = i;
		while (j > 0 && library[j].rating < library[j - 1].rating) {
			Book temp = library[j];
			library[j] = library[j - 1];
			library[j - 1] = temp;
		}
	}
}

void printLibrary(Library library, int length) {
	int i;
	for (i = 0; i < length; i++) {
		printf("%s %s %d %u", library[i].name, library[i].author, library[i].rating, library[i].type);
		if (library[i].type == PaperBack) {
			printf(" PaperBack\n");
		} else {
			printf(" HardBack\n");
		}
	}
}

void writeLibrary(Library library, int length, const char* filename) {
	FILE* fp = fopen(filename, "w");

	fprintf(fp, "%d\n", length);

	int i;
	for (i = 0; i < length; i++) {
		fprintf(fp, "%s %s %d %u\n", library[i].name, library[i].author, library[i].rating, library[i].type);
	}

	fclose(fp);
}

