#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char *cmd[MAXARG];
    int cmd_argc = 0;

    // bỏ qua "-n 1" nếu có
    if(argc > 2 && strcmp(argv[1], "-n") == 0){
        for(int i = 3; i < argc; i++){
            cmd[cmd_argc++] = argv[i];
        }
    } else {
        for(int i = 1; i < argc; i++){
            cmd[cmd_argc++] = argv[i];
        }
    }

    char line[128];
    char *args[MAXARG];
    int idx = 0;
    char c;

    while(read(0, &c, 1) == 1){
        if(c == '\n'){
            line[idx] = 0;

            int k = 0;

            // copy command
            for(int i = 0; i < cmd_argc; i++)
                args[k++] = cmd[i];

            // thêm input
            args[k++] = line;
            args[k] = 0;

            if(fork() == 0){
                exec(args[0], args);
                exit(0);
            }
            wait(0);

            idx = 0;
        } else {
            line[idx++] = c;
        }
    }

    exit(0);
}
