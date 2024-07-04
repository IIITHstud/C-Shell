#ifndef __PROMPT_H
#define __PROMPT_H

// extern int foregroundrocessid;

void prompt(char *homedirectory);
int parsesemicolon(char *input2,char **arguments);
void parsespace(char *input2,char ** stringsafterpartsing,int v,int *count_of_history,char **history,char *history_file_path,char *homedirectory,char *previous_directory,char * copy_of_input,Process *processids,int *numberofprocessids);
void executewarp(char **input2,char *homedirectory,char *previous_directory);
void executepeek(char **input2,char *homedirectory,char *previous_directory);
// void executepastevents(char **input2);
void storehistory(char **input2);
void add_to_history(char **input2,int count,int *count_of_history,char **history);
void proclore(char **input2,char *homedirectory);
void print_history(char **input2, int(*count_of_history), char **history, char *homedirectory, char *previous_directory,char *copy_of_input);

// void proclore(char **input2);
void save_history(char **input2,int count,int *count_of_history,char **history,char *history_file_path);
void load_history(int *count_of_history,char **history,char *history_file_path);
void executeprocess(char *input2,char *homedirectory,char *previous_directory,char *copy_of_input,int *count_of_history,char **history,Process *processid,int *numberofprocessids);

void seek_command(char ** input2,char *homedirectory,char *previous_directory);
void input_output(char *stringafterparsing,char* homedirectory,char *previousdirectory);
void executepiping(char *input);
void executepipingwithIO(char *input);
void activities(Process *processids,int *countofprocess);
void iman(char **input);
void ping(char **input);
void executefgbg(char **input);
void neonate(char **input);


#define ANSI_COLOR_GREEN   "\x1b[32m"  
#define ANSI_COLOR_WHITE   "\x1b[0m"  
#define ANSI_COLOR_BLUE    "\x1b[34m"  
#define ANSI_COLOR_RESET   "\x1b[0m"

// void warp();

#endif