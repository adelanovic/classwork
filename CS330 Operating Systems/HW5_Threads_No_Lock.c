/*
 Name: Adis Delanovic
 DogNET: delanoa
 Class: CS330 Operating Systems and Networking with Professor Spetka
 Assignment: Homework #5, Threads
 Date: 09/25/2020
 Editor:GNU Nano 2.9.3
 Compiler: GCC 7.5.0
 File Location: ~delanoa/www/CS330/HW/HW5/HW5_Threads_No_Lock.c
 Description: This program takes userinput of what character to search for, number of threads (limited to 4)
        and what file to search. The output is then displayed showing the occurances of the character. Conditional statements
  are used to make sure threads aren't updating the same memory location and creating a race condition.
*/

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


//Defined structure to keep data together
typedef struct search{
    	int threadnum[4];
    	int numthreads;
    	int index;
    	char userinput;
    	char c[440000];
	int occurs[4];
}Search;


//Global variable for access by threads
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
  	pthread_t threads[search.numthreads];

    	printf("-- Enter the character you want to find occurances for: ");
  	scanf(" %c", &search.userinput);
    	fflush(stdout);

    	printf("-- Enter the filename: ");
    	scanf(" %s", filename);
    	fflush(stdout);

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
  	fclose(file);

  	startTimer(&start);
  	for(int i = 0; i < search.numthreads; i++)
  	{
    		int *args = malloc(sizeof(int));
    		args[i] = i;
    		printf("-- Creating thread %d\n", i+1);
    		//Creates the thread, uses the allocated int index temporarily for storage and frees it after. Casts the args int as a void since the 4th argument of pthread_create requires a void value. 
    		if(pthread_create(&threads[i], NULL, findchars, (void*)&args[i]))
      			free(args);
  	}

	//Join all the threads back together. 
  	for(int i = 0; i < search.numthreads; i++)
 	{
    		pthread_join(threads[i], NULL);
  	}

  	endTimer(&end);
  	printResults(&start, &end);

  	//Add up all the ocurrances and display them. 
  	printf("-- The occurance of character '%c' is: %d\n\n", search.userinput, search.occurs[0] + search.occurs[1] + search.occurs[2] + search.occurs[3]);
    	return 0;
}

void *findchars(void *charsnfiles)
{
	int index = *(int*)charsnfiles;
       	printf("-- Entering thread number: %d\n", index+1);
  	int currentIndex = index;

  	//To achieve thread efficiency and ensure there is no race condition towards one certain memory allocation.
  	//Each of these if statements represent a thread number. Each thread works on its own memory location for number of occurances
 	//therefore bypassing the necessity for synchronization using mutex lock only one memory location.
  	if(index+1 == 1)
    	{
      		for(int i = 0; i < sizeof(search.c)/search.numthreads; i++)
        	{
          		if(toupper(search.c[currentIndex]) == toupper(search.userinput))
        		{
           	 		search.occurs[0]++;
        		}

	        	currentIndex+= search.numthreads;
      		}
    	}
  	else if(index+1 == 2)
        {
               	for(int i = 0; i < sizeof(search.c)/search.numthreads; i++)
                {
                      	if(toupper(search.c[currentIndex]) == toupper(search.userinput))
        		{
                                  search.occurs[1]++;
   			}

        		currentIndex+= search.numthreads;
      		}
        }
  	else if(index+1 == 3)
                {
                for(int i = 0; i < sizeof(search.c)/search.numthreads; i++)
                {
                         if(toupper(search.c[currentIndex]) == toupper(search.userinput))
        		{
                                  search.occurs[2]++;
        		}
     			 currentIndex+= search.numthreads;

                        }
                }
  	else  if(index+1 == 4)
        {
                for(int i = 0; i < sizeof(search.c)/search.numthreads; i++)
                        {
                          if(toupper(search.c[currentIndex]) == toupper(search.userinput))
        		  {
                                 search.occurs[3]++;
        		  }
        		currentIndex+= search.numthreads;
                        }
                }

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


