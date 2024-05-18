//
// Created by abdullah on 5/18/24.
//
#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Enter a number: ");
    int n;
    scanf("%d",&n);
    getchar();//for the newline in the buffer.
    int sum;

    int pid = fork();
    switch (pid) {
        case 0:
            if (n % 2 == 0) {
                n = n - 1;
            }

            sum = ((n + 1) / 2) * ((n + 1) / 2);

            printf("you are in the child:\nsum of odd nums: %d\n\n",sum);
            break;
        case -1:
            perror("fork");
        default:
            if (n % 2 != 0) {
                n = n - 1;
            }

            sum = (n / 2) * ((n / 2) + 1);
            printf("you are in the parent:\nsum of even nums: %d\n\n",sum);
    }

    return 0;
}