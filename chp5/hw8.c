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
    pipe(fd); // create pipe

    // we are writing in this part
    if (fork() == 0) {
        close(fd[0]); // close unused read
        int x = 42;
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
        return 0;
    }
    // we are reading in this part
    if (fork() == 0) {
        close(fd[1]); // close unused write
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("Got from child process y: %d\n", y);
        return 0;
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);

    


    return 0;
}