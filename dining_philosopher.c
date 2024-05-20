#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5  // Number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
int philosophers[N] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[N];

void test(int phil) {
    if (state[phil] == HUNGRY && state[(phil + 4) % N] != EATING && state[(phil + 1) % N] != EATING) {
        // state that eating
        state[phil] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", phil + 1, (phil + 4) % N + 1, phil + 1);
        printf("Philosopher %d is Eating\n", phil + 1);
        // sem_post the semaphore to signal philosopher to start eating
        sem_post(&S[phil]);
    }
}

// take up chopsticks
void take_fork(int phil) {
    sem_wait(&mutex);
    // state that hungry
    state[phil] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phil + 1);
    // eat if neighbours are not eating
    test(phil);
    sem_post(&mutex);
    // if unable to eat wait to be signalled
    sem_wait(&S[phil]);
    sleep(1);
}

// put down chopsticks
void put_fork(int phil) {
    sem_wait(&mutex);
    // state that thinking
    state[phil] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", phil + 1, (phil + 4) % N + 1, phil + 1);
    printf("Philosopher %d is thinking\n", phil + 1);
    test((phil + 4) % N);
    test((phil + 1) % N);
    sem_post(&mutex);
}

void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];
    // initialize the semaphores
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);
    for (i = 0; i < N; i++) {
        // create philosopher processes
        pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
    return 0;
}
