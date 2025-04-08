#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

#define BUF_SIZE 1024

// Function to simulate `ls -l`
void listFiles() {
    struct dirent *entry;
    struct stat fileStat;
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == -1) {
            perror("Stat error");
            continue;
        }

        // File type and permissions
        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

        // Number of links, owner, group
        printf(" %ld", fileStat.st_nlink);
        printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
        printf(" %s", getgrgid(fileStat.st_gid)->gr_name);

        // File size
        printf(" %ld", fileStat.st_size);

        // Last modified time
        char timeBuff[20];
        strftime(timeBuff, sizeof(timeBuff), "%b %d %H:%M", localtime(&fileStat.st_mtime));
        printf(" %s", timeBuff);

        // File name
        printf(" %s\n", entry->d_name);
    }

    closedir(dir);
}

// Function to simulate `cp source destination`
void copyFile(char *source, char *destination) {
    int srcFd = open(source, O_RDONLY);
    if (srcFd == -1) {
        perror("Error opening source file");
        return;
    }

    int destFd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd == -1) {
        perror("Error opening destination file");
        close(srcFd);
        return;
    }

    char buffer[BUF_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = read(srcFd, buffer, BUF_SIZE)) > 0) {
        write(destFd, buffer, bytesRead);
    }

    close(srcFd);
    close(destFd);
    printf("File copied successfully.\n");
}

// Function to simulate `wc filename`
void wordCount(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int lines = 0, words = 0, characters = 0;
    char ch, prev = ' ';
    
    while ((ch = fgetc(file)) != EOF) {
        characters++;
        if (ch == '\n') lines++;
        if ((ch == ' ' || ch == '\n' || ch == '\t') && prev != ' ' && prev != '\n' && prev != '\t') {
            words++;
        }
        prev = ch;
    }

    fclose(file);
    printf("Lines: %d, Words: %d, Characters: %d\n", lines, words, characters);
}

// Main function to handle user input
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("  %s ls       (List files in long format)\n", argv[0]);
        printf("  %s cp src dest  (Copy file)\n", argv[0]);
        printf("  %s wc file   (Word count)\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "ls") == 0) {
        listFiles();
    } else if (strcmp(argv[1], "cp") == 0) {
        if (argc < 4) {
            printf("Usage: %s cp <source> <destination>\n", argv[0]);
        } else {
            copyFile(argv[2], argv[3]);
        }
    } else if (strcmp(argv[1], "wc") == 0) {
        if (argc < 3) {
            printf("Usage: %s wc <filename>\n", argv[0]);
        } else {
            wordCount(argv[2]);
        }
    } else {
        printf("Invalid command.\n");
    }

    return 0;
}
