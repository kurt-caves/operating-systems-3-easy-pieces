#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>

// counters value may change at any time
volatile int counter = 0;
int loops;

// function to run a for loop
void *worker(void *arg) {
    int i;
    for(i=0; i< loops; i++)
        counter++;
    return NULL;
}

int main(int argc, char *argv[]) {

    if(argc != 2) {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    }
    // takes value from CLI
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value : %d\n", counter);

    // pthread_create enables concurrency
    pthread_create(&p1, NULL, worker, NULL);
    pthread_create(&p2, NULL, worker, NULL);

    // used to wait for a thread to complete its execution
    // optionally retrieve it's return value
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("Final value : %d\n", counter);
    return 0;

}