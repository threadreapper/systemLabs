#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char filename[] = "file.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("введите вот сюда вот текст:\n");
    char buffer[1024];
    ssize_t n;

    while ((n = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        if (write(fd, buffer, n) != n) {
            perror("write");
            close(fd);
            exit(1);
        }
    }

    close(fd); 
    printf("текст был успешно записан в %s\n", filename);
    return 0;
}
