/*
Michael Neely
C program to practice linked lists
*/

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node
{
	int nodeID;
	char nodeName[50];
	struct node*next;
};

typedef node Node;
typedef Node *NodePtr;

void insertNode(NodePtr *sptr, int id, char name[]);
int deleteNode(NodePtr *sptr, int id);
void printList(NodePtr currentPtr);
int searchList(NodePtr currentPtr,int id);
int isEmpty(NodePtr sptr);
int enterChoice( void );

int main()
{
	int choice, id;
	char name[50];
	NodePtr start = NULL;
	while ( ( choice = enterChoice() ) != 5 )
	{ 
		switch ( choice ) {
		case 1: //add node
			printf("\nEnter Id of new node: ");
			fflush(stdin);
			scanf("%d",&id);
			printf("Enter Name of new node: ");
			fflush(stdin);
			scanf("%s",name);
			insertNode(&start, id, name);
			break;
		case 2: //delete node
			if (!isEmpty(start)) //if list isnt empty
			{
				printf("\nEnter ID of node to be deleted: ");
				fflush(stdin);
				scanf("%d",&id);
				if(deleteNode(&start,id)) //delete node with user entered id
				{
					printf("\nNode with ID %d deleted.",id);
				}
				else
				{
					printf("Node with ID %d not found",id);
				}
			}
			else
			{
				printf("\nList is Empty :(");
			}
			break;
		case 3: //print nodes
			printList(start);
			break;
		case 4: //search for node
			printf("Enter ID of node to search for: ");
			fflush(stdin);
			scanf("%d",&id);
			if (searchList(start,id) == 0) //if not found
			{
				printf("\n\Node with ID %d not found.",id);

			}
			break;
		default:
			printf("\nIncorrect choice!\n");
			break;
		}

	}
return 0;
}
int enterChoice( void )
{ 
   int menuChoice;
   printf( "\n\n\nEnter your choice\n"
      "1 - Insert a NODE into the list\n"
      "2 - Delete a NODE from the list\n"
      "3 - Display the List\n"
      "4 - Search the List\n"
      "5 - End Program\n---------------------------------------------------------------\n? " );
   fflush(stdin);
   scanf( "%d", &menuChoice );
   return menuChoice;
}

void insertNode(NodePtr *sptr, int id, char name[])
{
	NodePtr newPtr;
	NodePtr previousPtr;
	NodePtr currentPtr;

	newPtr = (struct node *)malloc( sizeof( node ) );

	if (newPtr != NULL) //if space
	{
		newPtr->nodeID = id;
		strcpy(newPtr->nodeName,name);
		newPtr->next = NULL;

		previousPtr = NULL;
		currentPtr = *sptr;

		while(currentPtr != NULL && id > currentPtr->nodeID) //find correct location for insertion
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}
		if (previousPtr == NULL) //insert at beginning
		{
			newPtr->next = *sptr;
			*sptr = newPtr;
		}
		else //order by ID
		{
			previousPtr->next = newPtr;
			newPtr->next = currentPtr;
		}
	}
	else
	{
		printf("\nunable to create node :( ");
	}
}

int deleteNode(NodePtr *sptr, int id)
{
	NodePtr previousPtr;
	NodePtr tempPtr;
	NodePtr currentPtr;

	if (id == (*sptr)->nodeID) //delete first Node
	{
		tempPtr = *sptr;
		*sptr = (*sptr)->next;
		free(tempPtr);
		return id;
	}
	else 
	{
		previousPtr = *sptr;
		currentPtr = (*sptr)->next;
		while (currentPtr != NULL && currentPtr->nodeID != id) //find location
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}
		if (currentPtr != NULL) //delete node
		{
			tempPtr = currentPtr;
			previousPtr->next = currentPtr->next;
			free(tempPtr);
			return id;
		}
	}
	return '\0';
}
int isEmpty(NodePtr sptr) //return 1 if list is empty
{
	return sptr == NULL;
}

void printList(NodePtr currentPtr)
{
	if (currentPtr == NULL)
	{
		printf("\n Empty List :( ");
	}
	else
	{
		while (currentPtr != NULL) //while not at end of list
		{
			printf("\n\nNode details:\n-----------------------------\nID: %d\nName: %s",currentPtr->nodeID,currentPtr->nodeName);
			currentPtr = currentPtr->next; //go to next node
		}
	}
}
int searchList(NodePtr currentPtr,int id)
{
	if (currentPtr == NULL)
	{
		printf("\n Empty List :( ");
	}
	else
	{
		while (currentPtr != NULL) //while not at end of list
		{
			if(currentPtr->nodeID == id) //if match found
			{
				printf("\n\nNode found! \n\nNode details:\n-----------------------------\nID: %d\nName: %s",currentPtr->nodeID,currentPtr->nodeName);
				return 1;
			}
			else //go to next node
			{
				currentPtr = currentPtr->next;
			}
		}
	}
	return 0;
}
