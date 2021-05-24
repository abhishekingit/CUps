#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

typedef struct ProcessList
{
    char *pid;
    struct ProcessList *next;

} ProcessList;

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

void printPIDList(struct ProcessList *n)
{
    while (n->pid != NULL)
    {
        printf("%s\n", n->pid);
        n = n->next;
    }
}

ProcessList *fetchProcessList()
{
    DIR *procf;
    struct dirent *dirproc;

    ProcessList *head = (ProcessList *)malloc(sizeof(ProcessList));
    ProcessList *current = head;

    procf = opendir("/proc");
    if (!procf)
    {
        free(current);
        free(procf);
        perror("Opening directory failed");
        return NULL;
    }

    while ((dirproc = readdir(procf)) != NULL)
    {
        if (!is_pidDir(dirproc))
        {
            continue;
        }

        current->pid = malloc(1 + sizeof(dirproc->d_name));
        strcpy(current->pid, dirproc->d_name);
        current->next = malloc(sizeof(ProcessList));
        current = current->next;
        current->pid = NULL;
    }
    closedir(procf);
    return head;
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
        free(procf);
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

int getProcess(char *pid)
{
    DIR *procf;
    FILE *fptr1;
    struct dirent *dirproc;
    char path[1024];
    int Filepid;
    int ppid;
    int sessionid;
    char procState;
    // long unsigned int vsize;
    int flag = 0;

    procf = opendir("/proc");
    if (!procf)
    {
        perror("Opening directory failed");
        return 1;
    }

    while ((dirproc = readdir(procf)) != NULL)
    {
        if (strcmp(dirproc->d_name, pid) == 0)
        {
            snprintf(path, sizeof(path), "/proc/%s/stat", pid);
            fptr1 = fopen(path, "r");

            if (!fptr1)
            {
                perror(path);
                continue;
            }

            fscanf(fptr1, "%d %s %c %d %*d %d", &Filepid, path, &procState, &ppid, &sessionid);

            printf("%5d %-15s %-5c %-5d %-5d\n", Filepid, path, procState, ppid, sessionid);
            fclose(fptr1);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        fprintf(stdout, "No processes with PID found\n");
    }

    closedir(procf);
    return 0;
}
