/**
 * File: recv_signal.c
 * Modified by:
 * Chance Mason, Signals, CPE-2600 121
 * Brief summary of program:
 * Waits to receive a SIGUSR1 signal with
 * a random value
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGUSR1 - prints the sival_int value
 */
void handle_sigusr1(int sig, siginfo_t *siginfo, void *context) {
    printf("Received SIGUSR1 with sival_int: %d\n", siginfo->si_value.sival_int);
}

int main() {
    struct sigaction sa;
    pid_t pid = getpid();

    printf("recv_signal pid: %d\n", pid);

    // Initialize the sigaction structure
    sa.sa_sigaction = handle_sigusr1;
    sa.sa_flags = SA_SIGINFO; // Use sa_sigaction field, not sa_handler
    sigemptyset(&sa.sa_mask);

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Wait in an infinite loop
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

/*
 * To send SIGUSR1 to this process with a specific sival_int value, use the following command:
 * kill -SIGUSR1 <pid>
 * Replace <pid> with the process ID of the running program.
 */