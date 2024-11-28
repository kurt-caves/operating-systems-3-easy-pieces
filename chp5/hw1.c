#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int x = 100;
    printf("value of x before fork: %d, (pid:%d)\n", x, (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Error with fork\n");
    }
    else if (rc == 0) {
        printf("value of x in child: %d, (pid:%d)\n", x, (int) getpid());
        x = 200;
        // printf("changed x value in child x: %d, (pid:%d)\n", x, (int) getpid());
    }
    else {
        // wait(NULL);
        printf("value of x in parent x: %d, (pid:%d)\n", x, (int) getpid());
        x = 300;
        // printf("changed x value in parent x: %d, (pid:%d)\n", x, (int) getpid());
    }

    return 0;
}