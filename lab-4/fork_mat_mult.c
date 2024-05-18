//
// Created by abdullah on 5/18/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int a[2][3] = {
            {1, 2, 3},
            {4, 5, 6}
    };

    int b[3][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
    };

    int c[2][4];
    int i, j;
    int m;
    int n;
    int pid;

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    for (i = 0; i < 2; i++) {
        pid = fork();
        if (pid == -1) {
            perror("Can't fork");
            exit(1);
        }

        if (pid == 0)
        {
            close(pipefd[0]);

            for (j = 0; j < 4; j++) {
                m = 0;
                for (n = 0; n < 3; n++) {
                    m = m + a[i][n] * b[n][j];
                }
                c[i][j] = m;

                write(pipefd[1], &c[i][j], sizeof(c[i][j]));
            }

            close(pipefd[1]);
            exit(0);
        }
    }

    close(pipefd[1]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            read(pipefd[0], &c[i][j], sizeof(c[i][j]));
        }
    }

    close(pipefd[0]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < 2; i++) {
        wait(NULL);
    }

    return 0;
}
