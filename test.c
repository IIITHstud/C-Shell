#include <stdio.h>
#include <dirent.h>

int main()
{
    DIR *directory;
    struct dirent *entry;

    directory = opendir("/home");
    if (directory != NULL)
    {
        while ((entry = readdir(directory)) != NULL)
        {
            printf("%s\n", entry->d_name);
        }
        closedir(directory);
    }
    else
    {
        perror("Error opening directory");
        return 1;
    }
    return 0;
}
