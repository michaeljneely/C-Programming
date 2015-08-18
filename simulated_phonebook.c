/*
Michael Neely
C program that simulates a phone book
Allows the use to reads contacts in from a file and search by specified parameters
*/


#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

struct contact
{
	char firstName[50];
	char lastName[50];
	char companyName[50];
	char address[50];
	char city[50];
	char county[50];
	char state[50];
	char zip[50];
	char phone1[50];
	char phone2[50];
	char email[50];
	char web[50];
} ;

int numContacts = 0;
struct contact *contacts;  
int readFile(char *fileName);
int findContact(char *string);
int findCompany(char *string);
int findCity(char *string);
int findCounty(char *string);
int findState(char *string);
int findZip(char *string);

void printContact(struct contact *theContact);
int countLines(char *fileName);

void main()
{
	char string[20];
	char fileName[] = "F:\\C_Labs\\us-500b.txt";
	int i=0;
	int option;

	numContacts = countLines(fileName);

	contacts = (struct contact *)malloc(numContacts*sizeof(struct contact));


	if (!readFile(fileName)) 
	{
		printf( "File could not be opened !!\n" );
		return;
	} 
	puts("Options:\n1-search by name\n2-search by company\n3-search by sity\n4-search by county\n5-search by state\n6-search by zip\n");
	fflush(stdin);
	scanf("%d",&option);

	puts("Enter all \(or part\) of what you are looking for:");
	fflush(stdin);
	gets(string);
	for (i=0;i<strlen(string);i++) //to upper case
	{
		string[i] = toupper(string[i]);
	}
	switch(option)
	{
		case 1:
			findContact(string);
			break;
		case 2:
			findCompany(string);
			break;
		case 3:
			findCity(string);
			break;
		case 4:
			findCounty(string);
			break;
		case 5:
			findState(string);
			break;
		case 6:
			findZip(string);
			break;
		default:
			break;
	}
}

