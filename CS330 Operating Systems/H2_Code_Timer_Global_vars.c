/*
   Name: Adis Delanovic
   DogNET: delanoa
   Class: CS330 Operating Systems and Networking with Professor Spetka
   Assignment: Homework #2, use gettimeofday() to find elapsed time and time code execution
	       Must have a startTimer(), endTimer() and printResults() functions
   Date: 08/27/2020
   Editor: GNU nano 2.9.3
   File Location: ~delanoa/www/CS330/HW/HW2/H2_Code_Timer_Global_vars.c
*/

#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

//Function Prototypes
void startTimer();
void loopdyLoop();
void endTimer();
void printResults();

//Global variable for the timeval struct
struct timeval start, end;

int main(void)
{

//Function calls
	startTimer();

	loopdyLoop();

	endTimer();

	printResults();

	return 0;
}

//Function definitions

//Description: Gets the current
//Pre-condition: start is a timeval struct
//Post-condition: start now has a value for seconds and microseconds in start.tv_sec and start.tv_usec
void startTimer()
{
	gettimeofday(&start, NULL);
}

//Description: Gets the current time of day
//Pre-condition: end is a timeval struct
//Post-Condition: end now has a value for seconds and microseconds in end.tv_ec and end.tv_usec
void endTimer()
{
	gettimeofday(&end, NULL);

}

//Description: A loop that is just made to take computation time and does nothing in particular
//Pre-condition: i and j initialized to 0
//Post-condition: total gets i and j added to it. total and i are displayed, the function returns nothing
//		  variables local to the function are all discarded.
void loopdyLoop()
{
	int i = 0;
	int j = 0;
	long int total = 0;

	for(i = 0; i < 1000000000; i++)
	{
		for(j = 0; j < i * 3; j += i)
		{
			total += (i+j) ;
		}
	}
	printf("Value of [i] is %d, and value of [total] is %ld\n", i, total);
	printf("Now leaving useless function, [total] and [i] both discarded\n");
}

//Description: Displays the total microseconds, and seconds
//Pre-condition: start and end both have gotten accurate values from gettimeofday() function
//Post-condition: The correct elapsed time is displayed measuring how long our loopdyLoop() function took.
//		  does not necessarily mean total execution time since it doesn't take into account the printResults() function
//		  or returning control to the system.
void printResults()
{

	//Gets total microseconds
        int totalMicro = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);

	//Converts microseconds to seconds
	int totalSeconds = totalMicro/1000000;

	//Remainder as microseconds
	int remainMicros = totalMicro%1000000;

	printf("%d microseconds", totalMicro);
	printf("\n%d seconds and %d microseconds\n", totalSeconds, remainMicros);
}
