#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*
Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the
pipe() system call.
*/

int main(void) {

    int fd[2]; // store return descriptors
    // fd[0] = read
    // fd[1] = write
    if (pipe(fd) < 0) {
        fprintf(stderr, "error with pipe\n");
        return 1;
    }
    int id1 = fork();
    if (id1 == 0) {
        close(fd[0]);
        int x;
        printf("enter a number: ");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    } 
    else {
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("from child process y: %d\n", y);
    }

    


    return 0;
}