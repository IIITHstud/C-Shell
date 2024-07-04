#include "headers.h"
#include "prompt.h"


void prompt(char *homedirectory) {
    // Do not hardcode the prompt
    // printf("S");
     uid_t uid = getuid();
    
    // Use the getpwuid function to get user information by UID
    struct passwd *pw = getpwuid(uid);
    // char *user = getenv("USER");
    struct utsname systeminfo;
    int a = uname(&systeminfo);
    // uname(sty)
    char directory[100];
    getcwd(directory, sizeof(directory));

 if (strncmp(directory, homedirectory, strlen(homedirectory)) == 0) {
        char relativedirectory[100];
        snprintf(relativedirectory, sizeof(relativedirectory), "~%s", directory + strlen(homedirectory));
        printf("<" ANSI_COLOR_GREEN "%s@" ANSI_COLOR_RESET ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET ">", pw->pw_name, systeminfo.nodename, relativedirectory);
    } else {
        printf("<" ANSI_COLOR_GREEN "%s@" ANSI_COLOR_RESET ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET ">", pw->pw_name, systeminfo.nodename, directory);
    }
}
