#include <stdio.h>
#include <unistd.h>

int main(){
    int n;
    printf("enter a number: ");
    scanf("%d",&n);
    int pid = fork();
    if (pid == 0){
        n = n%2 == 0 ? n-1:n;
        printf("child: sum of odd nums: %d\n", ((n + 1) / 2) * ((n + 1) / 2));
    } else if(pid == -1)
        printf("error!.\n");
    else {
        n = n % 2 != 0 ? n - 1 : n;
        printf("parent: sum of even nums: %d\n", (n / 2) * ((n / 2) + 1));
    }
}
//
// Created by abdullah on 5/19/24.
//