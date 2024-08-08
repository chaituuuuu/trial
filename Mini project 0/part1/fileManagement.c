#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/syscall.h>

int main()
{
    while (1)
    {
        printf("Enter a command:");
        char str[100];
        scanf("%s", str);
        char c;
        scanf("%c", &c);

        if (strcmp(str, "PRINT") == 0)
        {
            char buffer[5000];
            int os;
            int fd;
            int in = fileno(stdin);

            fd = open("newfile.txt", O_RDONLY | O_CREAT, 0644);
            if (fd < 0)
            {
                printf("Failed to open file");
                return 1;
            }

            os = dup(in);
            if (os < 0)
            {
                printf("Failed to duplicate stdin in os");
                close(fd);
                return 1;
            }
            int as = dup2(fd, in);

            if (as < 0)
            {
                printf("Failed to transfer stdin to file descriptor of file");
                close(fd);
                close(os);
                return 1;
            }

            close(fd);

            while (scanf("%4999[^\n]%*c", buffer) == 1)
            {

                printf("%s\n", buffer);
            }
           
            clearerr(stdin);
            int as2 = dup2(os, in);
            if (as2 < 0)
            {
                printf("Failed to restore stdin by transfering the dup file descriptor to stdin");
                close(os);
                return 1;
            }

            close(os);
            continue;
        }
        else if (strcmp(str, "STOP") == 0)
        {
            break;
        }
        else if (strcmp(str, "INPUT") == 0)
        {
            char buffer[5000];
            int osn;
            int fd;
            int flow = fileno(stdout);
            char trial[5000];
            strcpy(trial,buffer);
            
            printf("Enter your message: ");
            scanf("%[^\n]", buffer);
            if(strcmp(buffer,trial)==0)
            {
                printf("enter a valid string\n");
                continue;
            }
            strcat(buffer, "\n");
            fd = open("newfile.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                printf("Failed to open file");
                return 1;
            }

            osn = dup(flow);
            if (osn < 0)
            {
                printf("failed to duplicate stdout in variable osn");
                return 1;
            }
            int as3 = dup2(fd, flow);
            if (as3 < 0)
            {
                printf("failed to transfer the file descriptor of file(fd) in  in stdout");
                return 1;
            }

            close(fd);

            printf("%s", buffer);
           
            int as4 = dup2(osn, flow);
            if (as4 < 0)
            {
                printf("Failed to restore stdout by transfering the dup file descriptor to stdout");
                return 1;
            }

            close(osn);
        }
        else
        {
            printf("enter a valid command\n");
        }
    }

    return 0;
}
