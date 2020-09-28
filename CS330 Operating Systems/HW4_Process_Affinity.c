/*
 Name: Adis Delanovic
 DogNET: delanoa
 Date: 09/12/2020
 Class: CS330 Operating Systems and Networking, Professor Spetka, Fall 2020 MW2-4pm.
 Assignment: Homework #4 Process Affinity.
 Editor: GNU Nano 2.9.3
 Compiler: GCC 7.5.0
 File Location: ~delanoa/www/CS330/HW/HW4/HW4_Process_Affinity.c
*/


#define _GNU_SOURCE
#include <sched.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

//Function Prototypes
//Timer
void startTimer(struct timeval *start);
void endTimer(struct timeval *end);
void printResults(struct timeval *start, struct timeval *end);

//CPU set up
void setCPU(cpu_set_t *mask);
void checkSet(cpu_set_t *mask);
void printCPUcount(cpu_set_t *mask);

//Testing
void runTest(void);

struct timeval startOne, endOne, startTwo, endTwo;

int main(void)
{
	//Conducts the tests, displays results
	runTest();
	return 0;
}

//Function definitions
//Description: Gets the current time.
//Pre-condition: start is a timeval struct
//Post-condition: start now has a value for seconds and microseconds in start.tv_sec and start.tv_usec
void startTimer(struct timeval *start)
{
	//Start is already a pointer and therefore don't include &
	gettimeofday(start,NULL);
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
//Post-condition: The correct elapsed time is displayed measuring how long our runTest() function took.
//		  does not necessarily mean total execution time since it doesn't take into account the printResults() function
//		  or returning control to the system.
void printResults(struct timeval *start, struct timeval *end)
{
	//Gets total microseconds, either dereference a struct with (*var). or -> notation.
        int totalMicro = (((*end).tv_sec * 1000000) + (*end).tv_usec) - (((*start).tv_sec * 1000000) + (*start).tv_usec);

	//Converts microseconds to seconds
	int totalSeconds = totalMicro/1000000;

	//Remainder as microseconds
	int remainMicros = totalMicro%1000000;
	printf("	Timer #1: %d microseconds", totalMicro);
	printf("\n	Timer #2: %d seconds and %d microseconds\n", totalSeconds, remainMicros);
	printf("\n###################################################\n\n");
	return;

}

//Description: Creates a child process and the child process creates more processes and runs on a single CPU.
//	       The parent CPU waits for the child and children of the first fork() and its the same program on
//	       multiple CPUs.
void runTest(void)
{
	cpu_set_t mask;

	pid_t onecpu = fork();

	//Child process (one CPU)
	if(onecpu == 0)
	{
		setCPU(&mask);

		if(sched_setaffinity(0, sizeof(cpu_set_t),&mask) == -1)
		{
			printf("Affinity Error\n");
		}

		printf("|--------------------------------------------------|\n");

		printCPUcount(&mask);

		checkSet(&mask);

		printf("|--------------------------------------------------|\n");
		printf("Entering Test Function #1 (Single CPU, two Processes). PID: %d, PPID: %d\n", getpid(), getppid());

		startTimer(&startOne);

		int total = 0;

		for(int k = 0; k < 2; k++)
		{

			pid_t forkit = fork();
			if(forkit == 0)
			{

				for(int i = 0; i < 1000000000; i++)
				{
					total += i;
				}

				return;
			}
			else if(forkit > 0)
			{
				while(wait(NULL) != -1);
			}
			else
			{
				printf("Fork Error\n");
			}

		}

		endTimer(&endOne);
		printf("Leaving Test Function #1 and displaying results. PID: %d, PPID: %d\n", getpid(), getppid());
		printResults(&startOne, &endOne);
	}

	//Parent process (no restrictions)
	else if( onecpu > 0)
	{
		while(wait(NULL) != -1);

		printf("Entering Test Function #2 (No restrictions on CPU, two Processes. PID: %d.\n", getpid());

		startTimer(&startTwo);

		int total = 0;

		for(int k =0; k< 2; k++)
		{
			pid_t forkit = fork();
			if(forkit == 0)
			{

				for(int i = 0; i < 1000000000; i++)
				{
					total+= i;
				}
				return;
			}
			else if(forkit > 0)
			{
				while(wait(NULL) != -1);
			}
			else
			{
				printf("Fork Error\n");
			}

		}

		endTimer(&endTwo);
		printf("Leaving Test Function #2 and displaying results.PID: %d, PPID: %d\n", getpid(), getppid());
		printResults(&startTwo, &endTwo);
	}
	else
	{
		printf("Program Error\n");
	}
}

//Description: Makes the mask cpu set zero (holds no values) then adds CPU to a set
//Pre-condition: mask is of type cpu_set_t
//Post-condition: mask has one cpu in it.
void setCPU(cpu_set_t *mask)
{
	CPU_ZERO(mask);
	CPU_SET(0, mask);

	return;
}


//Description: Prints total CPU count in system and also total CPUs in set being used.
//Pre-condition: mask is a valid cpu_set_t variable.
//Post-condition: Display results of _SC_NPROCESSORS_ONLN (processors online) and CPU_COUNT returns the set of
//		  CPU's in mask.
void printCPUcount(cpu_set_t *mask)
{
	long nprocs = sysconf(_SC_NPROCESSORS_ONLN);

	printf("         Total Number of CPUs in set: %d.\n", CPU_COUNT(mask));
	printf("         Total Number of CPUs online: %ld.\n", nprocs);
	return;
}


//Description: Checks to see if a CPU is part of a set.
//Pre-condition: mask  is a valid cpu_set_t variable.
//Post-condition: CPU_ISSET returns a boolean value
void checkSet(cpu_set_t *mask)
{
	if(CPU_ISSET(0, mask))
        {
                printf("       	 CPU is part of set.\n");
        }
        else
        {
                printf("        CPU is not part of set.\n");
        }

        return;
}
