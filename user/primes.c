#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

void
primes(int fd0);

int
main(int argc, char const *argv[])
{

    if (argc != 1)
    {
        printf("use: primes\n");
        exit(0);
    }

    int fd[2];
    int n_start = 2;
    int n_end = 35;

    pipe(fd);

    int pid = fork();

    if (pid == 0)
    {
        close(fd[1]);
        primes(fd[0]);
        exit(0);
    }
    else if (pid > 0)
    {
        close(fd[0]);
        close(1);
        for(int i = n_start; i <= n_end; i++) {write(fd[1], &i, 4);}
        close(fd[1]);
        wait(0);
        exit(0);
    }
    else
    {
        printf("err: fork()");
        exit(0);
    }
}

void
primes(int fd0)
{
    int prime, i;

    if(read(fd0, &prime, 4) <= 0)
    {
        exit(0);
    }
     int fd[2];

    printf("prime: %d\n", prime);
    pipe(fd);

    int pid = fork();
    if (pid == 0)
    {
        close(fd[1]);
        primes(fd[0]);
        exit(0);
    }
    else if (pid > 0)
    {
        close(fd[0]);
       while (read(fd0, &i, 4) > 0)
       {
            if (i % prime != 0) {
                write(fd[1], &i, 4);
            }
        }
        close(fd[1]);
        wait(0);
        exit(0);
    }
    else
    {
        printf("err: fork()");
        exit(0);
    }
}
