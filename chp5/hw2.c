#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/*
Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?
*/

int main(int argc, char *argv[]) {

    int rv = open("./hw2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    }
    else if (rc == 0) {
        char msg1[] = "from child\n";
        write(rv,msg1,11);
    }
    else {
        char msg2[] = "from parent\n";
        write(rv,msg2,12 );
    }
   

    return 0;

}