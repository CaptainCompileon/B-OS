#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

#define MAX 512

int
main(int argc, char *argv[])
{
    if(argc == 1){
        fprintf(2, "xargs: no command\n");
        exit(0);
    }

    char *argvt[MAXARG];
    memset(argvt, 0, sizeof(argvt));
    int i;
    for(i = 0; i < argc - 1; i++){
        argvt[i] = argv[i+1];
    }

    char linebuf[MAX];
    while(gets(linebuf, MAX) > 0){
        int m = 0;
        linebuf[strlen(linebuf) - 1] = '\0'; // drop '\n';
        char *p, *s;
        p = linebuf;
        while(*p != '\0'){
            while(*p++ == ' '); // skip whitespace
            s = p - 1;
            while(*p != ' ' && *p != '\0'){ // find the next whitspace;
                p++;
            }; 
            *p++ = '\0';
            argvt[argc -1 + (m++)] = s;
            if(argc + m >= MAXARG){
                fprintf(2, "xargs: too manh arguments\n");
                exit(0);
            }
            //fprintf(2, "%s\n",s);
        } 
        
        if(fork() == 0){
            exec(argv[1], argvt);
            fprintf(2, "xargs: exec error\n");
            fprintf(2, "argc: %d\n", argc + m);
            fprintf(2, "argv[1]: %s\n", argvt[0]);
            fprintf(2, "argv:");
            for(i = 0; i < argc + m - 1; i++){
                fprintf(2, " %s", argvt[i]);
            }
            fprintf(2, "\n");
            exit(0);
        }
        wait(0);
    }
    exit(0);
}
