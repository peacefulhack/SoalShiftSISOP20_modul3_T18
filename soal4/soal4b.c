#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int matrix[4][5];

struct args {
  int q;
  int w;
};

void *factorial(void* arg) {
  int q = ((struct args*)arg)->q;
  int w = ((struct args*)arg)->w;
  long hasilEl = 1;
  for (int n = 1; n <= matrix[q][w]; n++) hasilEl *= (long)n;
  hasil[q][w] = hasilEl;
}

int main() {
  key_t key = 1111;
  int *smmat45[4][5];
  int shmid = shmget(key, sizeof(smmat45), IPC_CREAT | 0666);
  for (int q = 0; q < 4; q++) {
    for (int w = 0; w < 5; w++) {
      smmat45[q][w] = shmat(shmid, NULL, 0);
      matrix[q][w]=*smmat45[q][w];
    }
  }
  shmdt(smmat45);
  shmctl(shmid, IPC_RMID, NULL);
}
