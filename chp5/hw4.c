#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/*
Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including execl(), execle(), execlp(),
execv(), execvp(), and execvP(). Why do you think there
are so many variants of the same basic call?
*/

int main(void) {

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    }
    else if (rc == 0) {
        char *myargs[2];
        myargs[0] = strdup("/bin/ls");
        myargs[1] = NULL;
        // execvp(myargs[0],myargs);
        execl(myargs[0],myargs,NULL);
    }
    else {
        wait(NULL);
    }

    return 0;
}