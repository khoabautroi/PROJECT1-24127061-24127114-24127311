#include "kernel/types.h"
#include "kernel/procinfo.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    struct procinfo info;
    int pid;
    if(argc < 2){
        printf("Usage: procinfo [pid]\n");
        exit(1);
    }
    pid = atoi(argv[1]); // Chuyển chuỗi người dùng nhập thành số int
    if(procinfo(pid, &info) == 0) {
        printf("Process: %s\n", info.name);
        printf("PID: %d, PPID: %d\n", info.pid, info.ppid);
        char *states[] = {"UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};
        printf("State:  %s\n", states[info.state]);        
        printf("Memory: %d bytes\n", (int)info.sz);
    }
    else printf("Error retrieving procinfo\n");
    exit(0);
}