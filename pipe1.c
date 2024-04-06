//Write a program to create a   named   pipe where child sends message to parent.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_NAME "my_named_pipe"

void parent(int fd) {
    char buffer[256];
    read(fd, buffer, sizeof(buffer));
    printf("Parent received message from child: %s\n", buffer);
}

void child(int fd) {
    char *message = "Hello Parent!";
    write(fd, message, strlen(message) + 1);
}

int main() {
    int fd;
    pid_t pid;

    mkfifo(FIFO_NAME, 0666);

    pid = fork();

    if (pid > 0) {
        fd = open(FIFO_NAME, O_RDONLY);
        parent(fd);
    } else if (pid == 0) {
        fd = open(FIFO_NAME, O_WRONLY);
        child(fd);
    }

    close(fd);
    unlink(FIFO_NAME);

    return 0;
}
