// gcc ga1.c -lrt -o ga1 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stddef.h>

#define MEMORY_SIZE 4096
#define DATA_SIZE 256
#define MEMORY_NAME "lab4"

#if DATA_SIZE > MEMORY_SIZE
#warning Segfault may occur
#endif

typedef struct res {
        size_t size;
        int data[DATA_SIZE];
} res_t;

int main() {
        FILE *fp = NULL;
        printf("Enter file name to read data: ");
        char *name=(char *)malloc(256);
        scanf("%s",name);
        int pr = fork(); //создается дочерний процесс
        if (pr == -1) {
                printf("Can\'t fork child!\n");
                exit(0);
        } else if (pr == 0) { //ребенок
                fp = freopen(name, "r", stdin);
                if (fp == NULL) {
                        printf("Can\'t open file!\n");
                        exit(0);
                }
                char * const * argv = NULL;
                if (execv("ga2", argv) == -1) { //дочерняя программа
                        printf("Can\'t execute child process!\n");
                        exit(0);
                }
        } else { //родитель
                int status;
                if (waitpid(pr, &status, 0) == -1) { //ждет, когда ребенок закончит
                        printf("Waitpid error!\n");
                }
                if (WIFSIGNALED(status)) { //дочерний процесс завершился из-за необработанного сигнала
                        fprintf(stderr, "Child process terminated by signal: %d\n", WTERMSIG(status));
                        shm_unlink(MEMORY_NAME);
                        exit(1);
                }
                if (WEXITSTATUS(status) != 0) {//8 младших битов значения, которые вернул ребенок
                        exit(1);
                }
                int fd = shm_open(MEMORY_NAME, O_RDONLY, S_IRUSR | S_IWUSR); //открывает объект разделяемой памяти
                if (fd == -1) { //ошибка открытия объекта разделяемой памяти
                        printf("Can\'t open shared memory file\n");
                }
                res_t *addr = mmap(NULL, MEMORY_SIZE, PROT_READ, MAP_SHARED, fd, 0); //отражение файла в память
                if (addr == (void *) -1) {
                        printf("Mmap error!\n"); //ошибка отражения
                }
                for (int i = 0; i < addr->size; i++) {
                        printf("%d\n", addr->data[i]);
                }
                munmap(addr, MEMORY_SIZE); //снимает отражение
                shm_unlink(MEMORY_NAME); // закрывает объект разделяемой памяти
                close(fd);
        }
        fclose(stdin);
        return 0;
}