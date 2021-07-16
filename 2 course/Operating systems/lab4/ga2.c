// gcc ga2.c -lrt -o ga2 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stddef.h>

#define DATA_SIZE 256
#define MEMORY_SIZE 4096
#define MEMORY_NAME "lab4"

#if DATA_SIZE > MEMORY_SIZE
#warning Segfault may occur
#endif

typedef struct res {
        size_t size;
        int data[DATA_SIZE];
} res_t;

void termination_handler() {
    fprintf(stderr, "Segmentation fault occur, try decrease DATA_SIZE macro\n");
    shm_unlink("lab4");
    exit(1);
}

int main() {
        signal(SIGSEGV, termination_handler); //обработка сигнала
        //открывает объект разделяемой памяти
        int fd = shm_open(MEMORY_NAME, O_EXCL | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if (fd == -1) { //ошибка открытия объекта разделяемой памяти
                printf("Can't open shared memory file\n");
        }
        if (ftruncate(fd, MEMORY_SIZE) == -1) { //укорачивает файл дл указанной длины
                printf("Can't extent shared memory file\n");
        }
        //отражение файла в память
        res_t *addr = mmap(NULL, MEMORY_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
        if (addr == (void *) -1) { //ошибка отражения
                printf("Mmap error!\n");
        }
        addr->size = 0;
        char c;
        int num = 0, res = 0, minus = 0, top = 1, pr = 0;
        while (scanf("%c", &c) > 0) {
                if (c == ' ' || c == '\t') {
                        if (num == 0) {
                                break;
                        } else {
                                if (top == 1)
                                        top = 0;
                                else if (minus == 1)
                                        res = (res / num) * (-1);
                                else res = res / num;
                        }
                        num = 0;
                        top = 0;
                        minus = 0;
                        pr = 1;
                } else if (c == '-') {
                        minus = 1;
                        pr = 0;
                } else if (c == '\n') {
                        if (num == 0) {
                                if (pr == 1) res = res / 1;
                                else break;
                        } else {
                                if (top == 1)
                                        top = 0;
                                else if (minus == 1)
                                        res = (res / num) * (-1);
                                else res = res / num;
                        }
                        addr->data[addr->size++] = res;
                        num = 0;
                        top = 1;
                        minus = 0;
                        res = 0;
                        pr = 0;
                } else if (c >= '0' && c <= '9') {
                        num = num *10 + c - '0';
                                if (top == 1)
                                        res = num;
                        pr = 0;
                }
        }
        munmap(addr, MEMORY_SIZE); //снимает отражение
        close(fd);
        return 0;
}