#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{

    int p_fd[2];
    int ch_fd[2];


    int pip = pipe(p_fd);
    if (pip < 0) {
      exit(1);
    }
    int pip2 = pipe(ch_fd);
    if (pip2 < 0) {
     exit(1);
    }

    int pid = fork();

    if (pid > 0) {
        //parent
        char buff[1];
        write(p_fd[1], "a", 1);
        pid = wait(0);
        read(ch_fd[0], buff , 1);
        printf("recieved pong\n");

    }
    else if (pid == 0) {
        //child
        char buff[1];
        read(p_fd[0], buff , 1);
        printf("recieved ping\n");
        write(ch_fd[1], "b", 1);
    } else {
      fprintf(2, "error: fork()\n");
      exit(1);
    }

    exit(0);
}
