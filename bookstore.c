/*
Michael Neely
C program that simulates a Book Store
Allows the user to create and modify book structures and write to a text file
*/
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

struct book{
	char title[20];
	char author[20];
	int year;
	int isbn;
	double wholesale_price;
	double retail_price;
};

int enterChoice(void);
void writeToTextFile(FILE *readPtr);
void updatePrice(FILE *fptr);
void newBook(FILE *fptr);
void deleteBook(FILE *fptr);

int main()
{
	FILE *fp;
	int choice;
	int i=0;
	if ((fp = fopen("books.dat","rb+"))==NULL) //create binary file with blank records if file pointer returns NULL
	{
		printf("File does not exist\nCreating Binary File with blank records...");
		struct book blankBook = { "","",0,0,0.0,0.0};
		fp = fopen("books.dat","wb+");
		for ( i = 1; i <= 100; i++ ) //write 100 blank book structures
		{
         fwrite( &blankBook, sizeof( struct book ), 1, fp );
		}
		fclose ( fp );
		main();
	}
	else //menu
	{
		while ( ( choice = enterChoice() ) != 5 ) { 

         switch ( choice ) { 
            case 1:
               writeToTextFile( fp );
               break;
            case 2:
               updatePrice( fp );
               break;
            case 3:
               newBook( fp );
               break;
            case 4:
               deleteBook( fp );
               break;
            default:
               printf( "Incorrect choice\n" );
               break;   
         }
      }

      fclose( fp ); 
   }
 
   return 0;
}
int enterChoice( void )
{ 
   int menuChoice;
   printf( "\nEnter your choice\n"
      "1 - store a formatted text file of books called\n"
      "    \"books.txt\" for printing\n"
      "2 - update a retail price\n"
      "3 - add a new record\n"
      "4 - delete a record\n"
      "5 - end program\n? " );
   scanf( "%d", &menuChoice );
   return menuChoice;
}
void writeToTextFile(FILE *readPtr)
{
	FILE *writingPtr;
	struct book temp = { "","",0,0,0.0,0.0}; //temporary structure
	if ( ( writingPtr = fopen( "accounts.txt", "w" ) ) == NULL ) //error handling
	{
      printf( "File could not be opened.\n" );
	}
   else { 
      rewind( readPtr ); //pointer to beginning of file
      fprintf( writingPtr, "%-20s%-20s%-10s%-10s%-15s%15s\n", //title and formatting
         "Title", "Author", "Year","ISBN","Wholesale Price","Retail Price");
      while ( !feof( readPtr ) ) { //print all book structures that actually contain info (isbn != 0)
         fread( &temp, sizeof( struct book ), 1, readPtr );
         if ( temp.isbn != 0 ) {
            fprintf( writingPtr, "%-20s%-20s%-10d%-10d%-15.2lf%15.2lf\n",
               temp.title, temp.author,temp.year,temp.isbn,temp.wholesale_price,temp.retail_price);
         }
      }
	  printf("\nSuccessful output to file.\n");
      fclose( writingPtr );
   }
}
void updatePrice(FILE *fptr)
{
	int ISBN;
   double newPrice;
   struct book temp = {"","",0,0,0.0,0.0}; //temp book struct
   printf( "Enter isbn of book whose retail price you want to update ( 1 - 100 ): " );
   fflush(stdin);
   scanf( "%d", &ISBN );
   fseek( fptr, ( ISBN - 1 ) * sizeof( struct book ), SEEK_SET ); //find correct book
   fread( &temp, sizeof( struct book ), 1, fptr ); //read in info
   if ( temp.isbn == 0 ) //error handling
   {
      printf( "Book with isbn #%d has no information.\n", ISBN );
   }
   else //print book info, get newPrice, update info and print out updated book
   {
      printf("%-20s%-20s%-10d%-10d%-15.2lf%15.2lf\n",
             temp.title, temp.author,temp.year,temp.isbn,temp.wholesale_price,temp.retail_price);
      printf( "Enter new retail price: \n?");
	  fflush(stdin);
      scanf( "%lf", &newPrice);
      temp.retail_price = newPrice;
      printf( "Updated info: \n%-20s%-20s%-10d%-10d%-15.2lf%15.2lf\n",
             temp.title, temp.author,temp.year,temp.isbn,temp.wholesale_price,temp.retail_price);
      fseek( fptr, ( ISBN - 1 ) * sizeof( struct book ), 
         SEEK_SET );
      fwrite( &temp, sizeof( struct book ), 1, fptr );
   }
}
void newBook(FILE *fptr)
{
   struct book temp = { "","",0,0,0.0,0.0}; //blank book struct

   int newISBN;
   printf( "Enter new isbn number ( 1 - 100 ): " );
   fflush(stdin);
   scanf( "%d", &newISBN );
   fseek( fptr, ( newISBN - 1 ) * sizeof( struct book ), //find correct spot in file
      SEEK_SET );
   fread( &temp, sizeof( struct book ), 1, fptr ); //read in struct
   if ( temp.isbn != 0 ) { //error handling
      printf( "Book with isbn #%d already contains information.\n",
              temp.isbn);
   }
   else { //add user input
      printf( "\nEnter title\n? " );
	  fflush(stdin);
      gets(temp.title);
	  printf( "\nEnter author\n? " );
	  fflush(stdin);
	  gets(temp.author);
	  printf( "\nEnter year\n? " );
	  fflush(stdin);
      scanf( "%d",&temp.year);
	  printf( "\nEnter wholesale price\n? " );
	  fflush(stdin);
      scanf( "%lf",&temp.wholesale_price);
	  printf( "\nEnter retail price\n? " );
	  fflush(stdin);
      scanf( "%lf",&temp.retail_price);
      temp.isbn = newISBN;
      fseek( fptr, ( temp.isbn - 1 ) * //find where to write to in file
         sizeof( struct book ), SEEK_SET );
      fwrite( &temp, . //write to binary file
         sizeof( struct book ), 1, fptr );
   }
}
void deleteBook(FILE *fptr)
{
   struct book temp;
   struct book blank = {"","",0,0,0.0,0.0}; //blank book struct
   int ISBN;
   printf( "Enter isbn number of book to delete ( 1 - 100 ): " );
   scanf( "%d", &ISBN );
   fseek( fptr, ( ISBN - 1 ) * sizeof( struct book ), //find book user wants to delete
      SEEK_SET );
   fread( &temp, sizeof( struct book ), 1, fptr ); //read info in
   if ( temp.isbn == 0 ) //error handling
   {
      printf( "Book with isbn  %d does not exist.\n", ISBN );
   }
   else
   {
	fseek( fptr, ( ISBN - 1 ) * sizeof( struct book ), //find book
         SEEK_SET );
    fwrite( &blank, sizeof( struct book ), 1, fptr ); //overwrite book struct with blank struct
	printf("\nrecord deleted. \n");
   }
}
