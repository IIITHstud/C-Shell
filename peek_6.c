#include "headers.h"
#include "prompt.h"

int compare_strings(const void *a, const void *b)
{
  return strcmp(*(const char **)a, *(const char **)b);
}

void print_permissions(mode_t mode)
{
  char perms[] = "rwxrwxrwx";
  char type;

  if (S_ISDIR(mode))
  {
    type = 'd';
  }
  else
  {
    type = '-';
  }

  for (int i = 0; i < 9; i++)
  {
    if (!(mode & (1 << (8 - i))))
    {
      perms[i] = '-';
    }
  }

  printf("%c%s ", type, perms);
}

void executepeek(char **input2,char *homedirectory,char* previous_directory)
{
  
  int count = 0;
  while (input2[count] != NULL)
  {
    count++;
  }

  char *entries[1000];
  char directory[100];
  char new_directory[100];
      char new_home_directory[1000];

  getcwd(directory, sizeof(directory));
  strcpy(new_home_directory,homedirectory);
  
  DIR *dir;
  struct dirent *entry;

  if(count==1 || strcmp(input2[1],"~")==0){
   
       dir = opendir(homedirectory);
      //  printf("%s",homedirectory);
    if (dir == NULL)
    {
      printf("invalid");
      return;
    }
    

    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
      entries[i] = strdup(entry->d_name);
      strcpy(entries[i], entry->d_name);
      i++;
      // printf("%s\n",entry->d_name);
      qsort(entries, i, sizeof(char *), compare_strings);

    }


    // for(int =0;i<n;i++)+

    for (int count2 = 0; count2 < i; count2++)
    {
        if (entries[count2][0] == '.')
      {
        continue;
      }

      char full_path[10000];
      snprintf(full_path, sizeof(full_path), "%s/%s", homedirectory, entries[count2]);
      struct stat file_stat;
      if (stat(full_path, &file_stat) == -1)
      {
        perror("stat");
        continue;
      }
      if (S_ISDIR(file_stat.st_mode))
      {
        printf(ANSI_COLOR_BLUE);
      }
      else if (file_stat.st_mode & S_IXUSR)
      {
        printf(ANSI_COLOR_GREEN);
      }
      else
      {
        printf(ANSI_COLOR_WHITE);
      }

      printf("%s\n", entries[count2]);
      printf(ANSI_COLOR_RESET);
    }

return;
}

else if(strcmp(input2[1],"-")==0){
          dir = opendir(previous_directory);
      //  printf("%s",previous_directory);
    if (dir == NULL)
    {
      printf("invalid");
      return;
    }
    

    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
      entries[i] = strdup(entry->d_name);
      strcpy(entries[i], entry->d_name);
      i++;
      // printf("%s\n",entry->d_name);
      qsort(entries, i, sizeof(char *), compare_strings);

    }


    // for(int =0;i<n;i++)+

    for (int count2 = 0; count2 < i; count2++)
    {
      char full_path[10000];
      snprintf(full_path, sizeof(full_path), "%s/%s", previous_directory, entries[count2]);
      struct stat file_stat;
      if (stat(full_path, &file_stat) == -1)
      {
        perror("stat");
        continue;
      }
      if (S_ISDIR(file_stat.st_mode))
      {
        printf(ANSI_COLOR_BLUE);
      }
      else if (file_stat.st_mode & S_IXUSR)
      {
        printf(ANSI_COLOR_GREEN);
      }
      else
      {
        printf(ANSI_COLOR_WHITE);
      }

      printf("%s\n", entries[count2]);
      printf(ANSI_COLOR_RESET);
    }
