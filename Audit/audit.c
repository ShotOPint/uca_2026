#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LOGFILE "audit.log"
#define BUF_SIZE 1024

// Append a message to the log file
void add_entry(const char *message) {
    int fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(message);
    if (write(fd, message, len) != len) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (write(fd, "\n", 1) != 1) {
        perror("write newline");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

// Display log file contents with line numbers
void view_entries() {
    int fd = open(LOGFILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE];
    ssize_t numRead;
    int line = 1;
    char *start, *end;

    while ((numRead = read(fd, buf, BUF_SIZE)) > 0) {
        start = buf;
        end = buf;
        while (end < buf + numRead) {
            if (*end == '\n') {
                *end = '\0';
                printf("%d: %s\n", line++, start);
                start = end + 1;
            }
            end++;
        }
        if (start < buf + numRead) {
            printf("%d: %s\n", line++, start);
        }
    }

    if (numRead == -1) {
        perror("read");
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s --add \"message\" | --view\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "--add") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Missing message for --add\n");
            exit(EXIT_FAILURE);
        }
        add_entry(argv[2]);
    } else if (strcmp(argv[1], "--view") == 0) {
        view_entries();
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    return 0;
}