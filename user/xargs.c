#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(2, "Error: too less parameters for xargs\n");
        exit(1);
    }

    int i;
    int pNumber = 0;
    char *p[MAXARG];
    for (i = 1; i < argc; ++i)
    {
        p[pNumber++] = argv[i];
    }
    int place = pNumber;
    char ch;
    char *line;
    char s[512];
    line = s;
    int index = 0;
    while (read(0, &ch, 1) > 0)
    {
        if (ch == '\n')
        {
            line[index] = '\0';
            index = 0;

            p[pNumber++] = line;
            p[pNumber] = 0;

            if (fork())
            {
                wait(0);
                pNumber = place;
            }
            else
            {
                exec(argv[1], p);
            }
        }
        else if (ch == ' ')
        {
            line[index] = '\0';
            index = 0;
            p[pNumber++] = line;
            char s[512];
            line = s;
        }
        else
        {
            line[index++] = ch;
        }
    }
    exit(0);
}
