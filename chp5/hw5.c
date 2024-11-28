#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


/*
Now write a program that uses wait() to wait for the child process
to finish in the parent. What does wait() return? What happens if
you use wait() in the child?
*/

int main(int argc, char *argv[]) {

    int id = fork();

    if(id < 0) {
        fprintf(stderr, "error forking");
    }
    else if (id == 0) {
        printf("hello, (pid:%d)\n", (int) getpid());
        
    }
    else {
        int w = wait(NULL);
        printf("return of wait: %d\n", w);
        printf("goodbye, (pid:%d)\n", (int) getpid());
        
    }

    return 0;
}