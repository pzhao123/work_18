#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define READ 0
#define WRITE 1

int main() {

    
    while (2) {       

        int fds1[2], fds2[2];
        pipe(fds1);
        pipe(fds2);

        int process;
        process = fork();

        //if parent
        if (process) {
            char input[200];
            printf("Input: ");
            fgets(input, sizeof(input), stdin);
            close(fds1[READ]);
            write(fds1[WRITE], input, sizeof(input));
        }
        //if child
        if (!process) {
            close(fds1[WRITE]);
            char line[200];
            read(fds1[READ], line, sizeof(line) );
            line[strlen(line) - 1] = '\0';
            int len = strlen(line);
            int i;
            for (i = 0; i < len; i++) {
                if ((line[i] >= 'a' && line[i] <= 'z')) {
                    line[i] = line[i] - 32;
                }
            }
            close(fds2[READ]);
            write(fds2[WRITE], line, sizeof(line));
            return 0;
        }
        //if parent
        else {
            int status;
            wait(&status);
            char result[200];
            close(fds2[WRITE]);
            read(fds2[READ], result, sizeof(result));
            printf("OUTPUT: %s\n", result);
        }
    }

    return 0;
}
