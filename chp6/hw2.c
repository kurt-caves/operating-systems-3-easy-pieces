#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

/*
The lmbench
benchmark does so by running two processes on a single CPU, and setting up two UNIX pipes between them; a pipe is just one of many ways
processes in a UNIX system can communicate with one another. The first
process then issues a write to the first pipe, and waits for a read on the
second; upon seeing the first process waiting for something to read from
the second pipe, the OS puts the first process in the blocked state, and
switches to the other process, which reads from the first pipe and then
writes to the second. When the second process tries to read from the first
pipe again, it blocks, and thus the back-and-forth cycle of communication
continues. By measuring the cost of communicating like this repeatedly,
lmbench can make a good estimate of the cost of a context switch. You
can try to re-create something similar here, using pipes, or perhaps some
other communication mechanism such as UNIX sockets.
One difficulty in measuring context-switch cost arises in systems with
more than one CPU; what you need to do on such a system is ensure that
your context-switching processes are located on the same processor. Fortunately, most operating systems have calls to bind a process to a particular processor; on Linux, for example, the sched setaffinity() call
is what you’re looking for. By ensuring both processes are on the same
processor, you are making sure to measure the cost of the OS stopping
one process and restoring another on the same CPU.
*/

#define ITERATIONS 1000

int main(void) {
    
    // fd[0] = read
    // fd[1] = write
    int fd1[2];
    int fd2[2];

    pipe(fd1);
    pipe(fd2);

    struct timeval start, end;

    if (fork() == 0) {
        //write
        close(fd1[0]);
        //read
        close(fd2[1]);

        int x = 42; // writing
        int a; // reading

        for(int i = 0; i < ITERATIONS; i++) {
            write(fd1[1], &x, sizeof(int));
            read(fd2[0], &a, sizeof(int));
        }
        printf("from fork2, a: %d\n",a);

        // write
        close(fd1[1]);
        // read
        close(fd2[0]);

        return 0;
    }

    if (fork() == 0) {

        close(fd1[1]);
        close(fd2[0]);

        int y;
        int b = 69;

        for(int i = 0; i < ITERATIONS; i++) {
            read(fd1[0], &y, sizeof(int));
            write(fd2[1], &b, sizeof(int));
        }
        printf("from fork1, y: %d\n",y);
        return 0;
    }

    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);

    gettimeofday(&start,NULL);

    // wait for childs to end
    wait(NULL);
    wait(NULL);

    gettimeofday(&end,NULL);
    printf("    start time seconds: %ld, microseconds %d\n", start.tv_sec, start.tv_usec);
    printf("    end time seconds: %ld, microseconds %d\n", end.tv_sec, end.tv_usec);
    return 0;
}