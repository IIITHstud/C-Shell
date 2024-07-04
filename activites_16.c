#include "headers.h"

#include "prompt.h"

#define BUFFER_SIZE 1000
int compareProcesses(const void *a, const void *b)
{
    return strcmp(((struct Process *)a)->processname, ((struct Process *)b)->processname);
}


void activities(Process *processids, int *countofprocess)
{
    int count = 0;
    qsort(processids, *countofprocess, sizeof(struct Process), compareProcesses);

    for (int i = 0; i < *countofprocess; i++)
    {
        char name[1000];
        char status;
        char statusfile[1000];
        char statPath[256];
        snprintf(statPath, sizeof(statPath), "/proc/%d/status", processids[i].pid);

        FILE *statfile = fopen(statPath, "r");
        if (statfile == NULL)
        {

            continue;
        }
        else
        {
            // printf("%d",);
            char line[1000];
            while (fgets(line, sizeof(line), statfile))
            {

                if (strncmp(line, "State:", 6) == 0)
                {
                    sscanf(line, "State: %c", &status);
                    // printf("%c\n",status);
                    if (status == 'S')
                    {
                        strcpy(statusfile, "Running");
                    }
                    else if (status == 'T')
                    {
                        strcpy(statusfile, "Stopped");
                    }
                    else
                    {

                        continue;
                    }
                    // printf("%c\n",status);
                    printf("%d : %s - %s\n", processids[i].pid, processids[i].processname, statusfile);
                }
            }
            count++;
            fclose(statfile);
            // sigint
        }
    }

}
