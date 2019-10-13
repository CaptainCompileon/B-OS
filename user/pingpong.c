#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

    int p_fd[2];
    int ch_fd[2];

    int pid = fork();

    pipe(p_fd);
    pipe(ch_fd);

    if (pid >0) {
        //parent
        char buff = 'revieved ping';
        write(p_fd[1], buff, sizeof(buff));
        read(ch_fd[0], 1 , sizeof(buff))
    }
    else if (pid == 0) {
        //child
        char buff = 'revieved pong';
        read(p_fd[0], 1 , sizeof(buff));
        write(ch_fd[1], buff, sizeof(buff));
    }

    exit();
}
