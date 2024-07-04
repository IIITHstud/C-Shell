#ifndef HEADERS_H_
#define HEADERS_H_
#define MAXARGUMENTS 100
#define HISTORY_FILE "history.txt"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <ncurses.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <termios.h>

extern int foregroundprocessid;
typedef struct Process{
        int pid;
        char processname[1000];
    }Process;

#include "prompt.h"


#endif