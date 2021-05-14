#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct flags
{
    int selEf;
    int selUs;
    char *uid;
    int selPr;
    char *pid;
    int fail;

} flags;

flags *parsecommand(int argc, char *argv[])
{
    int opt;
    flags *flag = malloc(sizeof(flags));

    flag->selEf = 0;
    flag->selUs = 0;
    flag->uid = 0;
    flag->selPr = 0;
    flag->pid = 0;
    flag->fail = 0;

    while ((opt = getopt(argc, argv, ":eu:p:")) != -1)
    {
        switch (opt)
        {
        case 'e':
            flag->selEf = 1;
            printf("option %c\n", opt);
            break;

        case 'u':
            flag->selUs = 1;
            flag->uid = optarg;
            printf("option %c\nUID %s", opt, optarg);
            break;

        case 'p':
            flag->selPr = 1;
            flag->pid = optarg;
            printf("option %c\nPID %s\n", opt, optarg);
            break;

        case ':':
            printf("option needs a value\n");
            break;

        case '?':
            flag->fail = 1;
            printf("unknown option %c used\n", optopt);
            return flag;
            break;

        default:
            break;
        }
    }

    return flag;
}
