/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by:
 * Chance Mason, Signals, CPE-2600 121
 * Brief summary of modifications:
 * program now receives the segmentation violation
 * signal and returns to where it left off
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGSEGV - prints a message
 */
void handle_signal(int sig) {
    printf("Received a segmentation fault signal\n");
}

int main(int argc, char* argv[]) {
    // Register the signal handler for SIGSEGV
    signal(SIGSEGV, handle_signal);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer to trigger a segmentation fault
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}