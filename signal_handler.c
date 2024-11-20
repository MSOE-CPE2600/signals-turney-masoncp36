/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by:
 * Chance Mason, Signals, CPE-2600 121
 * Brief summary of modifications:
 * Using the signal handler method when receiving a signal the program kills and exits.
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGINT - prints a message and sends SIGKILL to itself
 */
void handle_signal() {
    printf("Received a signal\n");
    kill(getpid(), SIGKILL); // Send SIGKILL to the current process
}

int main() {

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}