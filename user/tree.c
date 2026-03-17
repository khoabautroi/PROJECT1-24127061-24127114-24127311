#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void tree(char *path, int depth);

int
main(int argc, char *argv[])
{
    if(argc < 2){
        printf(".\n");
        tree(".", 0);
    } else {
        printf("%s/\n", argv[1]);
        tree(argv[1], 0);
    }
    exit(0);
}

void
tree(char *path, int depth)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        printf("tree: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        printf("tree: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if(st.type != T_DIR){
        close(fd);
        return;
    }

    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)
            continue;

        if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            continue;

        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        if(stat(buf, &st) < 0){
            printf("tree: cannot stat %s\n", buf);
            continue;
        }

        for(int i = 0; i < depth + 1; i++)
            printf("  ");

        printf("%s", de.name);

        if(st.type == T_DIR)
            printf("/");

        printf("\n");

        if(st.type == T_DIR)
            tree(buf, depth + 1);
    }

    close(fd);
}
