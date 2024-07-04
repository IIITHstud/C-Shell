#include "headers.h"
#include "prompt.h"

// void sigtstp_handler(int sig)
// {
//     // if(sig==SIGTSTP){

//     printf("%d\n",foregroundprocessid);

//       if (kill(foregroundprocessid,0) == 0)
//     {
//         kill(foregroundprocessid, SIGTSTP);
//         // printf("\nProcess %d suspended.\n", foregroundprocessid);
//         // foregroundprocessid = 0;
//     }
//     // else{
//     //     // printf("hello");
//     //      printf("\nCtrl-Z pressed, but not suspending the shell.\n");
//     // // }
//     // }

// }
void process_single_command(char *input2, int flag, char *homedirectory, char *previous_directory, char *copy_of_input, int *count_of_history, char **history, Process *processids, int *numberofprocesses)
{
    char *copy = strdup(input2);

    char *parsedpipeargument[MAXARGUMENTS];
    int count = 0;
    // parsedpipeargument[0]="sh";
    // parsedpipeargument[1]="-c";
    // parsedpipeargument[2]=input2;
    // parsedpipeargument[3]=NULL;

    // printf("%s",input2);

    for (int i = 0; i < MAXARGUMENTS; i++)
    {
        parsedpipeargument[i] = strsep(&input2, " \n\t");
        if (parsedpipeargument[i] == NULL)
        {
            break;
        }
        if (strlen(parsedpipeargument[i]) == 0)
        {
            i--;
        }
        // count++;
    }

    while (parsedpipeargument[count] != NULL)
    {
        count++;
    }
    if (strcmp(parsedpipeargument[0], "warp") == 0)
    {
        char current_directory[1000];
        getcwd(current_directory, sizeof(current_directory));

        executewarp(parsedpipeargument, homedirectory, previous_directory);

        strcpy(previous_directory, current_directory);
    }

    else if (strcmp(parsedpipeargument[0], "peek") == 0)
    {
        executepeek(parsedpipeargument, homedirectory, previous_directory);
    }

    else if (strcmp(parsedpipeargument[0], "pastevents") == 0)
    {
        print_history(parsedpipeargument, count_of_history, history, homedirectory, previous_directory, copy_of_input);
    }

    else if (strcmp(parsedpipeargument[0], "proclore") == 0)
    {
        proclore(parsedpipeargument, homedirectory);
    }
    else if (strcmp(parsedpipeargument[0], "seek") == 0)
    {
        seek_command(parsedpipeargument, homedirectory, previous_directory);
    }
    else
    {

        pid_t pid;
        int status;
        struct timeval start_time, end_time;

        gettimeofday(&start_time, NULL);

        pid = fork();
        if (pid == 0)
        {
            //    signal(SIGINT,SIG_DFL);
            //     signal(SIGTSTP,SIG_DFL);
            // Child process
            if (execvp(parsedpipeargument[0], parsedpipeargument) == -1)
            {

                printf("ERROR:%s is not a valid command\n", parsedpipeargument[0]);
                exit(1);
            }
        }

        else if (pid > 0)
        {

            // background process
            if (flag == 1)
            {

                // printf("---->%d",*numberofprocesses);
                // signal(SIGTSTP, sigtstp_handler);

                //here we are storing pid and process name
                pid_t copy_pid;
                copy_pid = pid;
                processids[*numberofprocesses].pid = copy_pid;
                // foregroundprocessid=copy_pid;

                strcpy(processids[*numberofprocesses].processname, copy);//here copying the process name
                (*numberofprocesses)++;
                while ((pid = waitpid(-1, &status, WNOHANG)) > 0)//for multiple background processes
                {//by this what we are doing for a particular user input
                 //then we waitpid() is finding that any child process is finished
                 //if yes it will return its pid then using status we can see if it exited normmally or abnormally
                 //and we can do that until there are finished child process
                 //like many process have finished so it will fetch data for all
                 //and if there are no child process left....then we don't want to wait for any child
                 //process to finish...so we are using (WNOHANG)
                    if (WIFEXITED(status))
                    {
                        printf("%s exited normally (%d)\n", parsedpipeargument[0], pid);
                    }
                    else
                    {
                        printf("Background process %d exited abnormally\n", pid);
                    }
                }

                printf("%d\n", copy_pid);

                // waitpid(pid, &status, 0);
            }
            else // foreground
            {

                // signal(SIGINT,SIG_IGN);
                // signal(SIGTSTP,SIG_IGN);
                // signal(SIGTSTP, sigtstp_handler);

                int copy_pid;
                copy_pid = pid;
                // foregroundrocessid=pid
                foregroundprocessid = copy_pid;
                processids[*numberofprocesses].pid = copy_pid;

                strcpy(processids[*numberofprocesses].processname, copy);
                (*numberofprocesses)++;

                while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
                {
                    if (WIFEXITED(status))
                    {
                        printf("%s exited normally (%d)\n", parsedpipeargument[0], pid);
                    }
                    else
                    {
                        printf("Background process %d exited abnormally\n", pid);
                    }
                }
                printf("%d\n", copy_pid);

                while (1)
                {
                    waitpid(pid, &status, WUNTRACED);
                    if (WIFEXITED(status))
                    {
                        break;
                    }
                    if (WIFSTOPPED(status))
                    {
                        break;
                    }
                }
            }
            gettimeofday(&end_time, NULL);
            int time = end_time.tv_sec - start_time.tv_sec;
            if (time > 2)
            {
                printf("%s for %d seconds\n", parsedpipeargument[0], time);
            }
        }
        else
        {
            perror("Fork error");
        }
    }
}

void executeprocess(char *input2, char *homedirectory, char *previous_directory, char *copy_of_input, int *count_of_history, char **history, Process *processids, int *numberofprocesses)
{
    // int pid1=getpid()
    // processids[numberofprocesses]=
    // printf("hello");
    int count = 0;
    char parsedpipeargument[MAXARGUMENTS][MAXARGUMENTS];

    int l = strlen(input2);
    for (int i = 0; i < l; i++)
    {
        int flag = 0;

        if (input2[i] == '&') // it means its an background process
        {
            // parsedpipeargument[count] = malloc(i + 1);
            strncpy(parsedpipeargument[count], input2, i);
            parsedpipeargument[count][i] = '\0';
            flag = 1;
            char copy[1000];
            strcpy(copy, parsedpipeargument[count]);
            process_single_command(copy, flag, homedirectory, previous_directory, copy_of_input, count_of_history, history, processids, numberofprocesses);
            // free(parsedpipeargument[count]);

            input2 += i + 1;
            l -= i + 1;
            i = -1;
            count++;
        }
    }
    if (l > 0) // foreground process
    {
        char copy[1000];
        strcpy(parsedpipeargument[count], input2);
        strcpy(copy, parsedpipeargument[count]);
        process_single_command(copy, 0, homedirectory, previous_directory, copy_of_input, count_of_history, history, processids, numberofprocesses);
        // passing flag as 0 to represent it is foreground
    }
    // printf("%d",count);
}
