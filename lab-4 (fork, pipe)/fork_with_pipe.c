#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pipe(pipefd);
    int pid = fork();
    if (pid == 0) {
        close(pipefd[0]);
        char str[100];
        printf("enter something: ");
        fgets(str, sizeof(str), stdin);
        write(pipefd[1], str, strlen(str)+1); // Write the null-terminated string
        close(pipefd[1]);
    } else if (pid == -1) {
        perror("something went south!\n");
    } else {
        close(pipefd[1]);
        char str[100];
        read(pipefd[0], str, 10); // Read sizeof(str) bytes from the pipe
        printf("%s\n", str);
        close(pipefd[0]);
    }
    return 0;
}
