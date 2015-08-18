//Michael Neely

/*This programs reads CSV data from a Shimmer Sensor (accelerometer) that is strapped to a user.
It determines if a fall occurred at any point during the time interval captured by the CSV file. */

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>


struct dataPoint
{
	int timestamp;
	int x;
	int y;
	int z;
	int sum;
};

int countLines(char *fileName);
int readFile(char *fileName);
int fallDetector(char *fileName);

int numPoints = 0;
struct dataPoint *points;

void main()
{
	char fileName[50];
	printf("Enter file path: \n? ");
	scanf("%s",fileName);
	numPoints = countLines(fileName);
	points = (struct dataPoint *)malloc(numPoints*sizeof(struct dataPoint));
	if (!readFile(fileName)) 
	{
		printf( "File could not be opened !!\n" );
		exit(0);
	}
	if (fallDetector(fileName))
	{
		puts("\nAlerting Authorities");
		exit(0);
	}
	printf("No fall detected...\n");
}

int countLines(char *fileName)
{
	char line[200];
	FILE *fptr = fopen(fileName, "r+");
	int nLines = 0;

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
		return 0;
	}
	fgets (line, 200, fptr);
	fgets (line,200,fptr);
	while (!feof(fptr))
	{ 
		nLines++;
		fgets (line,200,fptr);
	}

	fclose (fptr);

	return nLines;
}

int readFile(char *fileName)
{
	char line[200];
	FILE *fptr = fopen(fileName, "r+");
	char *token;
	int n=0;

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
		return 0;
	}
	fgets (line, 200, fptr);
	fgets (line,200,fptr);
	while (!feof(fptr))
	{ 
		if ((token = strtok (line,",")) != NULL) (points+n)->timestamp = atoi(token);
		if ((token = strtok (NULL,",")) != NULL) (points+n)->x = atoi(token);
		if ((token = strtok (NULL,",")) != NULL) (points+n)->y = atoi(token);
		if ((token = strtok (NULL,",")) != NULL) (points+n)->z = atoi(token);
		(points+n)->sum = (points+n)->x + (points+n)->y + (points+n)->z;
		n++;
		fgets (line,200,fptr);
	} 
	fclose (fptr);
	return 1;
}

int fallDetector(char *fileName)
{
	int i,j,k = 0;
	int fallLocation = 0;
	int flat = 0;
	for(i=0;i<numPoints;i++)
	{
		if ((points+i)->sum < 600) //if small total acceleration (means person is falling)
		{
			fallLocation = i;
			for(j=fallLocation;j<(fallLocation + 10);j++)
			{
				if((points+(j+1))->sum - (points+j)->sum > 3000) //if big spike afterwards (person hits the ground)
				{
					for(k=fallLocation;k<(fallLocation+50);k++)
					{
						if(abs((points+(k+1))->sum - (points+k)->sum) < 300) //if flat section
						{
							flat++;
						}
					}
					if (flat >= 20)// if a lot of flat sections (person is laying on ground)
					{
						printf("\nFall detected at timestamp: %d",(points+fallLocation)->timestamp); //fall detected
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
