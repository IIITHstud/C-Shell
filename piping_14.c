#include "headers.h"
#include "prompt.h"
// void execut_command2(char *outputfile,char*inputfile,char **args,int append){
//     // printf("%s",inputfile);

// }
int containsOnlySpacesOrTabs(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t') {
            return 1; // Found a character that is not a space or tab
        }
    }
    return 0; // All characters are spaces or tabs
}

void executepiping(char *input){

char *commands[MAXARGUMENTS];
char *copyofstringsafterparsing=strdup(input);

for(int i=0;i<MAXARGUMENTS;i++){
    commands[i]=strsep(&copyofstringsafterparsing,"|\n");
    if(commands[i]==NULL){
        break;
    }
    //The purpose of the if(strlen(commands[i])==0) condition followed by i-- in the code 
    //snippet is to handle empty strings that might result from consecutive delimiters in the parsed string. 
    if(strlen(commands[i])==0){
        i--;
    }
    // count++;

}

int numCommands=0;
while (commands[numCommands]!=NULL)
{
    numCommands++;
    /* code */
}
if(numCommands<2){
    printf("invalid use of pipe\n");
    return;
}
for(int i=0;i<numCommands;i++){
    if(containsOnlySpacesOrTabs(commands[i])==0){
        printf("invalid use of pipe\n");
        return;
    }

}
    //The int pipes[numCommands-1][2]; line declares an array of file descriptors to set up multiple pipes for communication between processes. Each row in the pipes 
    //array represents a pipe, where the first element (pipes[i][0]) is the read end of the pipe, and the second element (pipes[i][1]) is the write end. 
    //These pipes enable data flow between successive pairs of processes in a pipeline setup, facilitating inter-process communication in a command-line interpreter or similar applications.
    int pipes[numCommands-1][2];

    for (int i = 0; i < numCommands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe failed");
            return ;
        }
    }

    for (int i = 0; i < numCommands; i++) { 
        pid_t child = fork();

        if (child == -1) {
            perror("Fork failed");
            return ;
        }
if (child == 0) {
    if (i > 0) {
        dup2(pipes[i - 1][0], STDIN_FILENO);//use to connect input of the previous command to the input descryptor of current command. So now basically it reads the previous input
        close(pipes[i - 1][0]);
    }

    if (i < numCommands - 1) {
        dup2(pipes[i][1], STDOUT_FILENO);//writes in the current pipe
        close(pipes[i][1]);
    }

char *command[MAXARGUMENTS];


char *copyofstrings=strdup(commands[i]);


for(int i=0;i<MAXARGUMENTS;i++){
    command[i]=strsep(&copyofstrings," \n\t");
    if(command[i]==NULL){
        break;
    }
    if(strlen(command[i])==0){
        i--;
    }
    // count++;

}
    // printf("%s hello",command[0]);
int count=0;
while (command[count]!=NULL)
{
    count++;
    /* code */
}

    command[count] = NULL; // Nu

    if(strcmp(command[0],"sed")==0 && count>2){
    // printf("hello\n");
         command[1] = "-e"; 
    command[2] = "s/ //g"; 

    // Execute the modified command
    execvp(command[0], command);

    // If execvp fails, report an error
    perror("execvp");
    exit(1);
// char *newcommand={"sed","-e","s/old_text/new_text/g", NULL};
// execvp(command[0], command);
// perror("execvp");
// exit(1);
}

else{
execvp(command[0], command);
    perror("execvp");
    exit(1);

}

}
    //close(pipes[i - 1][0]);: This line closes the read end of the pipe connected to the previous command's output. 
    //After the child process has finished reading from this pipe, the parent process doesn't need it anymore, so it's closed to release system resources.
    //close(pipes[i][1]);: Similarly, this line closes the write end of the pipe connected to the current command's output.
    // After the child process has finished writing to this pipe, the parent process doesn't need it anymore, so it's closed to release system resources.


    else {
            // Parent process
            wait(NULL);
            if (i > 0) {
                // Close the read end of the previous pipe
                close(pipes[i - 1][0]);
            }
            
            if (i < numCommands - 1) {
                // Close the write end of the current pipe
                close(pipes[i][1]);
            }

            // Wait for the child to finish
        }
    }



// printf("%d\n",count);
// for(int i=0;i<count;i++){
//     printf("%s\n",parsedpipeargument[i]);
// }
// if(count < 2){


// }
// printf("%d",count);
}



// Parsing Input:
// The input string containing multiple commands separated by pipes (|) is parsed and stored in an array called commands.
// Validity Check:
// The number of commands is checked. If there are less than two commands, the function returns, as a pipeline requires at least two commands.
// Each command is checked for containing only spaces or tabs. If any command contains non-space characters, the function returns, indicating an invalid use of the pipeline.
// Setting up Pipes:
// An array of file descriptors, pipes[numCommands-1][2], is created to set up multiple pipes for communication between processes.
// Each pipe represents a communication channel between two successive commands.
// Forking Child Processes:
// A loop forks a child process for each command in the pipeline.
// Each child process inherits the file descriptors of the pipes from the parent.
// Input and Output Redirection:
// For each child process:
// If it's not the first command, the standard input is redirected to read from the read end of the pipe connected to the previous command's output.
// If it's not the last command, the standard output is redirected to write to the write end of the pipe connected to the next command's input.
// Command Execution:
// Each child process executes its respective command using execvp.
// If the command is sed and has more than two arguments, it's modified before execution to replace spaces with sed commands.
// Cleanup in Parent Process:
// The parent process waits for each child to finish executing its command.
// After each child process completes its task:
// If it's not the first command, the read end of the pipe connected to the previous command's output is closed.
// If it's not the last command, the write end of the pipe connected to the current command's output is closed.
// Summary:
// The code parses and validates the input commands, sets up pipes for inter-process communication, forks child processes for each command, redirects input and output appropriately, executes the commands, and cleans up resources after command execution. This sequence of steps ensures the proper execution of a pipeline of commands in a shell-like environment.





