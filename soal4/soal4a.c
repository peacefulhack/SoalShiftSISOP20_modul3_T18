#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int mat42[4][2] = {
  {1, 2},
  {3, 1},
  {2, 3},
  {1, 2}
};
int mat25[2][5] = {
  {3, 1, 2, 3, 1},
  {3, 2, 1, 3, 2}
};
int mat45[4][5];

struct args {
  int q;
  int w;
};

void *kali(void* arg) {
  int q = ((struct args*)arg)->q;
  int w = ((struct args*)arg)->w;
  for (int k = 0; k < 2; k++) {
    mat45[q][w] += mat42[q][k] * mat25[k][w];
  }
}

int main() {

  pthread_t tid[4][5];

  for (int q = 0; q < 4; q++) {
    for (int w = 0; w < 5; w++) {
      struct args *index = (struct args *)malloc(sizeof(struct args));
      index->q = q;
      index->w = w;
      pthread_create(&tid[q][w], NULL, &kali, (void *)index);
    }
  }
  printf("Hasil Matriks: \n");
  for (int q = 0; q < 4; q++) {
    for (int w = 0; w < 5; w++) {
      pthread_join(tid[q][w], NULL);
      printf("%3d", mat45[q][w]);
    }
    printf("\n");
  }

  key_t key = 1111;
  int *smmat45[4][5];

  int shmid = shmget(key, sizeof(mat45), IPC_CREAT | 0666);

  for (int q = 0; q < 4; q++) {
    for (int w = 0; w < 5; w++) {
      smmat45[q][w] = shmat(shmid, NULL, 0);
      *smmat45[q][w] = mat45[q][w];
    }
  }
  for(int q=0; q<4; q++){
    for(int w=0; w<5; w++){
      shmdt(smmat45[q][w]);
    }
  }
}
