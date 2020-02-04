////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c sendsig.c division.c
// This File:        division.c
// Other Files:      intdate.c sendsig.c
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

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int div_count;  // Counter of the number of successful division

/*
 * This handler function catches all SIGFPE signals. When it receives
 * a SIGFPE signal, gives an error message . Otherwise provides a final
 * number of successful messages.
 */
void handler_SIGFPE() {
    // Error message
    printf("Error: a division by 0 operation was attemped.\n");
    // Final result
    printf("Total number of operations completed successfully: %i\n",
           div_count);
    printf("The program will be terminated.\n");
    exit(0);
}

/*
 * This handler fuction catches all SIGINT signals. When it receives
 * a SIGINT signal, provides a final number of successful messages.
 */
void handler_SIGINT() {
    // Final result
    printf("\nTotal number of operations successfully completed: %i\n",
           div_count);
    printf("The program will be terminated.\n");
    exit(0);
}

/*
 * This program will run an infinite loop that will continally ask the user
 * to enter two inputs to divide. The program will output the quotient and
 * the remainder for each division and the number of successful divisions
 * will be recorded. The program can only end when there is a divide by 0
 * (SIGFPE) or a SIGINT signal sent. When either signal is received an output
 * message will display showing total number of successful divisions and program
 * will cleanly exit.
 */
int main() {
    div_count = 0;  // Reset the counter
    // Signal handler for SIGFPE
    struct sigaction sigfpe;
    memset (&sigfpe, 0, sizeof(sigfpe));
    sigfpe.sa_handler = handler_SIGFPE;
    if (sigaction(SIGFPE, &sigfpe, NULL) < 0) {
        printf("Error handling for SIGFPE.\n");
        exit(0);
    }
    // Signal handler for SIGINT
    struct sigaction sigint;
    memset(&sigint, 0, sizeof(sigint));
    sigint.sa_handler = handler_SIGINT;
    if (sigaction(SIGINT, &sigint, NULL) < 0) {
        printf("Error handling for SIGINT.\n");
        exit(0);
    }
    while (1) {  // The division process
        char buffer[100];
        printf("Enter first integer: ");
        fgets(buffer, 100, stdin);
        int first_num = atoi(buffer);  // First nummber
        printf("Enter second integer: ");
        fgets(buffer, 100, stdin);
        int second_num = atoi(buffer);  // Second number
        int result = first_num / second_num;  // Result
        int remainder = first_num % second_num;  // Reminder
        printf("%i / %i is %i with a remainder of %i\n",
               first_num, second_num, result, remainder);
        div_count++;  // Increase the counter
    }
    return (0);
}

