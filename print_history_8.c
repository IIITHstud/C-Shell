#include "headers.h"
#include "prompt.h"

//here input2 is the parsed argument
void print_history(char **input2, int(*count_of_history), char **history, char *homedirectory, char *previous_directory,char *copy_of_input)
{

  // (*count_of_history)++;
  int count = 0;
  while (input2[count] != NULL)
  {
    count++;
  }

  //if count==0 it means there is only pastevents command from the user
  //in that case we will directly going to print the array of strings(history)
  //otherwise there are other arguemts like purge or execute<index> thing for sure
  if (count > 1)
  {
    // In summary, this code snippet clears the content of each history entry, updates the history file by truncating it to zero length, 
    // and resets the count of history entries to zero. It effectively purges the history data and resets it to an empty state.
    if (strcmp(input2[1], "purge") == 0)
    {
      // printf("hello");
      for (int i = 0; i < (*count_of_history); i++)
      {
        history[i][0] = '\0';
        FILE *history_file = fopen("history.txt", "w");//Opening a file in write mode ("w") truncates the file 
                                                    //to zero length if it exists or creates a new empty file if it doesn't exist because otherwise
                                                    //it is going to open in the append mode if we want to append something to the previous content
        if (history_file != NULL)
        {
          fclose(history_file);
          // printf("History purged\n");
        }
        else
        {
          perror("Error purging history");
        }
      }
      *count_of_history = 0;
    }
    else if (strcmp(input2[1], "execute") == 0)
    {
      char *variable_input = malloc(sizeof(char) * 1000);
      int num = atoi(input2[2]);

      variable_input = strdup(history[*(count_of_history)-(num)]);//indexing from last
      // printf("%s\n",variable_input);

      char *parsedpipeargument[MAXARGUMENTS];

      for (int i = 0; i < MAXARGUMENTS; i++)
      {
        parsedpipeargument[i] = strsep(&variable_input, " \n\t");
        if (parsedpipeargument[i] == NULL)
        {
          break;
        }
        if (strlen(parsedpipeargument[i]) == 0)
        {
          i--;
        }
        count++;
      }
      int count = 0;
      while (parsedpipeargument[count] != NULL)
      {
        count++;
      }

      if (strcmp(parsedpipeargument[0], "warp") == 0)
      {
        char current_directory[1000];
        getcwd(current_directory, sizeof(current_directory));

        executewarp(parsedpipeargument, homedirectory, previous_directory);

        strcpy(previous_directory, current_directory);
      }

      else if (strcmp(parsedpipeargument[0], "peek") == 0)
      {
        executepeek(parsedpipeargument, homedirectory, previous_directory);
      }

      else if (strcmp(parsedpipeargument[0], "pastevents") == 0)
      {
        print_history(parsedpipeargument, count_of_history, history,homedirectory,previous_directory,copy_of_input);
      }

      else if (strcmp(parsedpipeargument[0], "proclore") == 0)
      {
        proclore(parsedpipeargument,homedirectory);
      }
      else if (strcmp(parsedpipeargument[0], "seek") == 0)
      {

        seek_command(parsedpipeargument,homedirectory,previous_directory);
      }
      else if (strcmp(parsedpipeargument[0], "echo") == 0)
      {
        printf("%s\n",parsedpipeargument[1]);
      }
      
    
    }
  }

else
{
  for (int i = 0; i < (*count_of_history); i++)
  {
    printf("%s\n", history[i]);
  }
}

}
