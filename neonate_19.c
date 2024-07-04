#include "headers.h"
#include "prompt.h"

void printpid()
{
    // /proc/sys/kernel/ns_last_pid stores the next PID to be assigned in Linux, ensuring unique process identifiers.
    FILE *file = fopen("/proc/sys/kernel/ns_last_pid", "r");
    if (file == NULL)
    {
        perror("Failed to open");
        return;
    }

    int latest_pid;//scaning n storing in latest_pid
    if (fscanf(file, "%d", &latest_pid) == 1)
    {
        printf("%d\n", latest_pid);
    }
    else
    {
        perror("Failed to read file");
    }

    fclose(file);
}

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios; // storing original terminal information so later we can restore that for correct functioning of that

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);            // automatically call this disbaleRawMode when program exists
    struct termios raw = orig_termios; // created a copy of that original terminal
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

int stopPrinting = 0;

void handleSignal(int signo)
{
    if (signo == SIGINT)
    {
        stopPrinting = 1;
    }
}

void neonate(char **input)
{
    int count = 0;
    while (input[count] != 0)
    {
        count++;
    }
    if (count < 3)
    {
        printf("invalid neonate command");
        return;
    }

    int interval = atoi(input[2]);

    if (interval <= 0)
    {
        printf("Invalid time interval\n");
        return;
    }

    enableRawMode();
    signal(SIGINT, handleSignal);//whenever SIGNINT(CTrl+C) get detected.....handleSingal will get automatically called
    // int i=(*countofprocessids)-1;

    pid_t pid = fork();
    if (pid < 0)
    {
        die("fork");
    }
    else if (pid == 0)//child prcess
    {
        while (!stopPrinting)//it will print pid jab tak stopprinting is not equal to 1
        {
            printpid();
            sleep(interval);
        }
        exit(0);//signifies successful termination 
    }

    else//parent process
    {

        char c; //The while (1) loop ensures that the program continuously listens for user input from the standard input stream.
                //Without this loop, the program would only read input once and then exit, 
                //which is not desirable for a program that needs to wait for user input until a specific condition is met.
        while (1)
        {
            read(STDIN_FILENO, &c, 1);
            if (c == 'x')
            {
                kill(pid, SIGINT);//we are printing pid periodically in child process so need to send SIGINT signal in child process
                                  //and pid is of child process os whenever we receive x...we can SIGINT signal to child process
                                  //because main task of printing we are doing there only

                wait(NULL);//Waiting for Child Process: After sending the SIGINT signal to the child process, the parent process needs to wait until the child process finishes executing.
                            //Synchronization between parent n child
                            //The NULL argument means that the parent process is not interested in retrieving the
                            //termination status of the child process. It's saying, "I don't need any information about why the child process terminated; I just want to wait until it's done."
                // }
                break;
            }
        }
    }
    disableRawMode();
}
