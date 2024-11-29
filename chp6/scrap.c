#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <mach/mach.h>
#include <pthread.h>

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

void set_affinity_tag(int tag) {
    // Create a policy with the given tag
    thread_affinity_policy_data_t policy;
    policy.affinity_tag = tag; // Set the affinity tag

    // Apply the policy to the current thread
    kern_return_t result = thread_policy_set(
        pthread_mach_thread_np(pthread_self()), // Get Mach thread for the current POSIX thread
        THREAD_AFFINITY_POLICY,                 // Specify the affinity policy
        (thread_policy_t)&policy,               // Pass the policy as expected by the API
        1                                       // The size of the policy (1 element)
    );

    // Check the result
    if (result != KERN_SUCCESS) {
        // Print an error message if setting the policy fails
        fprintf(stderr, "Error: Could not set affinity tag %d (error code: %d)\n", tag, result);
    } else {
        // Confirm success
        printf("Success: Affinity tag %d applied to the thread\n", tag);
    }
}

int main(void) {
    // fd[0] = read forever and always will fd[0] be read
    // fd[1] = write, same with write
    // fd will be filled with two file descriptors
    int fd[2];
    pipe(fd);

    int fd2[2];
    pipe(fd2);
   
    // will be used to measure time
    struct timeval tv;
    
    
    // we are writing here
    if(fork() == 0) {
        // set_affinity_tag(1);

        int time1 = gettimeofday(&tv,NULL);
        if (time1 == 0) {
            printf("time1\n");
            printf("    seconds since epoch(1970) : %ld\n", tv.tv_sec);
            printf("    microseconds: %d\n\n",tv.tv_usec);
        }
        else {
            printf("error getting time1\n");
        }

        // write section
        close(fd[0]);
        int x = 42;
        // write 42 to the write portion of the pipe
        write(fd[1], &x, sizeof(int));
        close(fd[1]);

        // read section
        close(fd2[1]);
        int a;
        read(fd2[0], &a, sizeof(int));
        printf("from fork 2, a: %d\n\n", a);
        close(fd2[0]);

        return 0;
    }

    if(fork() == 0) {
        // set_affinity_tag(1);

        int time2 = gettimeofday(&tv,NULL);
        if (time2 == 0) {
            printf("time2\n");
            printf("    seconds since epoch(1970) : %ld\n", tv.tv_sec);
            printf("    microseconds: %d\n\n",tv.tv_usec);
        }
        else {
            printf("error getting time2\n");
        }

        // read section
        close(fd[1]);
        int y;
        // read data from the read part of the pipe
        read(fd[0], &y, sizeof(int));
        printf("from fork1: %d\n\n", y);
        close(fd[0]);

        // write section
        close(fd2[0]);
        int b = 69;
        write(fd2[1], &b, sizeof(int));
        close(fd2[1]);

        return 0;
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL); // wait for child 1
    wait(NULL); // wait for child 2

    return 0;
}