#include "headers.h"
#include "prompt.h"



void load_history(int *count_of_history,char **history,char *history_file_path) {
    // printf("%d",*count_of_history);
    FILE* file=fopen(history_file_path,"r");
     if (file == NULL) {
        return;     
    }

    char line[1000];
    while (*count_of_history < 15 && fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        history[*count_of_history] = strdup(line);
        (*count_of_history)++;
    }
 
    fclose(file);

     }

