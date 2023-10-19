#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "Use: mycat namefile.\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 1)
    {
        char buffer[1024];
        ssize_t bytes_read;

        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
        {
            if (bytes_read == -1)
            {
                perror("Error in read");
                exit(EXIT_FAILURE);
            }
            if (write(STDOUT_FILENO, buffer, bytes_read) == -1)
            {
                perror("Error in write");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        const char *namefile = argv[1];
        int fd = open(namefile, O_RDONLY);

        if (fd == -1)
        {
            perror("Error in open");
            exit(EXIT_FAILURE);
        }

        char buffer[1024];
        ssize_t bytes_read;

        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
        {
            if (bytes_read == -1)
            {
                perror("Error in read");
                close(fd);
                exit(EXIT_FAILURE);
            }
            if (write(STDOUT_FILENO, buffer, bytes_read) == -1)
            {
                perror("Error in write");
                close(fd);
                exit(EXIT_FAILURE);
            }
        }

        if (bytes_read == -1)
        {
            perror("Error in read");
            close(fd);
            exit(EXIT_FAILURE);
        }

        close(fd);
    }

    exit(EXIT_SUCCESS);
}
