// File: avoid_zombie.c

#include <stdio.h>
#include <stdlib.h>     // For exit()
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>   // For wait()

int main()
{
    int pid1, pid2, cpid;

    pid1 = fork();

    if (pid1 == 0)
    {
        // First child
        printf("1st child's process id is %d\n", getpid());
        printf("First-child terminating from memory\n");
        exit(0);  // Properly exit to avoid dangling
    }
    else
    {
        pid2 = fork();

        if (pid2 == 0)
        {
            // Second child
            printf("2nd child's process id is %d\n", getpid());
            printf("Second-child terminating\n");
            exit(0);
        }
        else
        {
            // Parent process: waits for both children to avoid zombies
            cpid = wait(NULL);  // wait for one child
            printf("Child with pid %d died\n", cpid);

            cpid = wait(NULL);  // wait for second child
            printf("Child with pid %d died\n", cpid);

            printf("I am parent \n");
        }
    }

    return 0;
}
