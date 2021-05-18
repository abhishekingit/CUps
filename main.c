#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_parser.h"
#include "fetch_process.h"

//the main loop for the program
int main(int argc, char *argv[])
{
    flags *activeFlags = parsecommand(argc, argv);
    if (activeFlags == NULL)
    {
        return 0;
    }

    if (activeFlags->fail == 1)
    {
        fprintf(stderr, "CUps -e | -u <UID> | -p <PID>\n");
        return 0;
    }

    if (activeFlags->selEf)
    {
        printf("option e\n");
        printf("  PID ProcessName   State PPID SESSIONID\n");
        fetchProcess();
        return 0;
    }
    else
    {
        if (activeFlags->selUs)
        {
            printf("option u\n");
            if (activeFlags->uid)
            {
                printf("UID %s\n", activeFlags->uid);
                return 0;
            }
            else
            {
                printf("Also provide a UID\n");
                return 0;
            }
        }
        else
        {
            if (activeFlags->selPr)
            {
                printf("option p\n");
                if (activeFlags->pid)
                {
                    printf("PID %s\n", activeFlags->pid);
                    return 0;
                }
                else
                {
                    printf("Also provide a PID\n");
                    return 0;
                }
            }
            else
            {
                printf("No flag provided\n");
            }
        }
    }

    return 0;
}
