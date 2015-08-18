/*
Michael Neely
C program that reads CSV file of sales data and finds total sales by a certain category
*/
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct sale //data structure for each sale
{
	char day[3];
	char month[3];
	char year[3];
	char region[10];
	char rep[15];
	char item[15];
	int units;
	double unit_cost;
	double total;
};
FILE *fptr;
struct sale s[44]; //44 fictional sales

int getOption(); //asks user for option
char commaChecker(char string[]); //swaps commas with char before it, e.g. 1,648 becomes ,1648
double totalSalesByRegion(char string[]); //calculate total sales by region
double totalSalesByRep(char string[]); //calculate total sales by rep
double totalSalesByItem(char string[]); //calculate total sales by item
double totalSalesByYear(char string[]); //calculate total sales by year

void main(){
	char fileName[]="SampleData.txt";
	char temp[250];
	char *token;
	char delimiters[]=",/:\t\"\n ";
	char tempValues[10][10];
	char region[10];
	char rep[15];
	char item[15];
	char year[3];
	double total;
	int option = 0;
	int i = 0, j =0;
	fptr = fopen(fileName, "r+");

	if ( fptr  == NULL ) //ensure proper file opening
	{
		printf( "File could not be opened.\n" );
		return;
	} 
	else 
	{ 
			fgets(temp,250,fptr); //skip first line
			
			while(!feof(fptr)) //read until end of file
			{
				int i=0;
				fgets(temp,250,fptr); //scan in a single line
				commaChecker(temp); //eliminate issues with commas
				token = strtok(temp,delimiters); //divide string up
				while(token != NULL)
				{
					strcpy(tempValues[i],token); //copy token strings to spots in teh tempValues array
					i++;
					token=strtok(NULL,delimiters);
				}
				strcpy(s[j].month,tempValues[0]); //first token was month
				strcpy(s[j].day,tempValues[1]); //second token was day
				strcpy(s[j].year,tempValues[2]); //third token was year
				strcpy(s[j].region,tempValues[3]); //fourth token was region
				strcpy(s[j].rep,tempValues[4]); //fifth token was rep
				strcpy(s[j].item,tempValues[5]); //6th token was item
				s[j].units = atoi(tempValues[6]); //7th token was units --> converted to integer
				s[j].unit_cost = atof(tempValues[7]); //8th token was unit_cost --> converted to double
				s[j].total = atof(tempValues[8]); //9th token was total --> converted to double
				j++; //go to next structure
			}
	}
	fclose(fptr);
	option = getOption(); //ask user for option
	while (option != 0)
	{
		if (option == 1) //sales by region
		{
			printf("Enter Region: ");
			fflush(stdin);
			scanf("%s",region);
			total = totalSalesByRegion(region); //calculate total sales
			printf("\nTotal Sales by %s Region: %.2lf\n",region, total);
		}
		if (option == 2) // sales by rep
		{
			printf("Enter Rep: ");
			fflush(stdin);
			scanf("%s",rep);
			total = totalSalesByRep(rep); //calculate total sales
			printf("\nTotal Sales by \"%s\": %.2lf\n",rep, total);
		}
		if (option == 3) //sales by item
		{
			printf("Enter Item: ");
			fflush(stdin);
			scanf("%s",item);
			total = totalSalesByItem(item); //calculate total sales
			printf("\nTotal Sales of \"%s\": %.2lf\n",item,total);
		}
		if (option == 4) //sales by year
		{
			printf("Enter Year (2digits): ");
			fflush(stdin);
			scanf("%s",year);
			total = totalSalesByYear(year); //calculate total sales
			printf("\nTotal Sales in Year \"%s\": %.2lf\n",year,total);
		}
		if (option == 0) return; //exit
		option = getOption(); //allows users to use functions more than once before exiting
	}
	
}

int getOption() //gets user option
{
	int option = 0;

	puts("\n===============================================================================\nEnter one of the Following Options:\n1 - Sales by Region\n2 - Sales by Rep\n3 - Sales by Item\n4 - Sales by Year\n0 - Quit\n===============================================================================\n");
	fflush(stdin);
	scanf("%d", &option);
	return option;
}
char commaChecker(char string[]) //takes comma out of number
{
	int i = 0;
	int len = strlen(string);
	char temp[2];
	for (i=0;i<len;i++)
	{
		if (string[i] == ',') //swaps comma with char before it
		{
			temp[0] = string[i-1];
			string[i] = temp[0];
			string[i-1] = ',';
		}
	}
	return 1;
}

double totalSalesByRegion(char string[])
{
	int i = 0;
	double regionalTotal = 0.0;
	for (i=0;i<44;i++)
	{
		if (!strcmp(string,s[i].region)) //add to regionalTotal only if the structure region matches user entered region
		{
			regionalTotal += s[i].total;
		}
	}
	return regionalTotal;
}
double totalSalesByRep(char string[])
{
	int i = 0;
	double repTotal = 0.0;
	for (i=0;i<44;i++)
	{
		if (!strcmp(string,s[i].rep)) //add to repTotal only if the structure rep matches user entered rep
		{
			repTotal += s[i].total;
		}
	}
	return repTotal;
}

double totalSalesByItem(char string[])
{
	int i = 0;
	double itemTotal = 0.0;
	for (i=0;i<44;i++)
	{
		if (!strcmp(string,s[i].item)) //add to itemTotal only if the structure item matches user entered item
		{
			itemTotal += s[i].total;
		}
	}
	return itemTotal;
}
double totalSalesByYear(char string[])
{
	int i = 0;
	double yearTotal = 0.0;
	for (i=0;i<44;i++)
	{
		if (!strcmp(s[i].year,string)) //add to yearTotal only if the structure year matches user entered year
		{
			yearTotal += s[i].total;
		}
	}
	return yearTotal;
}

//END
