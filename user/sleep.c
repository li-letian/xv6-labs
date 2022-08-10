#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
    uint tick;

    if (argc != 2) {
        fprintf(2, "Usages sleep <ticks to sleep>\n");
        exit(1);
    }

    tick = atoi(argv[1]);
    sleep(tick);
    exit(0);
}