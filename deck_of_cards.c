//Michael Neely

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/* This program randomizes a created deck of cards using a Fisher-Yates Shuffle, and deals as many
hands of 5 cards as specified by the user */

struct card {
	char face;
	char suit;
	int cardNumber;
};

void fillDeck(struct card deck[]);

void shuffleDeck(struct card deck[]);

void deal(struct card deck[], int handsDealt);

void main ()
{
	struct card deck[52];
	int handsDealt = 0;
	int j = 0;
	printf("How many hands would you like to deal?: ");
	fflush(stdin);
	scanf_s("%d", &handsDealt, 2);
	if (handsDealt > 10)
	{
		printf("That's too many!");
		main();
	}
	else
	{
		fillDeck(deck);
		shuffleDeck(deck);
		deal(deck, handsDealt);
	}
	int repeat = 0;
	puts("Repeat? 1 for yes");
	fflush(stdin);
	scanf_s("%d", &repeat, 1);
	if (repeat == 1)
	{
		main();
	}
	else
	{
		exit(0);
	}
}

void fillDeck(struct card deck[])
{
	int i,j;
	int icard = 0;
	char suits[10] = {3,4,5,6};
	char faces[13] = {'A','2','3','4','5','6','7','8','9','X','J','Q','K'};
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<13;j++)
		{
			deck[icard].suit = suits[i];
			deck[icard].face = faces[j];
			icard++;
		}
	}
}

/*Fisher-Yates Shuffle */
void shuffleDeck(struct card deck[])
{
	int i,j;
	struct card temp;
	srand( time( NULL ) );
	for (i=51;i>0;i--)
	{
		j = rand() % 52;
		temp = deck[ i ];
		deck[ i ] = deck[ j ];
		deck[ j ] = temp;
	}
}

void deal(struct card deck[], int handsDealt)
{
	int i=0;
	for (i=0;i<handsDealt;i++)
	{
		int j =0;
		printf("Hand #%d:  ", i+1);
		for (j=i*5;j<=4+(i*5);j++)
		{
			printf("%c%c\t", deck[j].face, deck[j].suit);
		}
		printf("\n");
	}
	printf("\n\n");
}
