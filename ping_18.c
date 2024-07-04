#include "headers.h"
#include "prompt.h"


void ping(char **input){
    int count=0;
    while(input[count]!=NULL){
        count++;
    }
    if(count<2){
        printf("Not a valid ping command\n");
        return;
    }
int processid=atoi(input[1]);
int signal=(atoi(input[2]))%32;

if(kill(processid,0)==-1){
    printf("No such process found\n");
}
else{
    if(kill(processid,signal)==-1){

    printf("error in signal");
    }

}




}