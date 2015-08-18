/*
Michael Neely
Analyze CSV file of gas prices and find:
	-> The month with the highest price
	-> The year with the highest price
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stdafx.h"

typedef struct
{
	int year;
	double price[12];
	double average;
} gasoline;

gasoline records[30]; //make 30 record structures

char months[12][10]={"January","February","March","April","May","June","July","August","September","October","November","December"};
//for ease of printing out the month ^

int getOption(); //prompt user for option
int readFile(); //read file and populate data structures
double monthHighest(); //find month with the highest gas price
double yearHighest(); //find year with the highest annual average gas price

void main(){
	int option;
	readFile();
	option = getOption(); //prompt user for desired action
	while (option != 0) //while user doesn't want to exit
	{
		if (option == 1)
		{
			monthHighest(); //find month with highest price
		}
		if (option == 2)
		{
			yearHighest(); //find year with highest average price
		}
		if (option == 0) return; //exit
		option = getOption(); //else prompt user for another action
	}
}

int getOption()
{
	int option = 0;
	puts("\n===============================================================================\n Enter Choice:\n0 - Quit\n1 - Find the month with the highest price   \n2 - Find the year with the highest average price\n===============================================================================\n");
	//menu ^
	fflush(stdin);
	scanf("%d", &option); //get option
	return option;
}
int readFile(){
	char fileName[]="gasoline.txt"; //path to file
	char temp[250]; //temp string to hold a line from file
	char delim[] = "\t"; //delimiter of file (tab in this case)
	char *token; 
	char tempValues[13][20]; //array of strings to temporarily hold results of strtok
	int i = 0; //structure loop counter
	int j = 0; //tempValues loop counter 
	int k = 0; //price per month loop counter 
	FILE *fptr;
	fptr = fopen(fileName, "r+"); //open file
	if (fptr == NULL) //if cannot be opened
	{
		printf("\nError opening file.\n"); //standard error
		return 0; //unsuccessful termination
	}
	else
	{
		fgets(temp,250,fptr); //skip 1st 3 lines...
		fgets(temp,250,fptr);
		fgets(temp,250,fptr);
		while (!feof(fptr)) //while not end of file
		{
			fgets(temp,250,fptr); //read in line
			j=0; //reset value of j
			if (!strcmp(temp,"0")) //break if string is "0" (end of table as shown on gasoline.txt)
			{
				break;
			}
			else
			{
				token = strtok(temp,delim); //split line up into tokens
				while (token != NULL)
				{
					strcpy(tempValues[j],token); //copy token into tempValues array
					j++; //next slot in tempValues array
					token=strtok(NULL,delim); //continue loop
				}
				records[i].average = 0.0;
				records[i].year = atoi(tempValues[0]); //year is held in tempValues[0] (needs to be converted to int)
				for(k=0;k<12;k++) //loop through months k
				{
					records[i].price[k] = atof(tempValues[k+1]); //tempValues[1] through tempValues[13] are prices per month. (jan->dec)
					records[i].average += records[i].price[k]; //add price per month to year's average
				}
				records[i].average = ((records[i].average) / (12)); //calculate annual average (division by 12 months)
				i++; //go to next structure
			}
		}
		fclose(fptr); //close file
		return 1; //successful termination
	}
}

double monthHighest() //find highest monthly price of gasoline in structures
{
	int i,j;
	double highestPrice = 0.0;
	int year= 0; //year of highest price
	int month = 0; //month of highest price 
	for (i=0;i<30;i++) //structure loop
	{
		for(j=0;j<12;j++) //price per month loop
		{
			if (records[i].price[j] > highestPrice) //if next encountered price is greater than current value
			{
				highestPrice = records[i].price[j]; //update highest price
				year = records[i].year; //get year of highest price
				month = j; //get month of highest price
			}
		}
	}
	printf("\nHighest Price Month was: %lf in %s of %d\n",highestPrice, months[month], year); //print out results
	return highestPrice;
}

double yearHighest()
{
	int i;
	int year = 0; //year with highest average price
	double highestPrice = 0.0;
	for (i=0;i<30;i++) //structure loop
	{
		if (records[i].average > highestPrice) //if next encountered average price is greater
		{
			highestPrice = records[i].average; //update highest average price
			year = records[i].year; //update year of highest average price
		}
	}
	printf("\nHighest Annual Average Price was %lf in %d\n",highestPrice,year); //print out results
	return highestPrice;
}
