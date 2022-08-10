#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) {
    int pc_channel[2];
    int cp_channel[2];
    char buffer[20];

    pipe(pc_channel);
    pipe(cp_channel);

    if (fork()) {
        // parent
        write(pc_channel[1], "ping", strlen("ping"));
        read(cp_channel[0], buffer, strlen("pong"));
        printf("%d: received %s\n", getpid(), buffer);
    } else {
        // child
        read(pc_channel[0], buffer, strlen("pong"));
        printf("%d: received %s\n", getpid(), buffer);
        write(cp_channel[1], "pong", strlen("pong"));
    }

    exit(0);
}