int findContact(char *string)
{
	int i,j,k=0;
	char temp1[20]; //one name (last or first)
	char temp2[20]; //other name (last or first)
	char delim[2] = " "; //split string up by spaces
	char *token;
	int matches = 0; //how many matches the function finds
	if ((token = strtok (string,delim)) != NULL) strcpy(temp1,token); //split up into first and last name if necessary
	if ((token = strtok (NULL,delim)) != NULL) strcpy(temp2,token);
	for (i=0;i<numContacts;i++) //loop through every contact
	{
		for(j=0;j<strlen((contacts)->firstName);j++) //firstName to upper case
		{
			(contacts)->firstName[j] = toupper((contacts)->firstName[j]);
		}
		for(k=0;k<strlen((contacts)->lastName);k++) //lastName to upper case
		{
			(contacts)->lastName[k] = toupper((contacts)->lastName[k]);
		}
		if (strstr((contacts)->firstName,temp1) || strstr((contacts)->lastName,temp1) || strstr((contacts)->firstName,temp2) || strstr((contacts)->lastName,temp2))//if a match in first or last name
		{
			printContact(contacts);
			matches++;
		}
		contacts ++; //go to next struct
	}
	printf("-----------------------------------------\n %d Match(es)\n---------------------------------",matches); //print number of matches
	return matches;
}
int findCompany(char *string)
{
	int i=0, j=0, k=0;
	int matches = 0;
	char temp[5][30]; //containers for split up string (i.e. 'the' 'tire' 'company')
	char delim[2] = " ";
	char *token;
	token = strtok(string,delim);
	while (token != NULL) //split up entered string
	{
		strcpy(temp[i],token);
		i++;
		token=strtok(NULL,delim);
	}
	for(i=0;i<numContacts;i++)
	{
		for(j=0;j<strlen((contacts)->companyName);j++) //companyName to upper
		{
			(contacts)->companyName[j] = toupper((contacts)->companyName[j]);
		}
		for (k=0;k<5;k++) //check each piece of the chopped up user string with the company name
		{
			if (strstr((contacts)->companyName,temp[k]))
			{
				printContact(contacts);
				matches++;
			}
		}
		contacts++; // go to next struct
	}
	printf("-----------------------------------------\n %d Match(es)\n---------------------------------",matches);
	return matches;
}
//The other find funtions use exactly the same logic...
int findCity(char *string)
{
	int i=0, j=0, k=0;
	int matches = 0;
	char temp[5][30];
	char delim[2] = " ";
	char *token;
	token = strtok(string,delim);
	while (token != NULL)
	{
		strcpy(temp[i],token);
		i++;
		token=strtok(NULL,delim);
	}
	for(i=0;i<numContacts;i++)
	{
		for(j=0;j<strlen((contacts)->city);j++)
		{
			(contacts)->city[j] = toupper((contacts)->city[j]);
		}
		for (k=0;k<5;k++)
		{
			if (strstr((contacts)->city,temp[k]))
			{
				printContact(contacts);
				matches++;
			}
		}
		contacts++;
	}
	printf("-----------------------------------------\n %d Match(es)\n---------------------------------",matches);
	return matches;
}
int findCounty(char *string)
{
	int i=0, j=0, k=0;
	int matches = 0;
	char temp[5][30];
	char delim[2] = " ";
	char *token;
	token = strtok(string,delim);
	while (token != NULL)
	{
		strcpy(temp[i],token);
		i++;
		token=strtok(NULL,delim);
	}
	for(i=0;i<numContacts;i++)
	{
		for(j=0;j<strlen((contacts)->county);j++)
		{
			(contacts)->county[j] = toupper((contacts)->county[j]);
		}
		for (k=0;k<5;k++)
		{
			if (strstr((contacts)->county,temp[k]))
			{
				printContact(contacts);
				matches++;
			}
		}
		contacts++;
	}
	printf("-----------------------------------------\n %d Match(es)\n---------------------------------",matches);
	return matches;
}
int findState(char *string)
{
	int i=0, j=0, k=0;
	int matches = 0;
	char temp[5][30];
	char delim[2] = " ";
	char *token;
	token = strtok(string,delim);
	while (token != NULL)
	{
		strcpy(temp[i],token);
		i++;
		token=strtok(NULL,delim);
	}
	for(i=0;i<numContacts;i++)
	{
		for(j=0;j<strlen((contacts)->state);j++)
		{
			(contacts)->state[j] = toupper((contacts)->state[j]);
		}
		for (k=0;k<5;k++)
		{
			if (strstr((contacts)->state,temp[k]))
			{
				printContact(contacts);
				matches++;
			}
		}
		contacts++;
	}
	printf("-----------------------------------------\n %d Match(es)\n---------------------------------",matches);
	return matches;
}
int findZip(char *string)
{
	int i=0, j=0, k=0;
	int matches = 0;
	char temp[5][30];
	char delim[2] = " ";
	char *token;
	token = strtok(string,delim);
	while (token != NULL)
	{
		strcpy(temp[i],token);
		i++;
		token=strtok(NULL,delim);
	}
	for(i=0;i<numContacts;i++)
	{
		for(j=0;j<strlen((contacts)->zip);j++)
		{
			(contacts)->zip[j] = toupper((contacts)->zip[j]);
		}
		for (k=0;k<5;k++)
		{
			if (strstr((contacts)->zip,temp[k]))
			{
				printContact(contacts);
				matches++;
			}
		}
		contacts++;
	}
	printf("-----------------------------------------\n %d Match(es)\n---------------------------------",matches);
	return matches;
}

void printContact(struct contact *theContact)
{
	printf("\nFirst Name: %s",(theContact)->firstName); //get item in struct and print...
	printf("\nLast Name: %s",(theContact)->lastName);
	printf("\nCompany Name: %s",(theContact)->companyName);
	printf("\nAddress: %s",(theContact)->address);
	printf("\nCity: %s",(theContact)->city);
	printf("\nCounty: %s",(theContact)->county);
	printf("\nState: %s",(theContact)->state);
	printf("\nZip Code: %s",(theContact)->zip);
	printf("\nPhone #1: %s",(theContact)->phone1);
	printf("\nPhone #2: %s",(theContact)->phone2);
	printf("\nEmail Address: %s",(theContact)->email);
	printf("\nWeb Site: %s",(theContact)->web);
}

int countLines(char *fileName)
{
	char line[200];
	FILE *fptr = fopen(fileName, "r");
	int nLines = 0;

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
		return 0;
	}

	// use fgets to skip first line
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
	FILE *fptr = fopen(fileName, "r");
	char *token;
	char delim[6]=",";  
	int n=0,i=0;

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
		return 0;
	}

	// use fgets to skip first line
	fgets (line, 200, fptr);

	//first data line
	fgets (line,200,fptr);
	while (!feof(fptr))
	{ 
		if ((token = strtok (line,delim)) != NULL) strcpy((contacts+n)->firstName,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->lastName,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->companyName,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->address,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->city,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->county,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->state,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->zip,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->phone1,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->phone2,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->email,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->web,token);
		//printContact((contacts+n));
		n++;
		//next data line
		fgets (line,200,fptr);

	} 
     
	fclose (fptr);

	return 1;
}

