#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


/*
Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be
useful?
*/

int main(int argc, char *argv[]) {

    int id = fork();

    if(id < 0) {
        fprintf(stderr, "error forking");
    }
    else if (id == 0) {
        printf("hello, (pid:%d)\n", (int) getpid());
        pid_t childpid = (int) getpid();
        printf("childpid :%d\n", childpid);
        
    }
    else {
        
        int rv = waitpid(id,NULL,0);
        printf("goodbye, (pid:%d), waitpid: %d\n", (int) getpid(), rv);
        
    }

    return 0;
}