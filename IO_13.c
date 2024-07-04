#include "headers.h"
#include "prompt.h"
void executesystemcommands(char *outputfile, char **args, int append){
    


    
}
void execut_command2(char *outputfile, char *inputfile, char **args, int append)
{
    // printf("%s",inputfile);
    char temp_output[] = "temp_output.txt";
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    //we are doing this particular operation in child process only
    else if (pid == 0)
    {

        int flags = O_WRONLY | O_CREAT;
        if (append == 0)
        {
            flags |= O_APPEND;
            int file_descrpytor = open(outputfile, flags, 0644);
            if (file_descrpytor == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(file_descrpytor, STDOUT_FILENO);
            close(file_descrpytor);
        }
        // int flags = O_WRONLY | O_CREAT;
        else if (append == 1)
        {
            flags |= O_TRUNC;
            int file_descrpytor = open(outputfile, flags, 0644);
            if (file_descrpytor == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(file_descrpytor, STDOUT_FILENO);
            close(file_descrpytor);
        }

        int file_descrpytor2 = open(inputfile, O_RDONLY);
        if (file_descrpytor2 == -1)
        {
            printf("No such input file found!");
            exit(1);
        }
        dup2(file_descrpytor2, STDIN_FILENO);//STDIN_FILENO --> this is standard input file desciptor
        close(file_descrpytor2);
        int t = execvp(args[0], args);
        if (t < 0)
        {
            printf("Not a valid command");
            exit(1);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}


void execut_command(char *outputfile, char **args, int append)
{
    // printf("%s\n",args[0]);
    if(strcmp(args[0],"peek")==0 && append==-1){
        executesystemcommands(outputfile,args,append);

    }
    pid_t pid = fork();
    //here creating a child process 
    //so we can independently do anything in child process n in parent seperately


    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    //so we are exectung this in the child process only
    else if (pid == 0)
    {
        int flags = O_WRONLY | O_CREAT;
        if (append == 0)// >>
        {
            flags |= O_APPEND;//if append == 0 then we are appending at the end
            int file_descrpytor = open(outputfile, flags, 0644);
            if (file_descrpytor == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(file_descrpytor, STDOUT_FILENO);
            close(file_descrpytor);
            int t = execvp(args[0], args);
            if (t < 0)
            {
                printf("Not a valid command");
                exit(1);
            }
        }
        // int flags = O_WRONLY | O_CREAT;
        else if (append == 1)// >
        {
            flags |= O_TRUNC;//truncate length equal to zero
            int file_descrpytor = open(outputfile, flags, 0644);
            if (file_descrpytor == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(file_descrpytor, STDOUT_FILENO);
            close(file_descrpytor);
            int t = execvp(args[0], args);
            if (t < 0)
            {
                printf("Not a valid command");
                exit(1);
            }
        }

        // int flags = O_WRONLY | O_CREAT;
        else
        {
            // flags |=O_APPEND;
            int file_descrpytor = open(outputfile, O_RDONLY);//for rad mode
            if (file_descrpytor == -1)
            {
                printf("No such input file found!");
                exit(1);
            }
            dup2(file_descrpytor, STDIN_FILENO);
            close(file_descrpytor);
            int t = execvp(args[0], args);
            if (t < 0)
            {
                printf("Not a valid command");
                exit(1);
            }
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void input_output(char *input,char *homedirectory,char *previousdirectory)
{

    // here input2 is the complete unique string which came after sepration on the basis of semicolon..

    char *args[MAXARGUMENTS];
    char *outputfile;//in case of > we have a outputfile pointer...pointing to from where we need to print the data
    char *inputfile;//in case of < we have a inputfile pointer ...pointing to from where we need to fetch the data

    char *command;
    char *copy = strdup(input);
    int append;


    char *operator;//this stores the pointer to the character >> or >
    char *operator2;//this store the pointer to the character <
    size_t substring_length;
    size_t substring_length2;

    char *substring = malloc(sizeof(char) * MAXARGUMENTS);//this stores the command
    char *substring2 = malloc(sizeof(char) * MAXARGUMENTS);//this stores the second file in case of >> < or > <

    //this means either this will >> <  be there or > < this will be there
    if (((operator= strstr(input, ">>")) != NULL || (operator= strstr(input, ">")) != NULL) && (operator2 = strstr(input, "<")) != NULL)
    {
        inputfile = operator2 + 1;
        substring_length = operator2 - input;
        strncpy(substring, input, substring_length);
        substring[substring_length] = '\0';

        if ((operator= strstr(input, ">>")) != NULL)
        {
            outputfile = operator+ 2;
            append = 0;
            substring_length2 = operator- input;
            strncpy(substring2, input, substring_length2);
            substring2[substring_length2] = '\0';
        }
        else if ((operator= strstr(input, ">")) != NULL)
        {
            outputfile = operator+ 1;
            append = 1;
            substring_length2 = operator- input;
            strncpy(substring2, input, substring_length2);
            substring2[substring_length2] = '\0';
        }

        //substring2 is from index 0 
        //here we are copying from substring2 only...not from input
        memmove(substring2, substring2 + substring_length + 1, strlen(substring2));
        
    }
    else
    {

        if ((operator= strstr(input, ">>")) != NULL)
        {
            outputfile = operator+ 2;
            substring_length = operator- input;
            strncpy(substring, input, substring_length);
            substring[substring_length] = '\0';
            append = 0;
        }
        else if ((operator= strstr(input, ">")) != NULL)
        {
            outputfile = operator+ 1;
            substring_length = operator- input;
            strncpy(substring, input, substring_length);
            substring[substring_length] = '\0';
            append = 1;
        }
        else if ((operator= strstr(input, "<")) != NULL)
        {
            outputfile = operator+ 1;
            substring_length = operator- input;
            strncpy(substring, input, substring_length);
            substring[substring_length] = '\0';
            append = -1;
        }
    }

    for (int i = 0; i < MAXARGUMENTS; i++)
    {
        args[i] = strsep(&substring, " \n\t");
        if (args[i] == NULL)
        {
            break;
        }
        if (strlen(args[i]) == 0)
        {
            i--;
        }
        // count++;
    }

    int count = 0;
    while (args[count] != NULL)
    {
        count++;
    }

    char *file = strtok(outputfile, " \t\n");
    if (((operator= strstr(input, ">>")) != NULL || (operator= strstr(input, ">")) != NULL) && (operator2 = strstr(input, "<")) != NULL)
    {
        // }

        char *file2 = strtok(substring2, " \t\n");
        execut_command2(file, file2, args, append);
    }
    // printf("%s\n",file);
    // else if(strcmp(args[0],"peek")==0){

    // }
    else
    {
        execut_command(file, args, append);
    }
}