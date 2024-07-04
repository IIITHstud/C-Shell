#include "headers.h"
#include "prompt.h"
// extern int count_of_history_1;
// count_of_history_1=0;

void parsespace(char *input2,char ** stringsafterpartsing,int v,int *count_of_history,char **history,char *history_file_path,char *homedirectory,char *previous_directory,char *copy_of_input,Process *processids,int *countofprocessids) {


int count=0;
char *parsedpipeargument[MAXARGUMENTS];
//parsedpipeargument is seperating on the basis of space
char *copyofstringsafterparsing=strdup(input2);

for(int i=0;i<MAXARGUMENTS;i++){
    parsedpipeargument[i]=strsep(&input2," \n\t");
    if(parsedpipeargument[i]==NULL){
        break;
    }
    if(strlen(parsedpipeargument[i])==0){
        i--;
    }
    count++;

}




// printf("%s",parsedpipeargument[0]);
// char *history[16];

if(strcmp(parsedpipeargument[0],"warp")==0){
    char current_directory[1000];
    getcwd(current_directory,sizeof(current_directory));
    
executewarp(parsedpipeargument,homedirectory,previous_directory);

add_to_history(stringsafterpartsing,v,count_of_history,history);

save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);
strcpy(previous_directory,current_directory);


}

else if(strcmp(parsedpipeargument[0],"peek")==0){
    // printf("hello");
executepeek(parsedpipeargument,homedirectory,previous_directory);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);


}


else if(strcmp(parsedpipeargument[0],"pastevents")==0){
// add_to_history(stringsafterpartsing,v);
print_history(parsedpipeargument,count_of_history,history,homedirectory,previous_directory,copy_of_input);

}

else if(strcmp(parsedpipeargument[0],"proclore")==0){
// add_to_history(stringsafterpartsing,v);
proclore(parsedpipeargument,homedirectory);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);

}
else if(strcmp(parsedpipeargument[0],"seek")==0){

seek_command(parsedpipeargument,homedirectory,previous_directory);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);

}
else if((strstr(copyofstringsafterparsing,">>")!=NULL || strchr(copyofstringsafterparsing,'>')!=NULL || strchr(copyofstringsafterparsing,'<')!=NULL)&&strstr(copyofstringsafterparsing,"|")!=NULL){
    executepipingwithIO(copyofstringsafterparsing);
    add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);
}

else if(strstr(copyofstringsafterparsing,">>")!=NULL || strchr(copyofstringsafterparsing,'>')!=NULL || strchr(copyofstringsafterparsing,'<')!=NULL){
    input_output(copyofstringsafterparsing,homedirectory,previous_directory);
    add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);
}
else if(strstr(copyofstringsafterparsing,"|")!=NULL){
executepiping(copyofstringsafterparsing);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);

}
else if(strcmp(parsedpipeargument[0],"activities")==0){
    // printf("hello");
    activities(processids,countofprocessids);
}
else if(strcmp(parsedpipeargument[0],"iMan")==0){
    // printf("hello");
    iman(parsedpipeargument);
    // activities(processids,countofprocessids);
}
else if(strcmp(parsedpipeargument[0],"ping")==0){
    // printf("hello");
    ping(parsedpipeargument);
    // activities(processids,countofprocessids);
}
else if(strcmp(parsedpipeargument[0],"fg")==0 || strcmp(parsedpipeargument[0],"bg")==0){
    // printf("hello");
    executefgbg(parsedpipeargument);
}
else if(strcmp(parsedpipeargument[0],"neonate")==0){

    neonate(parsedpipeargument);
    
}
else{
    executeprocess(copy_of_input,homedirectory,previous_directory,copy_of_input,count_of_history,history,processids,countofprocessids);
    add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);

}

// for(int k=0;k<*countofprocessids;k++){
// printf("%d",processids[k]);
// }
   
    // return;
}

