#include "headers.h"
#include "prompt.h"

//add to history
void add_to_history(char **input2,int count,int *count_of_history,char **history) {
    // printf("%d",*count_of_history);
    if((*count_of_history)<15){
        
        //input2 is the after parsing semicolon so input2[0] is the one complete command
        //so input[count] is the one complete command
        if((*count_of_history)==0 || strcmp(history[*count_of_history - 1], input2[count]) != 0){
        history[(*count_of_history)]=strdup(input2[count]);//strdup dynamically allocate memory for the string and it return a pointer to the string
                                                           //and history is the array to pointer to strings 
            (*count_of_history)++;


        }

    }
        else{
            

            if(strcmp(history[14],input2[count])!=0){
            for(int i=0;i<14;i++){
          strcpy(history[i],history[i+1]);
            }
  strcpy(history[14],input2[count]);
            } 
        }
    }


