#include "headers.h"
#include "prompt.h"

//The function returns a dynamically allocated string containing the full path of the directory or file found, or NULL if no match is found.
char *directoryforpath(char *target_directory, char *word, int flagd, int flagf)
{
    // printf("%s\n",word);
    DIR *directory;
    struct dirent *entry;
    if ((directory = opendir(target_directory)) == NULL)
    {
        printf("No match found");
    }
    int flag = 0;
    while ((entry = readdir(directory)) != NULL)//entry contains all the file names in that directory
    {

        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
        {
            continue;
        }

        char *fullpath = malloc(sizeof(char) * 1000);

        strcpy(fullpath, target_directory);

        strcat(fullpath, "/");//So, the purpose of concatenating the forward slash / is to properly separate the directory path from the filename,
                            // ensuring that the resulting path is correctly formatted.

        strcat(fullpath, entry->d_name);
        // printf("%s\n",fullpath);
        struct stat STAT;
        if (stat(fullpath, &STAT) < 0)
        {
            continue;
        }

        if (S_ISDIR(STAT.st_mode))//checking if its a directory because then we can make recurssive call for that
        {
            // printf("%s %s\n",entry->d_name,fullpath);
            if (strcmp(entry->d_name, word) == 0 && flagf == 0)
            {
                return fullpath;
            }
            //Now there are 2 cases 
            //1)flagf is 1 so we need to recurrsively search in fullpath direcctory for files not directory
            //2)name is not matching then also we need to search recurrsively in fullpath directory

            return directoryforpath(fullpath, word, flagd, flagf);
        }

        //its a regular file and flagd is also zero that means we was searching  for this only
        if (S_ISREG(STAT.st_mode) && flagd == 0)
        {
            printf("%s %s\n", entry->d_name, fullpath);
            if (strstr(entry->d_name, word) != NULL)
            {
                // printf("garvitjhukta\n");
                return fullpath;
            }
        }
    }
}

void seek_recursion_flag_with_f(char *target_directory, char *word, char *relativepath, int flagd, int flagf, int flage, int *count)
{

    DIR *directory;

    struct dirent *entry;

    if ((directory = opendir(target_directory)) == NULL)
    {
        printf("No match found");
        return;
    }
    // int count = 0;
    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
        {
            continue;
        }

        char fullpath[10000];
        strcpy(fullpath, target_directory);
        strcat(fullpath, "/");
        strcat(fullpath, entry->d_name);

        char newrelativepath[1000];
        snprintf(newrelativepath, sizeof(newrelativepath), "%s/%s", relativepath, entry->d_name);
        struct stat STAT;
        if (stat(fullpath, &STAT) < 0)
        {
            continue;
        }
        if (S_ISDIR(STAT.st_mode))
        {
            if (strcmp(entry->d_name, word) == 0 && flagf == 0)
            {
                // flag=1;
                (*count)++;
                // printf("%s\n",newrelativepath);
            }
            seek_recursion_flag_with_f(fullpath, word, newrelativepath, flagd, flagf, flage, count);
        }
        else if (S_ISREG(STAT.st_mode) && flagd == 0)
        {
            if (strncmp(entry->d_name, word, strlen(word)) == 0 && entry->d_name[strlen(word)] == '.')
            {
                FILE *file = fopen(fullpath, "r");
                if (file == NULL)
                {
                    perror("Error opening file");
                    return;
                }

                char buffer[1024];
                while (fgets(buffer, sizeof(buffer), file) != NULL)
                {
                    printf("%s", buffer);
                }

                fclose(file);
                // printf("%s",fullpath);
                return;
                // (*count)++;
            }
        }
    }
    // if (count == 0)
    // {
    //     printf("No match found");
    // }
    return;
}

void seek_recursion_flag_with_e(char *target_directory, char *word, char *relativepath, int flagd, int flagf, int flage, int *count)
{

    DIR *directory;

    struct dirent *entry;

    if ((directory = opendir(target_directory)) == NULL)
    {
        printf("No match found");
        return;
    }
    // int count = 0;
    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
        {
            continue;
        }

        char fullpath[10000];
        strcpy(fullpath, target_directory);
        strcat(fullpath, "/");
        strcat(fullpath, entry->d_name);

        char newrelativepath[1000];
        snprintf(newrelativepath, sizeof(newrelativepath), "%s/%s", relativepath, entry->d_name);
        struct stat STAT;
        if (stat(fullpath, &STAT) < 0)
        {
            continue;
        }
        if (S_ISDIR(STAT.st_mode))
        {
            if (strcmp(entry->d_name, word) == 0 && flagf == 0)

            {
                // flag=1;
                (*count)++;
                // printf("%s\n",newrelativepath);
            }
            seek_recursion_flag_with_e(fullpath, word, newrelativepath, flagd, flagf, flage, count);
        }
        else if (S_ISREG(STAT.st_mode) && flagd == 0)
        {
            if (strncmp(entry->d_name, word, strlen(word)) == 0 && entry->d_name[strlen(word)] == '.')

            {
                (*count)++;
            }
        }
    }
    // if (count == 0)
    // {
    //     printf("No match found");
    // }
    return;
}

