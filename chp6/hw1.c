#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(void) {
    struct timeval tv;
    struct timezone tz;
    int time = gettimeofday(&tv, &tz);
    if (time == 0) {
        printf("time1\n");
        printf("    seconds since epoch(1970) : %ld\n", tv.tv_sec);
        printf("    microseconds: %d\n",tv.tv_usec);
        printf("    tz minutes west : %d\n", tz.tz_minuteswest);
    }
    int time2 = gettimeofday(&tv, &tz);
    if (time2 == 0) {
        printf("time2\n");
        printf("    seconds since epoch(1970) : %ld\n", tv.tv_sec);
        printf("    microseconds: %d\n",tv.tv_usec);
        printf("    tz minutes west : %d\n", tz.tz_minuteswest);
    }
    int time3 = gettimeofday(&tv, &tz);
    if (time3 == 0) {
        printf("time3\n");
        printf("    seconds since epoch(1970) : %ld\n", tv.tv_sec);
        printf("    microseconds: %d\n",tv.tv_usec);
        printf("    tz minutes west : %d\n", tz.tz_minuteswest);
    }
}
