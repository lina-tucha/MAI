#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PIPE_FD_SIZE 2

int main() {
        FILE *fp1 = NULL;
        printf("Enter file name to read data: ");
        char *name1=(char *)malloc(256);
        scanf("%s",name1);
        //name1 = "test.txt";
        int fd1[PIPE_FD_SIZE];
        if (pipe(fd1) == -1) {
                printf("Can\'t create pipe!\n");
                exit(0);
        }
        int pr = fork();
        if (pr == -1) {
                printf("Can\'t fork child!\n");
                exit(0);
        } else if (pr == 0) {
                fp1 = freopen(name1, "r", stdin);
                if (fp1 == NULL) {
                        printf("Can\'t open file!\n");
                        exit(0);
                }
                close(fd1[0]);
                if (dup2(fd1[1], 1) == -1) {
                        printf("Can\'t change stdout!\n");
                        exit(0);
                }
                char * const * argv = NULL;
                if (execv("ga2", argv) == -1) {
                        printf("Can\'t execute child process!\n");
                        exit(0);
                }
        } else {
                close(fd1[1]);
                int res;
                while (read(fd1[0], &res, sizeof(int))) {
                        printf("%d\n", res);
                }
                close(fd1[0]);
        }
        return 0;
}