#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>

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
    
    if (argc != 2) {
        fprintf(stderr, "usage: cpu <string>\n");
        exit(1);
    }

    char *str = argv[1];

    while (1) {
        printf("%s\n", str);
        Spin(1);
    }
    return 0;
}