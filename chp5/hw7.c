#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*
Write a program that creates a child process, and then in the child
closes standard output (STDOUT FILENO). What happens if the child
calls printf() to print some output after closing the descriptor?
*/

int main(void) {

    int rc = fork();
    if ( rc < 0 ) {
        printf("error forking\n");
    }
    else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("here i am printing in child\n");
    }
    else {
        printf("here I am printing in parent\n");
    }
    return 0;
}