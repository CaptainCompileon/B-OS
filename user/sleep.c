#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// argc: je pocet argumentov +1
// argv: pole argumentov
int main(int argc, char *argv[])
{
    //ak nie je zadany argument tak vypise hint
    if (argc < 2) {
        printf("use: sleep {number}");
    }
    //ak je spravi syscall sleep({number})
    if (argc == 2) {
        sleep(atoi(argv[1]));
    }

    exit(0);
}
