/*
 *   * * * main.c * * *
 *
 * Author: Nicolae Sapoval
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "thread_pool.h"

int main(int argc, char **argv)
{
    pid_t server_pid;
    int rv;

    int restart = 1;

    /*
      Run in a loop, so if the server fails, we just gracefully restart
    */
    while(restart)
    {
        server_pid = fork();
        if (server_pid == -1)
        {
            perror("main: fork() failed");
            exit(-1);
        }
        else if (server_pid == 0)
        {
            /* 
              We are in child process, so we can start server now
            */
            printf("Hello world! I am child.\n");
            restart = 0;
            scanf("%d", &rv);
        }
        else
        {
            /*
              Parent should wait until the child dies
            */
            wait(&rv);
            printf("Something went wrong, restarting.\n");
            restart = 1;
        }
    }

    return 0;
}