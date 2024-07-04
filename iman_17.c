#include "headers.h"

#include "prompt.h"

#define MAX_BUFFER_SIZE 4096

void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void stripHTMLTags(char *str)
{
    int insideTag = 0;
    int j = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '<')
        {
            insideTag = 1;
            continue;
        }
        if (insideTag)
        {
            if (str[i] == '>')
            {
                insideTag = 0;
            }
            continue;
        }
        str[j++] = str[i];
    }
    str[j] = '\0';
}

void iman(char **input)
{
    //     fprintf(stderr, "Usage: %s <command_name>\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }

    char *command_name = input[1];

    //here we have done DNA resolution (converted website name into ip address which is actually stored
    //in server which is a hostent struct)
    //Step-1:DNS resolution
    struct hostent *server = gethostbyname("man.he.net");
    if (server == NULL)
    {
        error("Error in DNS resolution");
    }

    //on success it returns a +ve value
    //on failure it returns -1
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);//creating a TCP socket
    if (sockfd < 0)
    {
        error("Error opening socket");
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);

    // Step-2: TCP socket establishing connecting with the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        error("Error connecting to server");
    }


    //Step-3:Sends the HTTP GET request for a specific topic to the server
    char request[MAX_BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET http://man.he.net/?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);
    
    //printf("%s\n",request);

    //Step-4:Read n write all the data from the server to the socket file desciptor
    if (write(sockfd, request, strlen(request)) < 0)
    {
        // error("Error writing to socket");
        printf("No manpagefound");
        return;
    }

    char buffer[1024];
    char line[1024];
    int n;
    int start = 0;

    int lineLength = 0;
    int bytesRead;
    int foundmanpage = 0;
    //All the data is in sockfd file desciptor n we are reading specified no of bytes each time
    //which is 1024 the size of buffer n it return the no of bytesRead n if it is 0 or -ve loop will break

    //Step-5: Printing the data available in socket file desciptor
    while ((bytesRead = read(sockfd, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < bytesRead; i++)
        {
            if (buffer[i] == '\n')
            {
                line[lineLength] = '\0';
                //here we are setting start=1 once if we get first line to be NAME it means/
                //this page exists otherwise this page does not exit n start will be same 0
                //so later if start==0,we will print NO suck command
                if (strncmp(line, "NAME", 4) == 0)
                {
                    start = 1;
                }
                if (start == 1)
                {
                    stripHTMLTags(line);
                    printf("%s\n", line);
                }
                // if(strncmp(line,"Search Again",12)==0){
                //     foundmanpage=1;
                //     break;
                // }
                lineLength = 0;
            }
            else if (lineLength < 1000)
            {
                line[lineLength++] = buffer[i];
            }
        }
    }
    if (start == 0)
    {
        printf("No such command\n");
        return;
    }

    if (n < 0)
    {
        error("Error reading from socket");
    }

    // Step 7: Close the socket
    close(sockfd);
}
