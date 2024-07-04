# Description
This is a basic terminal built in C Programming language as a part of Operating System and network course. It offer users a simple
yet functional terminal experience like changing directory, listing files , pastevnets etc. Color coding has also been done for the files and directories to distinguish between them. More commands would be added till final submissions


# Assumptions
1. A history.txt file is present
2. Pastevents commands are not stored in the text file 
3. System calls like cd, ls~ are not given as input because excevp does not take them as system call
4. In peek command I have assumed that the hidden files will be at the top and no files will start with a special character
5. Not more than 3 arguments will be given in peek command
6. If a command takes more than 2 seconds other than the commands implemented by ourselves, than that command will be displayed
along with its time taken in the next line after enter instead of displaying it in prompt
7.  If -e flag is enabled but the directory does not have access permission (execute) or file does not have read permission, then no output is printed.
8. Excessive edge cases has been handled but it may be possible that some of the cases might not work but i will make sure it will be handled in the final commit of the project.

