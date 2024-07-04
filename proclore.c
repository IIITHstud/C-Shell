#include "headers.h"

#include "prompt.h"

#define BUFFER_SIZE 1000


void proclore(char **input2,char *homedirectory){
  int count = 0;
  while (input2[count] != NULL)
  {
    count++;
  }
  if(count==1){

    pid_t pid=getpid();

    
// int n=getpgrp();
// printf("%d",n);
char path[BUFFER_SIZE];
char buffer[BUFFER_SIZE];
char linkname[BUFFER_SIZE];

    snprintf(buffer, sizeof(buffer), "/proc/%d/status", pid);
      snprintf(linkname, sizeof(linkname), "/proc/%d/exe", pid);
      ssize_t len = readlink(linkname, path, sizeof(path) - 1);
      path[len]='\0';
    FILE *fp = fopen(buffer, "r");

       


 char line[BUFFER_SIZE];
    char process_name[BUFFER_SIZE];
    char process_status[BUFFER_SIZE];
    char group_id[BUFFER_SIZE];
    char vmsize[BUFFER_SIZE];

//  int process_group;
//  int group_id;
    while (fgets(line, sizeof(line), fp) != NULL) {

        if (strncmp(line, "Name:", 5) == 0) {

            sscanf(line + 5, "%s", process_name);

        }
        if (strncmp(line, "State:", 6) == 0) {

            sscanf(line + 6, "%s", process_status);


        }
 if (strncmp(line, "NSpgid:", 7) == 0) {


            sscanf(line + 7, "%s", group_id);

        }
 if (strncmp(line, "VmSize:", 7) == 0) {

            sscanf(line + 7, "%s", vmsize);
        }

        // sscanf(line, "%*d %*s %*c %d", &process_group);

}

//   char line[BUFFER_SIZE];
    // if (fgets(line, sizeof(line), fp) != NULL) {
    //     // The process group ID is the fourth field in the /proc/<pid>/stat file
       
    // }



printf("pid : %d\n",pid );


printf("process status : %s\n",process_status);
        printf("Process Group: %s\n", group_id);
        printf("Virtual memory: %s\n", vmsize);
        if (strncmp(path, homedirectory, strlen(homedirectory)) == 0)
            {
                char relativedirectory[100];
                snprintf(relativedirectory, sizeof(relativedirectory), "~%s", path + strlen(homedirectory));
                printf("Executable path : %s\n", relativedirectory);
            }
            else
            {
                printf("Executable path : %s\n", path);
            }

  }

  else{
char path[BUFFER_SIZE];
char buffer[BUFFER_SIZE];
char linkname[BUFFER_SIZE];
int pid=atoi(input2[1]);

    snprintf(buffer, sizeof(buffer), "/proc/%d/status", pid);
      snprintf(linkname, sizeof(linkname), "/proc/%d/exe", pid);
      ssize_t len = readlink(linkname, path, sizeof(path) - 1);
      path[len]='\0';
    FILE *fp = fopen(buffer, "r");
    if(fp==NULL){
        return;
    }

       


 char line[BUFFER_SIZE];
    char process_name[BUFFER_SIZE];
    char process_status[BUFFER_SIZE];
    char group_id[BUFFER_SIZE];
    char vmsize[BUFFER_SIZE];

//  int process_group;
//  int group_id;
    while (fgets(line, sizeof(line), fp) != NULL) {

        if (strncmp(line, "Name:", 5) == 0) {

            sscanf(line + 5, "%s", process_name);

        }
        if (strncmp(line, "State:", 6) == 0) {

            sscanf(line + 6, "%s", process_status);


        }
 if (strncmp(line, "NSpgid:", 7) == 0) {


            sscanf(line + 7, "%s", group_id);

        }
 if (strncmp(line, "VmSize:", 7) == 0) {

            sscanf(line + 7, "%s", vmsize);
        }

        // sscanf(line, "%*d %*s %*c %d", &process_group);

}

//   char line[BUFFER_SIZE];
    // if (fgets(line, sizeof(line), fp) != NULL) {
    //     // The process group ID is the fourth field in the /proc/<pid>/stat file
       
    // }



printf("pid : %d\n",pid );


printf("process status : %s\n",process_status);
        printf("Process Group: %s\n", group_id);
        printf("Virtual memory: %s\n", vmsize);
        if (strncmp(path, homedirectory, strlen(homedirectory)) == 0)
            {
                char relativedirectory[100];
                snprintf(relativedirectory, sizeof(relativedirectory), "~%s", path + strlen(homedirectory));
                printf("Executable path : %s\n", relativedirectory);
            }
            else
            {
                printf("Executable path : %s\n", path);
            }

  }
}

