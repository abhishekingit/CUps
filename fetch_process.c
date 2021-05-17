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
    FILE *fptr;
    struct dirent *dirproc;
    char path[1024];
    int pid;

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

        snprintf(path, sizeof(path), "/proc/%s/stat", dirproc->d_name);
        fptr = fopen(path, "r");
        if (!fptr)
        {
            perror(path);
            continue;
        }

        fscanf(fptr, "%d %s", &pid, path);

        printf("%5d %-20s\n", pid, path);
        fclose(fptr);
    }
    closedir(procf);
    return 0;
}
