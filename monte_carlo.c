#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUM 3
int square_points = 0, circle_points = 0;


void *runner(void * args){
    int iter = * (int *) args;
    for(int i = 0; i < iter*iter; i++){
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        double d = x * x + y * y;
        if (d <= 1)
            circle_points++;
        square_points++;
    }
}


int main(){
    srand(time(NULL));
    pthread_t threads[THREAD_NUM];
    int iterations;
    printf("enter the num of iterations(>10): ");
    scanf("%d", &iterations);
    iterations /= THREAD_NUM;
    for(int i = 0; i < THREAD_NUM; i++)
        pthread_create(& threads[i], NULL, runner, & iterations);
    for(int i = 0; i < THREAD_NUM; i++)
        pthread_join(threads[i], NULL);
    double pi = 4 * (double)circle_points / square_points;
    printf("after %d number of iterations pi's value is : %f\n", iterations, pi);
}