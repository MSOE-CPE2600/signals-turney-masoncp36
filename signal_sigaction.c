/**
 * File: signal_sigaction.c
 * Modified by:
 * Chance Mason, Signals, CPE-2600 121
 * Brief summary of program:
 * Waits for a user signal and waits
 * prints the process identifier of the sender
 * then returns
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGUSR1 - prints the sender's PID
 */
void handle_sigusr1(int sig, siginfo_t *siginfo, void *context) {
    printf("Received SIGUSR1 from process %d\n", siginfo->si_pid);
}

int main() {
    //inintialize
    struct sigaction sa;
    pid_t pid;

    //initialize the sigaction structure
    sa.sa_sigaction = handle_sigusr1;
    sa.sa_flags = SA_SIGINFO; //use sa_sigaction field, not sa_handler
    sigemptyset(&sa.sa_mask);

    //register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    //fork the process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        //child process
        sleep(1); //ensure the parent is ready to receive the signal
        kill(getppid(), SIGUSR1); //send SIGUSR1 to the parent process
        printf("Child process sent SIGUSR1 to parent process\n");
    } else {
        //parent process
        printf("Parent process waiting for SIGUSR1...\n");
    }

    //both parent and child wait in an infinite loop
    while (1) {
        pause(); //wait for signals
    }

    return 0;
}

/*
 * To send SIGUSR1 to this process manually, use the following command:
 * kill -SIGUSR1 <pid>
 * Replace <pid> with the process ID of the running program.
 */