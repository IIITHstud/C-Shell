#include "headers.h"

char directory[100];
int foregroundprocessid = 0;
void sigint_handler(int sig)
{
    kill(foregroundprocessid, SIGINT);
    printf("\n");
}
void sigtstp_handler(int sig)
{
    // printf("%d\n",foregroundprocessid);
    kill(foregroundprocessid,SIGTSTP );
    printf("\n");
}

int main()
{
    // shellpid=getpid();
    int count_of_history = 0;
    char *history[16];
    Process processids[1000];

    int countofprocessids = 0;
    // printf("%d-->terminal\n",getpid());
    char cwd[1000];
    getcwd(cwd, sizeof(cwd));
    getcwd(directory, sizeof(directory));
    
    char previous_directory[1000];
    strcpy(previous_directory, directory);

    char history_file_path[1000];
    strcpy(history_file_path, cwd);
    strcat(history_file_path, "/");
    strcat(history_file_path, HISTORY_FILE);//here we are creating history.txt in the same directory where we run the make
    load_history(&count_of_history, history, history_file_path);

    //   setpgid(0, 0);
    // trap 'sigint_handler' SIGINT
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    while (1)
    {
        prompt(directory);

        char input[4096];
        char copy_input[4096];
        if (fgets(input, 4096, stdin) == NULL)
        {
            // for(int i=0;i<countofprocessids;i++){
            kill(0, SIGTERM);

            printf("\n");
            break;
        }

        // fgets(input, 4096, stdin);
        strcpy(copy_input, input);
        char *stringsafterparsing[MAXARGUMENTS];
        char *copystringsafterparsing[MAXARGUMENTS];
        if (strcmp(input, "exit\n") == 0)
        {
            break;
        }

        int l = parsesemicolon(input, stringsafterparsing);//this stores all the multicommand in the stringafterpassing and it gives the count of commands 
                                                            //that are given by seperating from ; in oneline

        for (int i = 0; i < l; i++)
        {
            copystringsafterparsing[i] = strdup(stringsafterparsing[i]);
            int u = strlen(copystringsafterparsing[i]);
            if (copystringsafterparsing[i][u - 1] == '\n')//in the last string there is \n included so need to remove that 
            {                                             //bcz when we get input from fgets ,it also include newline character at the end of the string 
                copystringsafterparsing[i][u - 1] = '\0';
            }
        }

        for (int i = 0; i < l; i++)
        {
            parsespace(stringsafterparsing[i], copystringsafterparsing, i, &count_of_history, history, history_file_path, directory, previous_directory, copystringsafterparsing[i], processids, &countofprocessids);
        }
    }
}
