////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      intdate.c division.c
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

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
 * This main fuction takes command arguments
 * and anylizes that if it is a kill command that either
 * a SIGUSR1 (-u) signal or a SIGINT (-i).
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {  // Check the length of the command first
        printf("Usage: <signal type> <pid>\n");
        exit(0);
    }
    // Get the process ID from the command
    pid_t pid = atoi(argv[2]);
    // Compare the second command with the specific signal types
    int cmp_sigusr1 = strcmp(argv[1], "-u");
    int cmp_sigint = strcmp(argv[1], "-i");
    if (cmp_sigusr1 == 0) {  // When the type is -u
        if (kill(pid, SIGUSR1) == -1) {
            printf("Error signal for SIGUSR1.\n");
            exit(0);
        }
    } else if (cmp_sigint == 0) {  // When the type is -i
        if (kill(pid, SIGINT) ==-1) {
            printf("Error signal for SIGINT.\n");
            exit(0);
        }
    } else {  // Otherwise the type is incorrect
        printf("Wrong SIGNAL TYPE.\n");
        exit(0);
    }
    return 0;
}

