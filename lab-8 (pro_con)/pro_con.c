//
// Created by abdullah on 5/19/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 20

sem_t sem_full, sem_empty, mutex;
int BUFFER[BUFFER_SIZE];
int CUR_INDEX = 0;

void * producer(void * args){
    int iteration = 0;
    while(iteration < 10){
        int value = rand()%100;
        sem_wait(&sem_empty);
        sem_wait(&mutex);
        BUFFER[CUR_INDEX++] = value;
        sem_post(&sem_full);
        sem_post(&mutex);
        printf("produced value: %d\n", value);
        usleep(1000);
        iteration++;
    }
    return NULL;
}

void * consumer(void * args) {
    int iteration = 0;
    while(iteration < 10){
        usleep(1000);
        sem_wait(&sem_full);
        sem_wait(&mutex);
        int consumed_val = BUFFER[--CUR_INDEX];
        sem_post(&sem_empty);
        sem_post(&mutex);
        printf("consumed value: %d\n", consumed_val);
        usleep(500);
        iteration++;
    }
    return NULL;
}

int main(){
    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&sem_empty, 0, BUFFER_SIZE);
    sem_init(&sem_full, 0, 0);

    pthread_t thread_pro;
    pthread_t thread_con;

    pthread_create(&thread_pro, NULL, producer, NULL);
    pthread_create(&thread_con, NULL, consumer, NULL);

    pthread_join(thread_pro, NULL);
    pthread_join(thread_con, NULL);

    return 0;
}