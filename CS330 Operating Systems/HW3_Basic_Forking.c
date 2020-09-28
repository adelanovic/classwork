/*
 Name: Adis Delanovic
 DogNET: delanoa
 Class: CS330 Operating Systems and Networking with Professor Spetka
 Assignment: Homework #3, basic forking (Multiprogramming and Multithreading)
 Date: 09/07/2020
 Editor:GNU Nano 2.9.3
 Compiler: GCC 7.5.0
 File Location: ~delanoa/www/CS330/HW/HW3/HW3_Basic_Forking.c
*/


#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
        //Create an array of pid_t for processs IDs, i need 26 processes
        pid_t child_process[26];

        //Number of letters to print
        int n = 26;
        int lines = 12;

        //Assign c the starting character.
        char c = 'A';

	printf("\n");

        //Main loop to control how many lines to print
        for(int j = 0; j < lines; j++)
        {
                //Create the processes  using fork() assigning the pid to pids
                for(int i = 0; i < n; i++)
                {
                        child_process[i] = fork();
                        //Checks for a successful use of fork()
                        if(child_process[i] == 0)
                        {
                                printf("%c", c);
                                return 0;
                        }
                        //Increment character
                        c++;
                }

        /*
                Wait for all child processes to end, wait(NULL) returns a -1 when there are no child processes remaining.
                If this isn't here the parent process will continue to run before the child has completed.
                The use of a loop is necessary since there are 26 child processes yA to yZ.
                Without the loop it would wait for any child process and continue with the parent process.
         */
                while(wait(NULL) != -1);

	//Reset c to 'A' and print a new line. 
		c = 'A';
		printf("\n");
        }

	printf("\n");

        return 0;

}