return;

}



  if (strcmp(input2[1], "-a") == 0 && count == 3)
  {
     if(input2[2][0]=='~'){
    // printf("hello");
    memmove(input2[2],input2[2]+1,strlen(input2[2]));
strcat(new_home_directory,input2[2]);
strcpy(input2[2],new_home_directory);
// printf("%s",new_home_directory);

}

    dir = opendir(input2[2]);
    if (dir == NULL)
    {
      printf("invalid");
      return;
    }
    

    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
      entries[i] = strdup(entry->d_name);
      strcpy(entries[i], entry->d_name);
      i++;
      // printf("%s\n",entry->d_name);

      qsort(entries, i, sizeof(char *), compare_strings);
    }

    // for(int =0;i<n;i++)

    for (int count2 = 0; count2 < i; count2++)
    {
      //   if (entries[count2][0] == '.')
      // {
      //   continue;
      // }

      char full_path[10000];
      snprintf(full_path, sizeof(full_path), "%s/%s", input2[2], entries[count2]);
      struct stat file_stat;
      if (stat(full_path, &file_stat) == -1)
      {
        perror("stat");
        continue;
      }
      if (S_ISDIR(file_stat.st_mode))
      {
        printf(ANSI_COLOR_BLUE);
      }
      else if (file_stat.st_mode & S_IXUSR)
      {
        printf(ANSI_COLOR_GREEN);
      }
      else
      {
        printf(ANSI_COLOR_WHITE);
      }

      printf("%s\n", entries[count2]);
      printf(ANSI_COLOR_RESET);
    }
  }

  else if (strcmp(input2[1], "-l") == 0 && count == 3)
  {
         if(input2[2][0]=='~'){
    // printf("hello");
    memmove(input2[2],input2[2]+1,strlen(input2[2]));
strcat(new_home_directory,input2[2]);
strcpy(input2[2],new_home_directory);
// printf("%s",new_home_directory);

}
    dir = opendir(input2[2]);
    if (dir == NULL)
    {
      printf("invalid");
      return;
    }
 

    int i = 0;

    while ((entry = readdir(dir)) != NULL)
    {

      entries[i] = strdup(entry->d_name);
      strcpy(entries[i], entry->d_name);
      i++;
      // printf("%s\n",entry->d_name);
    }

    qsort(entries, i, sizeof(char *), compare_strings);
    // printf("%d",i);
    for (int k = 0; k < i; k++)
    {
      if (entries[k][0] == '.')
      {
        continue;
      }

      char full_path[10000];
      snprintf(full_path, sizeof(full_path), "%s/%s", input2[2], entries[k]);

      struct stat file_stat;
      if (stat(full_path, &file_stat) == -1)
      {
        perror("stat");
        continue;
      }

      print_permissions(file_stat.st_mode);
      printf("%2ld ", file_stat.st_nlink);

      struct passwd *pw = getpwuid(file_stat.st_uid);
      struct group *gr = getgrgid(file_stat.st_gid);
      printf("%s ", pw ? pw->pw_name : "unknown");
      printf("%s ", gr ? gr->gr_name : "unknown");
      printf("%ld ", (long)file_stat.st_size);

      // printf("Type: %s ", S_ISDIR(file_stat.st_mode) ? "Directory" : "File");
      struct tm *timeinfo = localtime(&file_stat.st_mtime);
      char time_str[80];
      strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);

      printf("%-12s ", time_str);

      // printf("Last Modified: %s\n", time_str);
      if (S_ISDIR(file_stat.st_mode))
      {
        printf(ANSI_COLOR_BLUE);
      }
      else if (file_stat.st_mode & S_IXUSR)
      {
        printf(ANSI_COLOR_GREEN);
      }
      else
      {
        printf(ANSI_COLOR_WHITE);
      }

      printf("%s ", entries[k]);
      printf(ANSI_COLOR_RESET);

      printf("\n");
    }
  }
  else if (count == 4)
  {
         if(input2[3][0]=='~'){
    // printf("hello");
    memmove(input2[3],input2[3]+1,strlen(input2[3]));
strcat(new_home_directory,input2[3]);
strcpy(input2[3],new_home_directory);
// printf("%s",new_home_directory);

}
    dir = opendir(input2[3]);
    if (dir == NULL)
    {
      printf("invalid");
      return;
    }

     

    int i = 0;

    while ((entry = readdir(dir)) != NULL)
    {

      entries[i] = strdup(entry->d_name);
      strcpy(entries[i], entry->d_name);
      i++;
      // printf("%s\n",entry->d_name);
    }

    qsort(entries, i, sizeof(char *), compare_strings);
    printf("%d", i);
    for (int k = 0; k < i; k++)
    {

      char full_path[10000];
      snprintf(full_path, sizeof(full_path), "%s/%s", input2[3], entries[k]);

      struct stat file_stat;
      if (stat(full_path, &file_stat) == -1)
      {
        perror("stat");
        continue;
      }

      print_permissions(file_stat.st_mode);
      printf("%2ld ", file_stat.st_nlink);

      struct passwd *pw = getpwuid(file_stat.st_uid);
      struct group *gr = getgrgid(file_stat.st_gid);
      printf("%s ", pw ? pw->pw_name : "unknown");
      printf("%s ", gr ? gr->gr_name : "unknown");
      printf("%ld ", (long)file_stat.st_size);

      // printf("Type: %s ", S_ISDIR(file_stat.st_mode) ? "Directory" : "File");
      struct tm *timeinfo = localtime(&file_stat.st_mtime);
      char time_str[80];
      strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);

      printf("%-12s ", time_str);

      // printf("Last Modified: %s\n", time_str);
      if (S_ISDIR(file_stat.st_mode))
      {
        printf(ANSI_COLOR_BLUE);
      }
      else if (file_stat.st_mode & S_IXUSR)
      {
        printf(ANSI_COLOR_GREEN);
      }
      else
      {
        printf(ANSI_COLOR_WHITE);
      }

      printf("%s ", entries[k]);
      printf(ANSI_COLOR_RESET);
      printf("\n");
    }
  }
  else if(strcmp(input2[1],"-al")==0 || strcmp(input2[1],"-la")==0)
  {
         if(input2[2][0]=='~'){
    // printf("hello");
    memmove(input2[2],input2[2]+1,strlen(input2[2]));
strcat(new_home_directory,input2[2]);
strcpy(input2[2],new_home_directory);
// printf("%s",new_home_directory);

}

    dir = opendir(input2[2]);
    if (dir == NULL)
    {
      printf("invalid");
      return;
    }
    

    int i = 0;

    while ((entry = readdir(dir)) != NULL)
    {

      entries[i] = strdup(entry->d_name);
      strcpy(entries[i], entry->d_name);
      i++;
      // printf("%s\n",entry->d_name);
    }

    qsort(entries, i, sizeof(char *), compare_strings);
    printf("%d", i);
    for (int k = 0; k < i; k++)
    {
      // if (entries[k][0] == '.') {
      //     continue;
      // }

      char full_path[10000];
      snprintf(full_path, sizeof(full_path), "%s/%s", input2[2], entries[k]);

      struct stat file_stat;
      if (stat(full_path, &file_stat) == -1)
      {
        perror("stat");
        continue;
      }

      print_permissions(file_stat.st_mode);
      printf("%2ld ", file_stat.st_nlink);

      struct passwd *pw = getpwuid(file_stat.st_uid);
      struct group *gr = getgrgid(file_stat.st_gid);
      printf("%s ", pw ? pw->pw_name : "unknown");
      printf("%s ", gr ? gr->gr_name : "unknown");
      printf("%ld ", (long)file_stat.st_size);

      // printf("Type: %s ", S_ISDIR(file_stat.st_mode) ? "Directory" : "File");
      struct tm *timeinfo = localtime(&file_stat.st_mtime);
      char time_str[80];
      strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);

      printf("%-12s ", time_str);

      // printf("Last Modified: %s\n", time_str);
      if (S_ISDIR(file_stat.st_mode))
      {
        printf(ANSI_COLOR_BLUE);
      }
      else if (file_stat.st_mode & S_IXUSR)
      {
        printf(ANSI_COLOR_GREEN);
      }
      else
      {
        printf(ANSI_COLOR_WHITE);
      }

      printf("%s ", entries[k]);
      printf(ANSI_COLOR_RESET);

      printf("\n");
    }
  }

  else{
         if(input2[1][0]=='~'){
    // printf("hello");
    memmove(input2[1],input2[1]+1,strlen(input2[1]));
strcat(new_home_directory,input2[1]);
strcpy(input2[1],new_home_directory);
// printf("%s",new_home_directory);

}

    dir = opendir(input2[1]);
    if (dir == NULL)
    {
      printf("invalid");
      return;
    }
    

    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
      entries[i] = strdup(entry->d_name);
      strcpy(entries[i], entry->d_name);
      i++;
      // printf("%s\n",entry->d_name);

      qsort(entries, i, sizeof(char *), compare_strings);
    }

    // for(int =0;i<n;i++)

    for (int count2 = 0; count2 < i; count2++)
    {
        if (entries[count2][0] == '.')
      {
        continue;
      }

      char full_path[10000];
      snprintf(full_path, sizeof(full_path), "%s/%s", input2[1], entries[count2]);
      struct stat file_stat;
      if (stat(full_path, &file_stat) == -1)
      {
        perror("stat");
        continue;
      }
      if (S_ISDIR(file_stat.st_mode))
      {
        printf(ANSI_COLOR_BLUE);
      }
      else if (file_stat.st_mode & S_IXUSR)
      {
        printf(ANSI_COLOR_GREEN);
      }
      else
      {
        printf(ANSI_COLOR_WHITE);
      }

      printf("%s\n", entries[count2]);
      printf(ANSI_COLOR_RESET);
    }


  }
  return;

}

// return;
// }
