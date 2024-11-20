/**
 * File: signal_alarm.c
 * Modified by:
 * Chance Mason, Signals, CPE-2600 121
 * Brief summary of program:
 * This program handles an alarm signal and schedules 
 * for it to be sent after 5 seconds then exits when it is received
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGALRM - prints a message
 */
void handle_alarm(int sig) {
    printf("Received SIGALRM signal\n");
    exit(1);
}

int main() {
    // Register the signal handler for SIGALRM
    signal(SIGALRM, handle_alarm);

    // Schedule an alarm to be sent after 5 seconds
    alarm(5);

    // Wait until a signal is received
    while(1) {
        printf("Waiting for the alarm...\n");
        sleep(1);
    }

    return 0;
}