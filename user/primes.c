
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char *err = "fork failed";

    int prev[2];
    pipe(prev);

    int pid = fork();

    if (pid < 0)
    {
        write(2, err, strlen(err));
        exit(1);
    }

    if (pid == 0)
    {
        while (1)
        {
            int base = 0;
            
            close(prev[1]);
            if (0 == read(prev[0], &base, sizeof(base)))
            {
                close(prev[0]);
                exit(0);
            }

            printf("prime %d\n", base);

            int next[2];
            pipe(next);
            int pid = fork();
            if (pid < 0)
            {
                write(2, err, strlen(err));
                exit(1);
            }

            // parent
            if (pid > 0)
            {
                int cur = 0;
                for (; 0 != read(prev[0], &cur, sizeof(cur));)
                {
                    if (0 != cur % base)
                    {
                        write(next[1], &cur, sizeof(cur));
                    }
                }
                close(prev[0]);
                close(next[0]);
                close(next[1]);
                wait(0);
                exit(0);
            }

            // child
            close(prev[0]);
            prev[0] = next[0];
            prev[1] = next[1];
        }
        exit(0);
    }

    // parent
    close(prev[0]);
    for (int i = 2; i <= 32; i++)
    {
        write(prev[1], &i, sizeof(i));
    }
    close(prev[1]);
    wait(0);

    exit(0);
}