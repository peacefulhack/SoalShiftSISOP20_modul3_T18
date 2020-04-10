#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include <time.h>
//thread library
#include<pthread.h>
//server-client
//#include <netinet/in.h>
//#include <sys/socket.h>
//client
//#include <arpa/inet.h>
//shared memory
#include <sys/ipc.h>
#include <sys/shm.h>
#define Num 6

int *pokesm,*shutsm, *cmsm, *ulpsm,*lp,*pokeball,*berry,*status,*captur;
int cpoke = 0;
int cshop = 0;
int hasil = 0;
int esrate = 0;
int besrate = 0;
int enrate = 0;
int caprate = 0;
int dolrate = 0;
int bucket = 0;
int captrand = 0;
pthread_t tid[Num];

//deklarasi shared memory
int pshmid;
int shtshmid;
int cmshmid;
int ulpshmid;
int lpshmid;
int pokshmid;
int bershmid;
int sttshmid;
int capshmid;

void* shutdown(void* arg)
{
  while(1){
    if(*shutsm==1){
      pid_t shutt;
      shutt = fork();
      if(shutt==0){
        shmdt(pokesm);
        shmdt(cmsm);
        shmdt(ulpsm);
        shmdt(pokeball);
        shmdt(berry);
        shmdt(status);
        shmdt(captur);
        shmdt(shutsm);
        shmctl(pshmid  , IPC_RMID, NULL);
        shmctl(shtshmid, IPC_RMID, NULL);
        shmctl(cmshmid , IPC_RMID, NULL);
        shmctl(ulpshmid, IPC_RMID, NULL);
        shmctl(pokshmid, IPC_RMID, NULL);
        shmctl(lpshmid , IPC_RMID, NULL);
        shmctl(sttshmid, IPC_RMID, NULL);
        shmctl(capshmid, IPC_RMID, NULL);
        shmctl(bershmid, IPC_RMID, NULL);
      }
      else if(shutt>0){
        shutt = wait(NULL);
        char *argv[] = {"pkill", "-9", "pokezone", NULL};
        execv("/bin/pkill", argv);
      }
    }
  }
}
void* pokemon(void* arg)
{
  int t = cpoke++;
  srand(time(NULL));
  if(t == 1){
    int shiny;
    shiny = rand() % 8000;
    if(shiny == 0){
      hasil += 1;
      esrate += 5;
      caprate -= 20;
      dolrate += 5000;
    }
  }
  else{
    /*
    Bulbasaur   11*
    Charmander  12*
    Squirtle    13*
    Rattata     14*
    Caterpie    15*
    Pikachu     21*
    Eevee       22*
    Jigglypuff  23*
    Snorlax     24*
    Dragonite   25*
    Mew         31*
    Mewtwo      32*
    Moltres     33*
    Zapdos      34*
    Articuno    35*
    */
    int rarity = (rand() % 100) + 1;
    int jenis = (rarity % 5) + 1;
    hasil = jenis * 100;
    if(rarity<=5)
    {//Legendary
      hasil += 30;
      enrate += 5;
      esrate += 20;
      caprate +=30;
      dolrate += 200;
    }
    else if(rarity<=20)
    {//Rare
      hasil += 20;
      enrate += 15;
      esrate += 10;
      caprate +=50;
      dolrate += 100;
    }
    else
    {//Normal
      hasil += 10;
      enrate += 80;
      esrate += 5;
      caprate +=70;
      dolrate += 80;
    }
  }
}
void* lullaby(void* arg)
{
    while(1){
      if(*ulpsm==1){
        pthread_t id = pthread_self();
        if(pthread_equal(id,tid[2])){
          printf("ulpsm activated 1\n" );
          caprate +=20;
          sleep(10);
          caprate -=20;
          printf("ulpsm deactivated 1\n" );
        }
        else if(pthread_equal(id,tid[3])){
          printf("ulpsm activated 2\n" );
          besrate = esrate;
          esrate = 0;
          sleep(10);
          esrate = besrate;
          printf("ulpsm deactivated 2\n" );
        }
        if(*ulpsm==1){*ulpsm=0;}
      }
    }
    return NULL;
}
void* capture(void* arg)
{
  while(1){
    if(*captur!=0 && *captur<=700){
      printf("Trying to catch with weak hand and pokeball\n" );
      if(*captur%10==1){bucket-=20;}
      *captur/=10;
      if(*captur%10==1){bucket+=70;}
      else if(*captur%10==2){bucket+=50;}
      else if(*captur%10==3){bucket+=30;}
      captrand = (rand()%100)+1;
      if(captrand <= bucket){
        printf("penangkapan berhasil\n" );
        *captur=999;
        *status=1;
      }
      else{*captur=0;*status=2;printf("penangkapan gagal\n" );}
    }
    sleep(1);
  }
}