void seek_recursion_flag(char *target_directory, char *word, char *relativepath, int flagd, int flagf, int flage, int *flag)
{

    DIR *directory;
    //  int count = 0;
    struct dirent *entry;

    if ((directory = opendir(target_directory)) == NULL)
    {
        printf("No match found");
        return;
    }
    // int flag = 0;
    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
        {
            continue;
        }

        char fullpath[10000];
        strcpy(fullpath, target_directory);
        strcat(fullpath, "/");
        strcat(fullpath, entry->d_name);

        char newrelativepath[1000];
        snprintf(newrelativepath, sizeof(newrelativepath), "%s/%s", relativepath, entry->d_name);
        struct stat STAT;
        if (stat(fullpath, &STAT) < 0)
        {
            continue;
        }
        if (S_ISDIR(STAT.st_mode))
        {
            if (strcmp(entry->d_name, word) == 0 && flagf == 0)

            {
                *flag = 1;
                printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\n", newrelativepath);
            }
            // int flag=0;
            seek_recursion_flag(fullpath, word, newrelativepath, flagd, flagf, flage, flag);
        }
        else if (S_ISREG(STAT.st_mode) && flagd == 0)
        {
            if (strncmp(entry->d_name, word, strlen(word)) == 0 && entry->d_name[strlen(word)] == '.')

            {
                *flag = 2;
                printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, newrelativepath);
            }
        }
    }
}

void seek_recursion(char *target_directory, char *word, char *relativepath, int *flag, char *homedirectory, char *previous_directory)
{

    DIR *directory;
    struct dirent *entry;

    if ((directory = opendir(target_directory)) == NULL)
    {
        printf("No match found\n");
        return;
    }
    // int flag = 0;
    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
        {
            continue;
        }

        char fullpath[10000];
        strcpy(fullpath, target_directory);
        strcat(fullpath, "/");
        strcat(fullpath, entry->d_name);

        char newrelativepath[1000];
        snprintf(newrelativepath, sizeof(newrelativepath), "%s/%s", relativepath, entry->d_name);
        struct stat STAT;
        if (stat(fullpath, &STAT) < 0)
        {

            continue;
        }
        if (S_ISDIR(STAT.st_mode))
        {
            if (strcmp(entry->d_name, word) == 0)

            {
                *flag = 1;
                printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, newrelativepath);
            }
            seek_recursion(fullpath, word, newrelativepath, flag, homedirectory, previous_directory);
        }

        else if (S_ISREG(STAT.st_mode))
        {
            if (strncmp(entry->d_name, word, strlen(word)) == 0 && entry->d_name[strlen(word)] == '.')

            {
                *flag = 2;
                printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, newrelativepath);
            }
        }
    }
}

