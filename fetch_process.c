#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

int is_pidDir(const struct dirent *somedir)
{
    const char *p;
    for (p = somedir->d_name; *p; p++)
    {
        if (!isdigit(*p))
        {
            return 0;
        }
    }
    return 1;
}

int fetchProcess()
{
    DIR *procf;
    FILE *fptr1;
    struct dirent *dirproc;
    char path1[1024];
    int pid;
    int ppid;
    int sessionid;
    char procState;

    procf = opendir("/proc");
    if (!procf)
    {
        perror("Opening directory failed");
        return 1;
    }

    while ((dirproc = readdir(procf)) != NULL)
    {
        if (!is_pidDir(dirproc))
        {
            continue;
        }

        snprintf(path1, sizeof(path1), "/proc/%s/stat", dirproc->d_name);
        fptr1 = fopen(path1, "r");

        if (!fptr1)
        {
            perror(path1);
            continue;
        }

        fscanf(fptr1, "%d %s %c %d %*d %d ", &pid, path1, &procState, &ppid, &sessionid);

        printf("%5d %-15s %-5c %-5d %-5d\n", pid, path1, procState, ppid, sessionid);
        fclose(fptr1);
    }
    closedir(procf);
    return 0;
}
