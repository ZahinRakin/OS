#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

int BUFFER[10];
int count = 0;

sem_t sem_empty;
sem_t sem_full;
sem_t buff_lock;

void * producer(void *args){
    while(true){
        int val = rand() % 100;
        sem_wait(& sem_empty);
        sem_wait(& buff_lock);
        printf("pro: %d\n",val);
        BUFFER[count++] = val;
        sem_post(& buff_lock);
        sem_post(& sem_full);
    }
    return NULL;
}

void * consumer(void *args){
    while(true){
        sleep(.1);
        sem_wait(& sem_full);
        sem_wait(& buff_lock);
        int val = BUFFER[--count];
        printf("con: %d\n",val);
        sem_post(& buff_lock);
        sem_post(& sem_empty);
    }

}

int main(){
    srand(time(NULL));
    pthread_t pro_thread;
    pthread_t con_thread;
    sem_init(& sem_empty, 0, 10);
    sem_init(& sem_full, 0, 0);
    sem_init(& buff_lock, 0, 1);
    pthread_create(& pro_thread, NULL, producer, NULL);
    pthread_create(& con_thread, NULL, consumer, NULL);
    pthread_join(pro_thread, NULL);
    pthread_join(con_thread, NULL);
    sem_destroy(& sem_empty);
    sem_destroy(& sem_full);
    sem_destroy(& buff_lock);
    return 0;
}