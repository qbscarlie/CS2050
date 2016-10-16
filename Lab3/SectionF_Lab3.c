/***
  Carlie Procell
  Prelab3
  Section F
  ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	int id;
	char name[20];
	float gpa;
} Student;

//function prototypes
Student findStudent(FILE* fp, int studentId);
Student* getClass(const char* classFile, const char* studentFile, int* len);
void bubbleSort(Student* students, int len);
void storeClass(const char* filename, Student* students, int len);
void printClass(Student* students, int len);
int numStudentsInBinaryFile(const char* filename);

//main function
int main(int argc, char* argv[])
{
	if(argc!=4)
	{
		printf("Insufficient arguments\n");
		return 0;
	}
	int len;
	Student* array = getClass(argv[1], argv[2], &len);
	bubbleSort(array, len);
	char* output = argv[3];
	storeClass(output, array, len);
	printClass(array, len);
	int numstudents;
	numstudents = numStudentsInBinaryFile(argv[2]);
	printf("\n number of students may or may not be %d", numstudents);
	free(array);
	return 0;
}

//function to find students
Student findStudent(FILE* fp, int studentId)
{
	fseek(fp, sizeof(Student)* (studentId-1), SEEK_SET);
	Student var;
	fread(&var, sizeof(Student), 1, fp);
	return var;
}

//function to get class
Student* getClass(const char* classFile, const char* studentFile, int* len)
{
	FILE* classFile1=fopen(classFile, "r");
	if(classFile==NULL)
		return 0;
	FILE* studentFile1=fopen(studentFile, "rb");
	if(studentFile==NULL)
		return 0;
	fscanf(classFile1, "%d", len);
	Student* array=malloc(sizeof(Student)* *len);
	int i, studentid;
	for(i=0;i<*len;i++)
	{
		fscanf(classFile1, "%d", &studentid);
		array[i] = findStudent(studentFile1, studentid);
	}
	fclose(classFile1);
	fclose(studentFile1);
	return array;
}

//function to sort based on gpa from high to low
void bubbleSort(Student* students, int len)
{
	int i,j, swapid;
	double swap;
	char swapname[100];
	for(i=1;i<len;i++)
	{
		for(j=0;j<len-1;j++)
		{
			if(students[j].gpa < students[j+1].gpa)
			{
				swap = students[j].gpa;
				students[j].gpa = students[j+1].gpa;
				students[j+1].gpa = swap;
				
				strcpy(swapname,students[j].name);
				strcpy(students[j].name, students[j+1].name);
				strcpy(students[j+1].name, swapname);

				swapid = students[j].id;
				students[j].id = students[j+1].id;
				students[j+1].id = swapid;
			}
		}
	}
}

//function to store into new binary file
void storeClass(const char* filename, Student* students, int len)
{
	FILE* filenameptr=fopen(filename, "wb");
	fwrite(students, len, sizeof(students), filenameptr);
	fclose(filenameptr);
}

//function to print sorted list
void printClass(Student* students, int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		printf("\n%d %s %f\n", students[i].id, students[i].name, students[i].gpa);
	}
}

int numStudentsInBinaryFile(const char* filename)
{
	FILE *filenameptr = fopen(filename, "rb");
	fseek(filenameptr, 0, SEEK_END);
	int len;
	len = ftell(filenameptr);
	fclose(filenameptr);
	return len/sizeof(Student);
}
