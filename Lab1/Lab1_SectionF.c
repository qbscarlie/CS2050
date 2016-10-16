/***
  Carlie Procell
  Section F
  Lab 1
  ***/

#include <stdio.h>
#include <stdlib.h>

double* read_file(char* filename, int len);
double find_min(double* array, int len);
double find_max(double* array, int len);
double find_avg(double* array, int len);
void write_to_file(char* filename, double* array, int len);

int main(int argc, char* argv[])
{
	if(argc!=4)
	{
		printf("\nInsuffiient arguments\n");
		return 0;
	}
	int len=atoi(argv[1]);
	if(read_file(argv[2],len)==0)
	{
		printf("\nError opening file.\n");
		return 0;
	}
	double* array=read_file(argv[2],len);
	double min = find_min(array,len);
	printf("min: %lf\n", min);
	double max = find_max(array,len);
	printf("max: %lf\n", max);
	double avg = find_avg(array,len);
	printf("avg: %lf\n", avg);
	write_to_file(argv[3],array,len);
	free(array);
	return 1;
}

double* read_file(char* filename, int len)
{
	FILE* input=fopen(filename, "r");
	if(input==NULL)
	{
		return 0;
	}
	int i;
	double* array=malloc(sizeof(double)*len);
	for(i=0;i<len;i++)
	{
		fscanf(input, "%lf", (array+i));
	}
	fclose(input);
	return array;
}

double find_min(double* array, int len)
{
	int i;
	double min = *(array+0);
	for(i=1;i<len;i++)
	{
		if(*(array+i)<(min))
			min=*(array+i);
	}
	return min;
}

double find_max(double* array, int len)
{
	int i;
	double max = *(array+0);
	for(i=1;i<len;i++)
	{
		if(*(array+i)>(max))
			max=*(array+i);
	}
	return max;
}

double find_avg(double* array, int len)
{
	int i;
	double sum=0, avg;
	for(i=0;i<len;i++)
	{
		sum+=*(array+i);
	}
	avg=sum/len;
	return avg;
}

void write_to_file(char* filename, double* array, int len)
{
	FILE* output=fopen(filename, "w");
	int i;
	for(i=len;i>=0;i--)
	{
		fprintf(output, "%lf\n", *(array+i));
	}
}
