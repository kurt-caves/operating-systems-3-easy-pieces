#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/*Write another program using fork(). The child process should
print “hello”; the parent process should print “goodbye”. You should
try to ensure that the child process always prints first; can you do
this without calling wait() in the parent?*/

int main(int argc, char *argv[]) {

    int id = fork();

    if(id < 0) {
        fprintf(stderr, "error forking");
    }
    else if (id == 0) {
        printf("hello\n");
    }
    else {
        wait(NULL);
        printf("goodbye\n");
    }

    return 0;
}