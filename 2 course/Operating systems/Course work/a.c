#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>

#define BUF_SIZE 100
#define SHARED_MEMORY "/shm_file"
#define S_1 "/sem1"
#define S_2 "/sem2"
#define S_3 "/sem3"

int main() {

  int fd_shm;
  char* shmem;
  char* tmp = (char*)malloc(sizeof(char) * BUF_SIZE);
  char* buf_size = (char*)malloc(sizeof(char) * 10);
  sem_t* sem1 = sem_open(S_1, O_CREAT, 0660, 0);
  sem_t* sem2 = sem_open(S_2, O_CREAT, 0660, 0);
  sem_t* sem3 = sem_open(S_3, O_CREAT, 0660, 0);
  if (sem1 == SEM_FAILED || sem2 == SEM_FAILED || sem3 == SEM_FAILED) {
    perror("Sem opening error in program 'a'\n");
    exit(1);
  }
  if ((fd_shm = shm_open(SHARED_MEMORY, O_RDWR | O_CREAT | O_EXCL, 0660)) == -1) {
    perror("shm_open error in program 'a'\n");
    exit(1);
  }
  if (ftruncate(fd_shm, BUF_SIZE) == -1) {
    perror("ftruncate error in program 'a'\n");
    exit(-1);
  }

  shmem = (char*)mmap(NULL, BUF_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd_shm, 0);
  sprintf(buf_size, "%d", BUF_SIZE);
  char* argv[] = {buf_size, SHARED_MEMORY, S_2, S_3, NULL};


  while (scanf ("%s", tmp) != EOF) {
    pid_t pid = fork();
    if (pid == 0) {
      pid_t pid_1 = fork();
      if (pid_1 == 0) {
        sem_wait(sem1);
        printf("program A sent:\n");
        if (execve("./b.out", argv, NULL) == -1) {
          perror("Could not execve in program 'a'\n");
        }
      } else if (pid_1 > 0) {
        sem_wait(sem3);
        if (execve("./c.out", argv, NULL) == -1) {
          perror("Could not execve in program 'a'\n");
        }
      }
    } else if (pid > 0) {
      sprintf(shmem, "%s", tmp);
      sem_post(sem1);
      sem_wait(sem2);
      printf("_________________\n\n");
    }
  }

  shm_unlink(SHARED_MEMORY);
  sem_unlink(S_1);
  sem_unlink(S_2);
  sem_unlink(S_3);
  sem_close(sem1);
  sem_close(sem2);
  sem_close(sem3);
  close(fd_shm);
}




