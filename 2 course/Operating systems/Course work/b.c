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

int main(int argc,  char const * argv[]) {
  if (argc < 2) {
    perror("args < 2 in program 'b'\n");
    exit(1);
  }
  int buf_size = atoi(argv[0]);
  char const* shared_memory_name = argv[1];
  char const* sem3_name = argv[3];
  int fd_shm;

  if ((fd_shm = shm_open(shared_memory_name, O_RDWR , 0660)) == -1) {
    perror("shm_open error in program 'b'\n");
    exit(1);
  }

  sem_t* sem3 = sem_open(sem3_name, 0,0,0);
  if (sem3 == SEM_FAILED) {
    perror("sem3 error in program 'b'\n");
    exit(1);
  }

  char* shmem = (char*)mmap(NULL, buf_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd_shm, 0);
  int size = strlen(shmem);
  printf("%d symbols\n", size);
  sem_post(sem3);
}




