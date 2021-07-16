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


int  main(int argc, char* const argv[])
{
  if (argc < 2) {
    printf("args < 2 in program 'c'\n");
    return 0;
  }
  int buf_size = atoi(argv[0]);
  char const* shared_memory_name = argv[1];
  char const* sem2_name = argv[2];
  char const* sem3_name = argv[3];
  int fd_shm;

  if ((fd_shm = shm_open(shared_memory_name, O_RDWR , 0660)) == -1) {
    perror("shm_open error in program 'c'\n");
    exit(1);
  }

  sem_t* sem2 = sem_open(sem2_name, 0,0,0);
  sem_t* sem3 = sem_open(sem3_name, 0,0,0);
  if (sem2 == SEM_FAILED || sem3 == SEM_FAILED) {
    perror("sem2 || sem3 error in program 'c'\n");
    exit(1);
  }

  char* shmem = (char*)mmap(NULL, buf_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd_shm, 0);
  pid_t p = fork();
  if (p == 0) {
    printf("program C got:\n");
    if (execve("b.out", argv, NULL) == -1) {
      perror("execve error in program 'c'\n");
      exit(1);
    }
  } else if (p > 0) {
    sem_wait(sem3);
    printf("%s\n", shmem);
  }
  sem_post(sem2);
}




