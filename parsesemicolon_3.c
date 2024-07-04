#include "headers.h"
#include "prompt.h"


int parsesemicolon(char *input2,char **arguments) {
// printf("%s",input200);

int count=0;
// char *arguments[1000];
// int i=0;
for(int i=0;i<MAXARGUMENTS;i++){
    arguments[i]=strsep(&input2,";");
    if(arguments[i]==NULL){
        break;
    }
    count++;
    
}

return count;
   
    // return;
}

