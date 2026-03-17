#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char buf[512];
    char *args[MAXARG];
    int i;

    for(i = 1; i < argc; i++){
        args[i-1] = argv[i];
    }

    int n = argc - 1;
    int idx = 0;
    char c;

    while(read(0, &c, 1) == 1){
        if(c == '\n'){
            buf[idx] = 0;

            args[n] = buf;
            args[n+1] = 0;

            if(fork() == 0){
                exec(args[0], args);
                exit(0);
            }
            wait(0);

            idx = 0;
        } else {
            buf[idx++] = c;
        }
    }

    exit(0);
}
