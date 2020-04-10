#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int mat45[4][5];
long mat45h[4][5];

struct args {
  int i;
  int j;
};

void *factorial(void* arg);

int main() {
  key_t key = 1234;
  int *smmat45;
  int shmid = shmget(key, 80, IPC_CREAT | 0666);
  smmat45 = shmat(shmid, NULL, 0);
  int* inherit = (int *)smmat45;
  memcpy(mat45, inherit, 80);
  shmdt(smmat45);
  shmctl(shmid, IPC_RMID, NULL);

  pthread_t tid[4][5];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      struct args *index = (struct args *)malloc(sizeof(struct args));
      index->i = i;
      index->j = j;
      pthread_create(&tid[i][j], NULL, &factorial, (void *)index);
    }
  }
  printf("Matriks :\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      pthread_join(tid[i][j], NULL);
      printf("%20ld", mat45h[i][j]);
    }
    printf("\n");
  }
}

void *factorial(void* arg) {
  int i = ((struct args*)arg)->i;
  int j = ((struct args*)arg)->j;
  long hasilEl = 1;
  for (int n = 1; n <= mat45[i][j]; n++)
  {
    hasilEl += (long)n;
  }
  mat45h[i][j] = hasilEl;
}
