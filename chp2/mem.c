#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>

double GetTime() {
    // create timeval struct
    struct timeval t;
    // if this returns 0 then success
    int rc = gettimeofday(&t, NULL); // ignore timezone set to null
    // ensure the function executes without error
    assert(rc == 0);
    // return current time, seconds and microseconds
    return (double) t.tv_sec + (double) t.tv_usec/1e6;
}

void Spin(int howlong) {
    double t = GetTime();
    while ((GetTime() - t) < (double) howlong)
        ; // do nothing
}

int main(int argc, char *argv[]) {

    // allocate mem for p on heap
    int *p = malloc(sizeof(int));
    // make sure its not null
    assert(p != NULL);
    // print the process id as well as memory address
    printf("(%d) memory address of p: %08x\n", (int) getpid(), (unsigned) p);

    *p = 0;
    while (1) {
        Spin(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p);
    }



}