void seek_command(char **input2, char *homedirectory, char *previous_directory)
{
    char new_home_directory[100];
    strcpy(new_home_directory, homedirectory);

    int count = 0;
    while (input2[count] != NULL)
    {
        count++;
    }

    char *relativepath = ".";

    if (count == 3)
    {
        if (strcmp(input2[1], "-d") != 0 && strcmp(input2[1], "-f") != 0 && strcmp(input2[1], "-e") != 0)
        {
            if (input2[2][0] == '~')
            {
                memmove(input2[2], input2[2] + 1, strlen(input2[2]));
                strcat(new_home_directory, input2[2]);
                strcpy(input2[2], new_home_directory);
            }
            if (input2[2][0] == '-')
            {
                strcpy(input2[2], previous_directory);
            }
            int flag = 0;
            seek_recursion(input2[2], input2[1], relativepath, &flag, homedirectory, previous_directory);
            if (flag == 0)
            {
                printf("No match found!\n");
            }
            // printf("%d",flag);
        }

        else
        {
            if (strcmp(input2[1], "-d") == 0)
            {
                int flag = 0;
                seek_recursion_flag(relativepath, input2[2], relativepath, 1, 0, 0, &flag);
                if (flag == 0)
                {
                    printf("No match found\n");
                }
            }
            if (strcmp(input2[1], "-f") == 0)
            {

                int flag = 0;
                seek_recursion_flag(relativepath, input2[2], relativepath, 0, 1, 0, &flag);
                if (flag == 0)
                {
                    printf("No match found\n");
                }
            }

            if (strcmp(input2[1], "-e") == 0)
            {
                int flag = 0;
                printf("invalid flag");
                // seek_recursion_flag(relativepath,input2[2],relativepath,0,0,1);
            }
        }
    }
    else if (count == 2)
    {
        char *target_directory = ".";
        int flag = 0;
        seek_recursion(target_directory, input2[1], relativepath, &flag, homedirectory, previous_directory);
        if (flag == 0)
        {
            printf("No match found!\n");
        }
    }

    else if (count == 4)
    {
        if (strcmp(input2[1], "-d") == 0 && strcmp(input2[2], "-f") != 0 && strcmp(input2[2], "-e") != 0)
        {
            if (input2[3][0] == '~')
            {
                memmove(input2[3], input2[3] + 1, strlen(input2[3]));
                strcat(new_home_directory, input2[2]);
                strcpy(input2[3], new_home_directory);
            }
            if (input2[3][0] == '-')
            {
                strcpy(input2[3], previous_directory);
            }
            int flag = 0;
            seek_recursion_flag(input2[3], input2[2], relativepath, 1, 0, 0, &flag);
            if (flag == 0)
            {
                printf("No match found!\n");
            }
        }

        else if (strcmp(input2[1], "-f") == 0 && strcmp(input2[2], "-d") != 0 && strcmp(input2[2], "-e") != 0)
        {
            if (input2[3][0] == '~')
            {
                memmove(input2[3], input2[3] + 1, strlen(input2[3]));
                strcat(new_home_directory, input2[2]);
                strcpy(input2[3], new_home_directory);
            }
            if (input2[3][0] == '-')
            {
                strcpy(input2[3], previous_directory);
            }
            int flag = 0;
            seek_recursion_flag(input2[3], input2[2], relativepath, 0, 1, 0, &flag);
            if (flag == 0)
            {
                printf("No match found!\n");
            }
        }
        else if ((strcmp(input2[1], "-d") == 0 && strcmp(input2[2], "-e") == 0) || (strcmp(input2[2], "-d") == 0 && strcmp(input2[1], "-e") == 0))
        {

            int countarguments = 0;
            //  printf("hello");
            char *newrelativepath = ".";

            seek_recursion_flag_with_e(relativepath, input2[3], relativepath, 1, 0, 0, &countarguments);
            // printf("%d",count);
            if (countarguments == 1)
            {
                char *newdirectory = directoryforpath(newrelativepath, input2[3], 1, 0);
                // char * newdirectory="hello";
                printf("%s\n", newdirectory);
                // printf("he;;");
                chdir(newdirectory);
            }
            else
            {
                int flag = 0;
                seek_recursion_flag(newrelativepath, input2[3], relativepath, 1, 0, 0, &flag);
                if (flag == 0)
                {
                    printf("No match found!\n");
                }
            }
        }

        else if ((strcmp(input2[1], "-f") == 0 && strcmp(input2[2], "-e") == 0) || (strcmp(input2[1], "-e") == 0 && strcmp(input2[2], "-f") == 0))
        {

            int countarguments = 0;
            //  printf("hello");
            char *newrelativepath = ".";

            seek_recursion_flag_with_e(newrelativepath, input2[3], relativepath, 0, 1, 0, &countarguments);
            if (countarguments == 1)
            {
                seek_recursion_flag_with_f(newrelativepath, input2[3], relativepath, 0, 1, 0, &countarguments);
            }
            else
            {
                int flag = 0;
                seek_recursion_flag(relativepath, input2[3], relativepath, 0, 1, 0, &flag);
                if (flag == 0)
                {
                    printf("No match found\n");
                }
            }
            // printf("%d",countarguments);
        }
        else{
            printf("invalid flags");
        }
    }
    // printf("hello");
    else if (count == 5)
    {
        if (input2[4][0] == '~')
        {
            memmove(input2[4], input2[4] + 1, strlen(input2[4]));
            strcat(new_home_directory, input2[2]);
            strcpy(input2[4], new_home_directory);
        }
        if (input2[4][0] == '-')
        {
            strcpy(input2[4], previous_directory);
        }

        if ((strcmp(input2[1], "-d") == 0 && strcmp(input2[2], "-e") == 0) || (strcmp(input2[1], "-e") == 0 && strcmp(input2[2], "-d") == 0))
        {

            int count = 0;
            seek_recursion_flag_with_e(input2[4], input2[3], relativepath, 1, 0, 0, &count);

            if (count == 1)
            {
                // printf("%s\t%s\n",input2[4],input2[3]);
                char *newdirectory = directoryforpath(input2[4], input2[3], 1, 0);

                // if(newdirectory)
                printf("%s\n", newdirectory);
                chdir(newdirectory);
            }
            else
            {
                int flag = 0;
                seek_recursion_flag(input2[4], input2[3], relativepath, 1, 0, 0, &flag);
                if (flag == 0)
                {
                    printf("No match found!\n");
                }
            }
        }

        else if ((strcmp(input2[1], "-f") == 0 && strcmp(input2[2], "-e") == 0) || (strcmp(input2[1], "-e") == 0 && strcmp(input2[2], "-f") == 0))

        {

            int countarguments = 0;
            //  printf("hello");
            // char *newrelativepath = ".";

            seek_recursion_flag_with_e(input2[4], input2[3], relativepath, 0, 1, 0, &countarguments);
            if (countarguments == 1)
            {
                seek_recursion_flag_with_f(input2[4], input2[3], relativepath, 0, 1, 0, &countarguments);
            }
            else
            {
                int flag = 0;
                seek_recursion_flag(input2[4], input2[3], relativepath, 0, 1, 0, &flag);
                if (flag == 0)
                {
                    printf("No match found!\n");
                }
            }
        }
        else
        {
            printf("invalid flags\n");
        }
    }
}
