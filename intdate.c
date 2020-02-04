////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c sendsig.c division.c
// This File:        intdate.c
// Other Files:      sendsig.c division.c
// Semester:         CS 354 Spring 2019
//
// Author:           Shihan Cheng
// Email:            scheng93@wisc.edu
// CS Login:         shihan

/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          NA
//
// Online sources:   NA
//
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int alarm_timer = 3;  // Alarm will go off 3 seconds later
int count_sigusr1 = 0;  // Counter to of SIGUSR1 caught

/* This function sets an alarm clock for delivery of a signal, should print
 * the pid (process id) of the program and the current time (in the same
 * format as the Linux date command).
 */
void handler_SIGALRM() {
    time_t currtime;
    if (time(&currtime) == -1) {  // Make sure current time is valid
        printf("Error current time.\n");
        exit(0);
    }
    // Print process ID and current time
    printf("PID: %d", getpid());
    printf(" | Current time: %s", ctime(&currtime));
    if (alarm(alarm_timer) != 0) {  // Check alarm timer
        printf("Alarm has an error.\n");
        exit(0);
    }
    alarm(alarm_timer);  // Reset the alarm as 3 seconds
}

/* This function is to catch SIGUSR1 and print the information of SIGUSR1
 * caught.Increases the sigusr1 counter once it is caught
 */
void handler_SIGUSR1() {
    printf("SIGUSR1 caught!\n");
    count_sigusr1++;  // Increase counter when sigusr1 is caught
}

/* This function will catch the interrupt signal when user typing Control+c
 * or using sendsig to send an interrupt signal to the running program
 */
void  handler_SIGINT() {
    // Print the time of signal received
    printf("\nSIGINT received.\n");
    printf("SIGUSR1 was received %i times. Exiting now.\n", count_sigusr1);
    exit(0);
}

/*
 * The main for this program will run on an infinite loop while
 * an alarm continuously goes off every 3 seconds. The program
 * is set to handle signals for the alarm as well as SIGUSR1 and
 * SIGINT. The program will respond to the different signals in
 * various ways.
 * argc:the number of arguments
 * argv: use the char pointer to store each arguments
 */
int main(int argc, char *argv[]) {
    printf("Pid and time will be printed every 3 seconds.\n");
    printf("Enter ^C to end the program.\n");
    // Signal handler for SIGALARM
    struct sigaction sigalrm;
    memset (&sigalrm, 0, sizeof(sigalrm));
    sigalrm.sa_handler = handler_SIGALRM;
    if (sigaction(SIGALRM, &sigalrm, NULL) < 0) {
        printf("Error handling for SIGALARM");
        exit(0);
    }
    if (alarm(alarm_timer) != 0) {  // Check the global alarm timer
        printf("Alarm error.\n");
        exit(0);
    }
    // Signal handler for SIGUSR1
    struct sigaction sigusr1;
    memset (&sigusr1, 0, sizeof(sigusr1));
    sigusr1.sa_handler = handler_SIGUSR1;
    if (sigaction(SIGUSR1, &sigusr1, NULL) < 0) {
        printf("Error handling for SIGUSR1");
        exit(0);
    }
    // Signal handler for SIGINT
    struct sigaction sigint;
    memset(&sigint, 0, sizeof(sigint));
    sigint.sa_handler = handler_SIGINT;
    if (sigaction(SIGINT, &sigint, NULL) < 0) {
        printf("Error handling for SIGINT");
        exit(0);
    }
    // Infinite loop
    while (1) {
    }
    return (0);
}

