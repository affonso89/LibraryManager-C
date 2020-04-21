/*
Create an app to manage books in a library.
App should:
1- Display all books available and borrowed
2- Allow input for new books
3- Remove books from offering
4- Borrow and return books
Use struct.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct book {
  int number;
  char title[27];
  char author[30];
  char availability;
};

// funtions
int displayBooks();

int getCommand();

int numberGen();

int addBook(struct book *newBook);

int delBook();

int borrowBook();

int retBook();

int main(){
  
  displayBooks();
  
  return 0;
}

int displayBooks(){
  system("clear");
  
  printf("===================================================================\n");
  printf("                               LIBRARY                             \n");
  printf("===================================================================\n\n");
  printf("\nCommands:\n[1]ADD\t[2]BORROW\t[3]RETURN\t[4]DEL\t[5]EXIT\n");
  printf("\nNR |           TITLE            |         AUTHOR         |  AVAILABLE\n");
  //printf("01 | Harry Potter               | J. K. Rowling          |     Y\n");
  // display books.txt file
  char line[70];
  FILE *fp = NULL;
  
  fp = fopen("books.txt", "r");
  
  if(fp == NULL){
    perror("Error opening file.");
    return(-1);
  }
  
  while(!feof(fp)){
    fgets(line, 70, fp);
    strcpy(line, strtok(line, "\n"));
    puts(line);
  }
  
  fclose(fp);
  
  getCommand();
}

int getCommand(){
  int com;
  
  struct book newBook;
  struct book *pNewBook;
  pNewBook = &newBook;
  
  printf("\nType your command: ");
  scanf("%d", &com);
  
  if(com == 1){
    addBook(pNewBook);
  } else if(com == 2){
    borrowBook();
  } else if(com == 3){
    retBook();
  } else if(com == 4){
    delBook();
  } else if(com == 5){
    printf("Exiting program.\n");
    return -1;
  }
}

int numberGen(){
  char line[110];
  int number;
  
  FILE *fp = NULL;
  
  fp = fopen("books.txt", "r");
  
  if(fp == NULL){
    perror("Error opening file.");
    return(-1);
  }
  
  while(fgets(line, sizeof(line), fp) != NULL){
    // just get last line, do nothing in loop
  }
  
  sscanf(line, "%d", &number);
  
  return number + 1;
}

int addBook(struct book *newBook){
  FILE *fp = NULL;
  
  fp = fopen("books.txt", "a");
  
  if(fp == NULL){
    perror("Error opening file.");
    return(-1);
  }
  
  newBook->number = numberGen();
  while(getchar() != '\n'){
    continue;
  }
    
  printf("Type the book title: ");
  fgets(newBook->title, 27, stdin);
  strcpy(newBook->title, strtok(newBook->title, "\n")); //removes \n from end of fgets string
  
  printf("Type the book author: ");
  fgets(newBook->author, 30, stdin);
  strcpy(newBook->author, strtok(newBook->author, "\n")); //removes \n from end of fgets string
  
  // adding spaces for formating
  while (strlen(newBook->title) <= 25){
    strcat(newBook->title, " ");
  }
  
  while (strlen(newBook->author) <= 21){
    strcat(newBook->author, " ");
  }
  
  // setting initial availability to Y
  newBook->availability = 'Y';
  
  fprintf(fp, "\n%02d | %s | %s |     %c", newBook->number, newBook->title, newBook->author, newBook->availability);
  
  
  fclose(fp);
  displayBooks();

  return 0;
}

int borrowBook(){
  char line[110];
  int number, bookNumber;
  
  FILE *fp = NULL;
  FILE *ft = NULL;
  
  fp = fopen("books.txt", "r");
  ft = fopen("temp.txt", "w");
  
  if(fp == NULL){
    perror("Error opening file.");
    return(-1);
  }
  
  printf("\nType the book number to be borrowed: ");
  scanf("%d", &bookNumber);
  // check if book number exists
  
  while(fgets(line, sizeof(line), fp) != NULL){
    sscanf(line, "%d", &number);
    
    while(bookNumber > (numberGen() - 1) || bookNumber <= 0){
      printf("\nBook number not found. Type the book number to be borrowed: ");
      scanf("%d", &bookNumber);
    }
    
    if(number == bookNumber && number == (numberGen() - 1)){
      
      while(line[strlen(line) - 1] == 'N'){
        printf("\nBook already borrowed.");
        fflush(stdout);
        sleep(3);
        break;
      }
      
      line[strlen(line) - 1] = 'N';
      fprintf(ft, "%s", line);
      
    } else if(number == bookNumber) {
      
      while(line[strlen(line) - 2] == 'N'){
        printf("\nBook already borrowed.");
        fflush(stdout);
        sleep(3);
        break;
      }
      
      line[strlen(line) - 2] = 'N';
      fprintf(ft, "%s", line);
    } else {
      fprintf(ft, "%s", line);
    }
  }
  
  fclose(fp);
  fclose(ft);
  
  remove("books.txt");
  rename("temp.txt", "books.txt");
  
  displayBooks();
  
  return 0;
}

int retBook(){
  char line[110];
  int number, bookNumber;
  
  FILE *fp = NULL;
  FILE *ft = NULL;
  
  fp = fopen("books.txt", "r");
  ft = fopen("temp.txt", "w");
  
  if(fp == NULL){
    perror("Error opening file.");
    return(-1);
  }
  
  printf("\nType the book number to be returned: ");
  scanf("%d", &bookNumber);
  // check if book number exists
  
  while(fgets(line, sizeof(line), fp) != NULL){
    sscanf(line, "%d", &number);
    
    while(bookNumber > (numberGen() - 1) || bookNumber <= 0){
      printf("\nBook number not found. Type the book number to be returned: ");
      scanf("%d", &bookNumber);
    }
    
    if(number == bookNumber && number == (numberGen() - 1)){
      
      while(line[strlen(line) - 1] == 'Y'){
        printf("\nThis book has not been borrwed yet.");
        fflush(stdout);
        sleep(3);
        break;
      }
      
      line[strlen(line) - 1] = 'Y';
      fprintf(ft, "%s", line);
    } else if(number == bookNumber) {
      
      while(line[strlen(line) - 2] == 'Y'){
        printf("\nThis book has not been borrwed yet.");
        fflush(stdout);
        sleep(3);
        break;
      }
      
      line[strlen(line) - 2] = 'Y';
      fprintf(ft, "%s", line);
    } else {
      fprintf(ft, "%s", line);
    }
  }
  
  fclose(fp);
  fclose(ft);
  
  remove("books.txt");
  rename("temp.txt", "books.txt");
  
  displayBooks();
  
  return 0;
}

int delBook(){
  char line[110];
  char *pline = line +2; // remove first 2 chars from line array
  int number, bookNumber;
  struct book tempBook;
  
  char s;
  
  FILE *fp = NULL;
  FILE *ft = NULL;
  
  fp = fopen("books.txt", "r");
  ft = fopen("temp.txt", "w");
  
  if(fp == NULL){
    perror("Error opening file.");
    return(-1);
  }
  
  printf("\nType the book number to be DELETED: ");
  scanf("%d", &bookNumber);
  // check if book number exists
  
  while(fgets(line, sizeof(line), fp) != NULL){
    sscanf(line, "%d", &number);
    //printf("%s\n", line);
    
    while(bookNumber > (numberGen() - 1) || bookNumber <= 0){
      printf("\nBook number not found. Type the book number to be DELETED: ");
      scanf("%d", &bookNumber);
    }
  
    // DELETE algorithm
    if(number < bookNumber){
      fprintf(ft, "%s", line);
      // There's a bug here. If you try to delete the last book it generates
      // a new line in the file and messes up the display option
    } else if(number > bookNumber && number <= (numberGen() - 1)){
      fprintf(ft, "%02d", number - 1);
      fprintf(ft, "%s", pline);
    }
    
    
  }
  
  fclose(fp);
  fclose(ft);
  
  remove("books.txt");
  rename("temp.txt", "books.txt");
  
  displayBooks();
  
  return 0;
}