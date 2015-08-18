/*
Michael Neely
C program to process a data file which contains tab delimited results, then
finds and outputs a single line in the file or all the data from a range via
command line arguments
*/


#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int readResults(char *inPath);
int writeRange(char *start, char *end, int toFile, char *outPath);
int writeSingle(char *firstName, char *lastName, int toFile, char *outPath);

typedef struct
{
	int ID;
	char firstName[25];
	char lastName[25];
	char english, french, maths, philosophy;
} student;

student students[100];
int ns = 0;

void main( int argc, char *argv[] )
{ 
	char *firstName, *lastName;
	char *start, *end;
	char *inPath = argv[1];
	char *outPath = NULL;
	char *findmethod = argv[2];
	char *outputmethod = NULL;
	int toFile = 0; // if user wants output to file or not
	ns = 0;
	if (argc > 5) //if number of args great enough, check for '\o'
	{
		outputmethod = argv[5];
		if (!strcmp(outputmethod, "/o"))
		{
			toFile = 1;
		}
	}
	if (argc > 6) //get file Outpath if number of args great enough
	{
		outPath = argv[6];
	}
	readResults(inPath); //fill structures
	if (!strcmp(findmethod,"/s")) //if user wants single
	{
		firstName = argv[3];
		lastName = argv[4];
		writeSingle(firstName,lastName,toFile,outPath);
	}
	else if (!strcmp(findmethod,"/r")) //if user wants range
	{
		start = argv[3];
		end = argv[4];
		writeRange(start,end,toFile,outPath);
	}
}

/* this function reads the data file and populates the array of student data structures */
int readResults(char *inPath)
{
	char temp[200];
	FILE *fptr;
	fptr = fopen(inPath, "r");

	if (fptr == NULL)
	{
		printf ("Error in readResults opening data file: %s \n", inPath);
		return 0;
	}

	fgets(temp,200, fptr);
	fscanf(fptr,"%d %s %s %c %c %c %c", &students[ns].ID,students[ns].firstName, students[ns].lastName,&students[ns].english,
		&students[ns].maths, &students[ns].french,&students[ns].philosophy);

	while (!feof(fptr))
	{
		ns++;
		fscanf(fptr,"%d %s %s %c %c %c %c", &students[ns].ID,students[ns].firstName, students[ns].lastName,&students[ns].english,
			&students[ns].maths, &students[ns].french,&students[ns].philosophy);
	}
	fclose(fptr);
	return 1;
}
/*
this function prints out the results for students in the range start-end
if toFile is false then the results are written to the stdout
if tofile is true then the results are written to the file specified by outPath
*/
int writeRange(char *start, char *end, int toFile, char *outPath)
{
	
	int i = 0; //counter
	int lbound, upbound; //bounds of range
	for(i=0;i<ns;i++) //generate range
	{
		if (!strcmp(start,students[i].lastName))
		{
			lbound = i;
		}
		if (!strcmp(end, students[i].lastName))
		{
			upbound = i;
		}
	}
	if(toFile == 1) //if output to file
	{
		FILE *outptr = fopen(outPath,"w");
		if (outptr == NULL)
		{
			printf ("Error");
			return 0;
		}
		while (lbound <= upbound) //loop to output to file
		{
			fprintf(outptr,"\n%d %s %s %c %c %c %c", students[lbound].ID,students[lbound].firstName, students[lbound].lastName,students[lbound].english,
			students[lbound].maths, students[lbound].french,students[lbound].philosophy);
			lbound++;
		}
		fclose(outptr);
	}
	else //print range to stdout
	{
		while( lbound <= upbound)
		{
			printf("\n%d %s %s %c %c %c %c", students[lbound].ID,students[lbound].firstName, students[lbound].lastName,students[lbound].english,
			students[lbound].maths, students[lbound].french,students[lbound].philosophy);
			lbound++;
		}
		printf("\n");
	}
	return 1; //end
}

/*
this function prints out the results for a students with
the given firstName and lastName
if toFile is false then the results are written to the stdout
if tofile is true then the results are written to the file specified by outPath
*/
int writeSingle(char *firstName, char *lastName, int toFile, char *outPath)
{
	int i = 0; //counter
	if (toFile == 1) //if user wants to output to file
	{
		FILE *outptr = fopen(outPath,"w");
		if (outptr == NULL)
		{
			printf ("Error");
			return 0;
		}
		for (i=0;i<ns;i++) //find desired student and output to file
		{
			if (!strcmp(firstName,students[i].firstName) && !strcmp(lastName,students[i].lastName))
			{
				fprintf(outptr,"%d %s %s %c %c %c %c", students[i].ID,students[i].firstName, students[i].lastName,students[i].english,
				students[i].maths, students[i].french,students[i].philosophy);
			}
		}
		fclose(outptr);
	}
	else //print to stdout
	{
		for (i=0;i<ns;i++) //loop to find student
		{
			if (!strcmp(firstName,students[i].firstName) && !strcmp(lastName,students[i].lastName))
			{
				printf("%d %s %s %c %c %c %c", students[i].ID, students[i].firstName, students[i].lastName,students[i].english,
				students[i].maths,students[i].french,students[i].philosophy);
			}
		}
		printf("\n");
	}
	return 1; //end
}
