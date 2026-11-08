// Dylan Bodoh, 111

// finfo.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("File Type: Regular File\n");
    }
    else if (S_ISDIR(mode)) {
        printf("File Type: Directory\n");
    }
    else if (S_ISLNK(mode)) {
        printf("File Type: Symbolic Link\n");
    }
    else if (S_ISCHR(mode)) {
        printf("File Type: Character Device\n");
    }
    else if (S_ISBLK(mode)) {
        printf("File Type: Block Device\n");
    }
    else if (S_ISFIFO(mode)) {
        printf("File Type: FIFO/Pipe\n");
    }
    else if (S_ISSOCK(mode)) {
        printf("File Type: Socket\n");
    }
    else {
        printf("File Type: Unknown\n");
    }
}

void print_permissions(mode_t mode) {
    char perms[10];
    //terenary ops for permisions
    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';

    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';

    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';

    perms[9] = '\0';

    printf("Permissions: %s\n", perms);
}

int main(int argc, char *argv[]) {
    struct stat fileInfo;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &fileInfo) == -1) {
        perror("could not get file");
        return 1;
    }

    print_file_type(fileInfo.st_mode);
    print_permissions(fileInfo.st_mode);

    printf("Owner UID: %u\n", fileInfo.st_uid);
    printf("Size: %lld bytes\n", (long long) fileInfo.st_size);

    char timeStr[100];
    struct tm *tm_info = localtime(&fileInfo.st_mtime);

    if (tm_info == NULL) {
        perror("localtime");
        return 1;
    }

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);

    printf("Last Modified: %s\n", timeStr);

    return 0;
}