int main(int argc, char *argv[])
{
    //initiate shared memory
    key_t pokek = 1111;
    key_t capk  = 1112;
    key_t shpk  = 2222;
    key_t shtk  = 3333;
    key_t cmk   = 4444;
    key_t ulpk  = 5555;
    key_t lpk   = 6666;
    key_t pokk  = 7777;
    key_t berk  = 8888;
    key_t statk = 9999;

    int pshmid = shmget(pokek,  sizeof(int), IPC_CREAT | 0666);
    int shtshmid = shmget(shtk, sizeof(int), IPC_CREAT | 0666);
    int cmshmid = shmget(cmk  , sizeof(int), IPC_CREAT | 0666);
    int ulpshmid = shmget(ulpk, sizeof(int), IPC_CREAT | 0666);
    int lpshmid = shmget(lpk  , sizeof(int), IPC_CREAT | 0666);
    int pokshmid = shmget(pokk, sizeof(int), IPC_CREAT | 0666);
    int bershmid = shmget(berk, sizeof(int), IPC_CREAT | 0666);
    int sttshmid = shmget(statk, sizeof(int), IPC_CREAT| 0666);
    int capshmid = shmget(capk, sizeof(int), IPC_CREAT | 0666);

    pokesm = shmat(pshmid,    NULL, 0);
    shutsm = shmat(shtshmid,  NULL, 0);
    cmsm = shmat(cmshmid,     NULL, 0);
    ulpsm = shmat(ulpshmid,   NULL, 0);
    lp = shmat(lpshmid,       NULL, 0);
    pokeball = shmat(pokshmid,NULL, 0);
    berry = shmat(bershmid,   NULL, 0);
    status = shmat(sttshmid,  NULL, 0);
    captur = shmat(capshmid,  NULL, 0);

    *captur   = 0;
    *pokesm   = 0;
    *ulpsm    = 0;
    *lp       = 100;
    *pokeball = 100;
    *berry    = 100;
    *status   = 0;

    pid_t mainfeature;


    mainfeature = fork();
    if(mainfeature==0){
      while(1){
        if(*lp <= 190){*lp+=10;}
        else{*lp=200;}

        if(*pokeball<=190){*pokeball+=10;}
        else{*pokeball=200;}

        if(*berry<=190){*berry+=10;}
        else{*berry=200;}
        sleep(10);
      }
    }
    else{

        pthread_create( &tid[2], NULL, &lullaby, NULL);
        pthread_create( &tid[3], NULL, &lullaby, NULL);
        pthread_create( &tid[3], NULL, &shutdown, NULL);
      while(1){
          pthread_create( &tid[0], NULL, &pokemon, NULL);
          pthread_create( &tid[1], NULL, &pokemon, NULL);
          pthread_join(tid[0],NULL);
          pthread_join(tid[1],NULL);
          *pokesm = hasil;
          if(*cmsm == 1){
            printf("Combat mode activated\n" );
            int st = 0;
            while(*status == 0){
              st = (rand() % 100) + 1;
              if(st <= esrate && *status == 0){*status=2;}
              if(*status==0){sleep(20);}
            }
            if(*status == 1){
            printf("pokemon telah ditangkap\n" );
            }
            else{
              printf("pokemon kaburr\n" );
            }
            *cmsm = 0;*status = 0;
          }
          pthread_create(&tid[5],NULL,&capture,NULL);
        printf("%d\n", hasil);

        hasil = 0;cpoke = 0;enrate=0;esrate=0;caprate=0;dolrate=0;
        sleep(1);
      }
    }
}
