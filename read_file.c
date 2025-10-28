#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char filename[] = "file.txt";
    
    int fd1 = open(filename, O_RDONLY);
    if (fd1 == -1) {
        perror("open fd1");
        exit(1);
    }

    int fd2 = dup(fd1);
    if (fd2 == -1) {
        perror("dup");
        close(fd1);
        exit(1);
    }

    int fd3 = open(filename, O_RDONLY);
    if (fd3 == -1) {
        perror("open fd3");
        close(fd1);
        close(fd2);
        exit(1);
    }

    if (lseek(fd1, 10, SEEK_SET) == -1) {
        perror("lseek");
    }

    printf("дескрипторы: fd1=%d, fd2=%d, fd3=%d\n", fd1, fd2, fd3);

    char buf1[8], buf2[8], buf3[8];

    ssize_t r1 = read(fd1, buf1, 7);
    ssize_t r2 = read(fd2, buf2, 7);
    ssize_t r3 = read(fd3, buf3, 7);

    buf1[r1] = '\0';
    buf2[r2] = '\0';
    buf3[r3] = '\0';

    printf("fd1: %s\n", buf1);
    printf("fd2: %s\n", buf2);
    printf("fd3: %s\n", buf3);

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
