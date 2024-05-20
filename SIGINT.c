#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

// Function to be executed by the separate thread
void *task(void *arg) {
    int i;
    for (i = 0; i < 10; i++) {
        printf("Thread: %d\n", i);
        sleep(1); // Simulate some work
    }
    return NULL;
}

// Signal handler function
void sigint_handler(int sig) {
    printf("\nSIGINT signal caught. Terminating...\n");
    exit(EXIT_SUCCESS);
}

int main() {
    pthread_t tid;
   
    // Set up the signal handler for SIGINT
    signal(SIGINT, sigint_handler);
   
    // Create a separate thread
    if (pthread_create(&tid, NULL, task, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
   
    // Main program continues executing
    int i;
    for (i = 0; i < 5; i++) {
        printf("Main: %d\n", i);
        sleep(1); // Simulate some work
    }
   
    return 0;
}