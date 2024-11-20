/**
 * File: send_signal.c
 * Modified by:
 * Chance Mason, Signals, CPE-2600 121
 * Brief summary of program:
 * Sends a SIGUSR1 signal with 
 * a random value to a specified process
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = atoi(argv[1]);

    // Seed the random number generator
    srand(time(NULL));

    // Generate a random integer
    int random_value = rand();

    // Print the random number
    printf("Sending SIGUSR1 with random value: %d to process %d\n", random_value, pid);

    // Prepare the sigval structure
    union sigval sig_value;
    sig_value.sival_int = random_value;

    // Send the SIGUSR1 signal with the random value
    if (sigqueue(pid, SIGUSR1, sig_value) == -1) {
        perror("sigqueue");
        exit(EXIT_FAILURE);
    }

    return 0;
}