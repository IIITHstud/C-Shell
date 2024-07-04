 #include "headers.h"
#include "prompt.h"


//since input is an array of strings so double pointer since for warp there are be multiple commands at a single time
//Ex:warp .. - here in input there will be warp, .. , - , these three strings n we will implement it from left to right

//homedirectory n previous_directory are strings so char pointer
void executewarp(char  **input2, char *homedirectory, char *previous_directory)
{
    char new_directory[10000];
    char current_directory[1000];
    char new_home_directory[1000];

    getcwd(current_directory, sizeof(current_directory));
    strcpy(new_home_directory, homedirectory);

    // printf("%s\n",current_directory);

    //counting the number of strings in input2
    int count = 0;
    while (input2[count] != NULL)
    {
        count++; 
    }
    // printf("%d",count);
    uid_t uid = getuid();

    // Use the getpwuid function to get user information by UID
    struct passwd *pw = getpwuid(uid);

    
    //will start from string-1 since string-0 is warp only
    for (int i = 1; i < count; i++)
    {

        //count 1 means only warp is there no-other argument is given

        if (count == 1 || strcmp(input2[1], "~") == 0)
        {
            //   char *home_dir = getenv("HOME");
            chdir(homedirectory);
            getcwd(new_directory, sizeof(new_directory));

            if (strncmp(new_directory, homedirectory, strlen(homedirectory)) == 0)
            {
                char relativedirectory[100];
                snprintf(relativedirectory, sizeof(relativedirectory), "/home/%s%s", pw->pw_name, new_directory + strlen(homedirectory));
                printf("%s\n", relativedirectory);
            }

            return;
        }
        else if (strcmp(input2[i], "-") == 0)
        {
            chdir(previous_directory);

            if (strncmp(previous_directory, homedirectory, strlen(homedirectory)) == 0)
            {
                char relativedirectory[100];
                snprintf(relativedirectory, sizeof(relativedirectory), "/home/%s%s", pw->pw_name, previous_directory + strlen(homedirectory));
                printf("%s\n", relativedirectory);
            }
            else
            {
                printf("%s\n", previous_directory);
            }
        }

        else if (strcmp(input2[i], "..") == 0 || strcmp(input2[i], ".") == 0)
        {
            chdir(input2[i]);
            getcwd(new_directory, sizeof(new_directory));

            if (strncmp(new_directory, homedirectory, strlen(homedirectory)) == 0)
            {
                char relativedirectory[100];
                snprintf(relativedirectory, sizeof(relativedirectory), "/home/%s%s", pw->pw_name, new_directory + strlen(homedirectory));
                printf("%s\n", relativedirectory);
            }
            else
            {
                printf("%s\n", new_directory);
            }
            // printf("%s\n",new_directory);
        }

        else
        {

            char *path = (char *)malloc(sizeof(char) * (strlen(input2[1] + 1)));
            strcpy(path, input2[i]);

            if (input2[i][0] == '/')
            {
                // printf("hello");
                chdir(input2[i]);
                getcwd(new_directory, sizeof(new_directory));
                // printf("%s\n",new_directory);

                if (strncmp(new_directory, homedirectory, strlen(homedirectory)) == 0)
                {
                    char relativedirectory[100];
                    snprintf(relativedirectory, sizeof(relativedirectory), "/home/%s%s", pw->pw_name, new_directory + strlen(homedirectory));
                    printf("%s\n", relativedirectory);
                }
                else
                {
                    printf("%s\n", new_directory);
                }
            }
            else if (input2[i][0] == '~')
            {
                // printf("hello");
                memmove(input2[i], input2[i] + 1, strlen(input2[i]));
                strcat(new_home_directory, input2[i]);
                // printf("%s",new_home_directory);
                chdir(new_home_directory);
                if (strncmp(new_home_directory, homedirectory, strlen(homedirectory)) == 0)
                {
                    char relativedirectory[100];
                    snprintf(relativedirectory, sizeof(relativedirectory), "/home/%s%s", pw->pw_name, new_home_directory + strlen(homedirectory));
                    printf("%s\n", relativedirectory);
                }
            }
            else
            {

                char *path = (char *)malloc(sizeof(char) * (strlen(input2[i] + 1)));
                strcpy(path, input2[i]);

                char new_directory[10000];

                //  char *path="hello";

                char dash[10] = "/";

                strcat(current_directory, dash);
                strcat(current_directory, path);
                strcat(current_directory, dash);
                // printf("%s\n",current_directory);
                int l = chdir(current_directory);
                if(l<0){
                    printf("Not a valid directory\n");
                }
                else{


                if (strncmp(current_directory, homedirectory, strlen(homedirectory)) == 0)
                {
                    char relativedirectory[100];
                    snprintf(relativedirectory, sizeof(relativedirectory), "/home/%s%s", pw->pw_name, current_directory + strlen(homedirectory));
                    printf("%s\n", relativedirectory);
                }
                else
                {
                    printf("%s\n", current_directory);
                }
                }
            }

            // return;
        }
    }
}

// return;
