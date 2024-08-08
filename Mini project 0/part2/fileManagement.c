#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{

    //task 1
    int x = 25;
    int rc = fork();

    if (rc < 0)
    {

        printf("fork failed\n");

        exit(1);
    }
    else if (rc == 0)
    {
        printf("initial value of x in child process: %d\n", x);
        x = 9;
        printf("changed value of x in child process: %d\n", x);
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("value of x in parent process: %d\n", x);
        x = 4;
        printf("new value of x in parent process: %d\n", x);
    }

    //task 2
    int rc1;
    char parent_pid[13];
    snprintf(parent_pid, sizeof(parent_pid), "%d", getpid());
    rc1 = fork();

    if (rc1 < 0)
    {

        printf("fork failed");
        exit(1);
    }
    else if (rc1 == 0)
    {

        execlp("sh", "sh", "-c",
               "echo Parent Process ID: $1 > newfile.txt",
               "sh", parent_pid, (char *)NULL);

        printf("exec command failed");
    }
    else
    {

        wait(NULL);
        printf("the child process is completed\n");
    }


    // task 3
    int rc2;
    rc2 = fork();
    if (rc2 < 0)
    {
        printf("error in fork command\n");
        exit(1);
    }
    else if (rc2 == 0)
    {
        sleep(1.75);
        printf("after the parents process exited new parents process (PID: %d)\n", getppid());

        exit(0);
    }
    else
    {
        exit(0);
    }

    return 0;
}
