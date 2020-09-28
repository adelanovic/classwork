/*
 Name: Adis Delanovic
 DogNET: delanoa
 Class: CS330 Operating Systems and Networking with Professor Spetka
 Assignment: Homework #5, Threads
 Date: 09/25/2020
 Editor:GNU Nano 2.9.3
 Compiler: GCC 7.5.0
 File Location: ~delanoa/www/CS330/HW/HW5/HW5_Threads.c
 Description: This program takes userinput of what character to search for, number of threads (limited to 4)
  and what file to search. The output is then displaying showing the occurances of the character. mutex lock
  is used to ensure synchronization between the threads. Professor Spetka uses a similar approach on how to iterate data usig multiple threads. For each thread created the currentIndex is currentIndex + number of threads.
*/


#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

//Defined structure to encapsulate some data
typedef struct search{
  int threadnum[4];
  int numthreads;
  int index;
  char userinput;
  char c[440000];
  int occurs;
}Search;

//Global variables declared for access by threads
pthread_mutex_t lock;
Search search;

//Function Prototypes
void startTimer(struct timeval *start);
void endTimer(struct timeval *end);
void printResults(struct timeval *start, struct timeval *end);
void *findchars(void *charsnfiles);

int main(void)
{
    char filename[20];
    struct timeval start, end;

    printf("\n-- Enter number of threads to use: ");
    scanf(" %d", &search.numthreads);

    //Variable declared of type thread, thread is an array of number of threads user entered.
    pthread_t threads[search.numthreads];

    printf("-- Enter the character you want to find occurances for: ");
    scanf(" %c", &search.userinput);
    fflush(stdout);

    printf("-- Enter the filename: ");
    scanf(" %s", filename);
    fflush(stdout);

    //Open the file and place it into character array.
    FILE *file = fopen(filename, "r");

    if(file == NULL)
    {
        printf("-- File failed to open.\n");
        return 0;
    }
    else
    {
        printf("-- File opened successfully.\n");
        for(int i = 0; i < sizeof(search.c);i++)
        {
            search.c[i] = fgetc(file);

        }
    }

    //Close the file
    fclose(file);

    startTimer(&start);
    for(int i = 0; i < search.numthreads; i++)
    {
      int *args = malloc(sizeof(int));
      args[i] = i;
      printf("-- Creating thread %d\n", i+1);
      //Creates the thread, uses the allocated int index temporarily for storage and frees it after.
      if(pthread_create(&threads[i], NULL, findchars, (void*)&args[i]))
      	free(args);
    }

    //Join all the threads together.
    for(int i = 0; i < search.numthreads; i++)
    {
    	pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);

    endTimer(&end);
    printResults(&start, &end);

    printf("-- The occurance of character '%c' is: %d\n\n", search.userinput, search.occurs);
    return 0;
}


//Description: Using 1-4 threads find the occurances of a specific character in a given file.
//Pre-condition: A "Search" structure is passed that contains the contents of the file and other information.
//Post-condition: Occurances of a specific character are stored in search.occurs
void *findchars(void *charsnfiles)
{
  int occuredInThread = 0;

  //Cast the void argument as an integer
  int index = *(int*)charsnfiles;
        printf("-- Entering thread number: %d\n", index+1);
  int currentIndex = index;

  //The for loop is divided based on number of threads.
  for(int i = 0; i < sizeof(search.c)/search.numthreads; i++)
  {
    if(toupper(search.c[currentIndex]) == toupper(search.userinput))
    {
      occuredInThread++;
    }
    currentIndex += search.numthreads;
  }

  //Lock the data that all threads have access to, unlock it after.
  pthread_mutex_lock(&lock);
  search.occurs += occuredInThread;
  pthread_mutex_unlock(&lock);

  //Properly exit the thread.
  pthread_exit(0);
}

//Function definitions
//Description: Gets the current
//Pre-condition: start is a timeval struct
//Post-condition: start now has a value for seconds and microseconds in start.tv_sec and start.tv_usec
void startTimer(struct timeval *start)
{
    gettimeofday(start, NULL);
}

//Description: Gets the current time of day
//Pre-condition: end is a timeval struct
//Post-Condition: end now has a value for seconds and microseconds in end.tv_ec and end.tv_usec
void endTimer(struct timeval *end)
{
    gettimeofday(end, NULL);

}


//Description: Displays the total microseconds, and seconds
//Pre-condition: start and end both have gotten accurate values from gettimeofday() function
//Post-condition: The correct elapsed time is displayed measuring how long our loopdyLoop() function took.
//      does not necessarily mean total execution time since it doesn't take into account the printResults() function
//      or returning control to the system.
void printResults(struct timeval *start, struct timeval *end)
{
  //Gets total microseconds, either dereference a struct with (*var). or -> notation.
    int totalMicro = (((*end).tv_sec * 1000000) + (*end).tv_usec) - (((*start).tv_sec * 1000000) + (*start).tv_usec);

    //Converts microseconds to seconds
    int totalSeconds = totalMicro/1000000;

    //Remainder as microseconds
    int remainMicros = totalMicro%1000000;

    printf("\n################################################################################\n\n");
    printf("  Timer #1: %d microseconds", totalMicro);
    printf("\n  Timer #2: %d seconds and %d microseconds\n", totalSeconds, remainMicros);
    printf("\n################################################################################\n\n");
}

