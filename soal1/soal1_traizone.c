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

int *pokesm, *shutsm, *cmsm, *ulpsm,*lp,*pokeball,*berry,*captur,*status;

int carpok = 0;
char nama[50];
int pilihan = 0;
int pilihan2=0;
pthread_t tid[8];
int cetekan = 0;
char message[50];
int message1 = 0;
//Jumlah Pokemon
int jmlh_poke = 0;

//Nama Pokemon
char npoke1[50];
char npoke2[50];
char npoke3[50];
char npoke4[50];
char npoke5[50];
char npoke6[50];
char npoke7[50];

//AP pokemon
int ap[7]={0,0,0,0,0,0,0};

//Item
int item[3]={10,10,10};

//Uang
int dollar=0;
int dolpok=0;

int pokeid = 0;

void* nama_pokemon()
{
  pokeid = *pokesm;
  if(pokeid == 110){strcpy(nama,"Bulbasaur");       dolpok=80;}
  if(pokeid == 111){strcpy(nama,"Shiny Bulbasaur"); dolpok=5080;}
  if(pokeid == 210){strcpy(nama,"Charmander");      dolpok=80;}
  if(pokeid == 211){strcpy(nama,"Shiny Charmander");dolpok=5080;}
  if(pokeid == 310){strcpy(nama,"Squirtle");        dolpok=80;}
  if(pokeid == 311){strcpy(nama,"Shiny Squirtle");  dolpok=5080;}
  if(pokeid == 410){strcpy(nama,"Rattata");         dolpok=80;}
  if(pokeid == 411){strcpy(nama,"Shiny Rattata");   dolpok=5080;}
  if(pokeid == 510){strcpy(nama,"Caterpie");        dolpok=80;}
  if(pokeid == 511){strcpy(nama,"Shiny Caterpie");  dolpok=5080;}
  if(pokeid == 120){strcpy(nama,"Pikachu");         dolpok=100;}
  if(pokeid == 121){strcpy(nama,"Shiny Pikachu");   dolpok=5100;}
  if(pokeid == 220){strcpy(nama,"Eevee");           dolpok=100;}
  if(pokeid == 221){strcpy(nama,"Shiny Eevee");     dolpok=5100;}
  if(pokeid == 320){strcpy(nama,"Jigglypuff");      dolpok=100;}
  if(pokeid == 321){strcpy(nama,"Shiny Jigglypuff");dolpok=5100;}
  if(pokeid == 420){strcpy(nama,"Snorlax");         dolpok=100;}
  if(pokeid == 421){strcpy(nama,"Shiny Snorlax");   dolpok=5100;}
  if(pokeid == 520){strcpy(nama,"Dragonite");       dolpok=100;}
  if(pokeid == 521){strcpy(nama,"Shiny Dragonite"); dolpok=5100;}
  if(pokeid == 130){strcpy(nama,"Mew");             dolpok=200;}
  if(pokeid == 131){strcpy(nama,"Shiny Mew");       dolpok=5200;}
  if(pokeid == 230){strcpy(nama,"Mewtwo");          dolpok=200;}
  if(pokeid == 231){strcpy(nama,"Shiny Mewtwo");    dolpok=5200;}
  if(pokeid == 330){strcpy(nama,"Moltres");         dolpok=200;}
  if(pokeid == 331){strcpy(nama,"Shiny Moltres");   dolpok=5200;}
  if(pokeid == 430){strcpy(nama,"Zapdos");          dolpok=200;}
  if(pokeid == 431){strcpy(nama,"Shiny Zapdos");    dolpok=5200;}
  if(pokeid == 530){strcpy(nama,"Articuno");        dolpok=200;}
  if(pokeid == 531){strcpy(nama,"Shiny Articuno");  dolpok=5200;}
}



void* menu(void *arg)
{
  pid_t child;
  char *argv1[] = {"clear", NULL};

  pthread_t id = pthread_self();
  if(pthread_equal(id,tid[0]))
  {
    child = fork();
    if(child==0){
      execv("/usr/bin/clear", argv1);
    }
    else{
      child =wait(NULL);
        printf("Input Menu Pokemon T18:\n" );
        if(carpok == 0){
        printf("1: Cari Pokemon\n" );
        }
        else{
          printf("1: Berhenti Mencari\n" );
        }
        printf("2: Pokedex\n" );
        printf("3: Shop\n" );
        printf("4: Go to Capture Mode\n");
        printf("5: Exit\n\n" );
        printf("pilihan anda:\n");
        if(message1==1){
          printf("%s\n", message);
          message1 = 0;
        }

    }
  }
}
void* pokedex(void *arg)
{
  pid_t child;
  char *argv1[] = {"clear", NULL};

  pthread_t id = pthread_self();
  if(pthread_equal(id,tid[0]))
  {
    child = fork();
    if(child==0){
      execv("/usr/bin/clear", argv1);
    }
    else{
      child =wait(NULL);
        printf("POKEDEX\n" );
        printf("%s\n", npoke1);
        printf("%d\n", ap[0]);
        printf("%s\n", npoke2);
        printf("%d\n", ap[1]);
        printf("%s\n", npoke3);
        printf("%d\n", ap[2]);
        printf("%s\n", npoke4);
        printf("%d\n", ap[3]);
        printf("%s\n", npoke5);
        printf("%d\n", ap[4]);
        printf("%s\n", npoke6);
        printf("%d\n", ap[5]);
        printf("%s\n", npoke7);
        printf("%d\n", ap[6]);
        sleep(2);

    }
  }
}
void* menu2(void *arg)
{
  pid_t child;
  char *argv1[] = {"clear", NULL};

  pthread_t id = pthread_self();
  if(pthread_equal(id,tid[0]))
  {
    child = fork();
    if(child==0){
      execv("/usr/bin/clear", argv1);
    }
    else{
      child =wait(NULL);
        printf("Input Menu CM Pokemon T18:\n" );
        printf("1: Tangkap\n" );
        printf("2: Item\n" );
        printf("3: Kabur\n" );
        printf("4: Exit\n\n" );
        printf("Wild %s has appeared!\n", nama);
        printf("pilihan anda:\n");

    }
  }
  return NULL;
}
void* apred(void *arg)
{
    int cek;
    while(1)
    {
      while(*cmsm==1){
        sleep(10);
      }
      for(int i=0;i<7;i++){
        if(ap>10){
          ap[i]-=10;
        }
        else{
          ap[i]=0;
          cek = rand() % 99;
          if(cek<10){
            ap[i]+=50;
          }
          else{
            if(i<6){
              for(int k=i; k<6;k++){
                ap[k]=ap[k+1];
              }
              ap[6]=0;
            }
            if(i==0){
              memset(npoke1,0,50);
              strcat(npoke1,npoke2);
              memset(npoke2,0,50);
              strcat(npoke2,npoke3);
              memset(npoke3,0,50);
              strcat(npoke3,npoke4);
              memset(npoke4,0,50);
              strcat(npoke4,npoke5);
              memset(npoke5,0,50);
              strcat(npoke5,npoke6);
              memset(npoke6,0,50);
              strcat(npoke6,npoke7);
              memset(npoke7,0,50);

            }
            else if(i==1){
              memset(npoke2,0,50);
              strcat(npoke2,npoke3);
              memset(npoke3,0,50);
              strcat(npoke3,npoke4);
              memset(npoke4,0,50);
              strcat(npoke4,npoke5);
              memset(npoke5,0,50);
              strcat(npoke5,npoke6);
              memset(npoke6,0,50);
              strcat(npoke6,npoke7);
              memset(npoke7,0,50);
            }
            else if(i==2){
              memset(npoke3,0,50);
              strcat(npoke3,npoke4);
              memset(npoke4,0,50);
              strcat(npoke4,npoke5);
              memset(npoke5,0,50);
              strcat(npoke5,npoke6);
              memset(npoke6,0,50);
              strcat(npoke6,npoke7);
              memset(npoke7,0,50);
            }
            else if(i==3){
              memset(npoke4,0,50);
              strcat(npoke4,npoke5);
              memset(npoke5,0,50);
              strcat(npoke5,npoke6);
              memset(npoke6,0,50);
              strcat(npoke6,npoke7);
              memset(npoke7,0,50);
            }
            else if(i==4){
              memset(npoke5,0,50);
              strcat(npoke5,npoke6);
              memset(npoke6,0,50);
              strcat(npoke6,npoke7);
              memset(npoke7,0,50);
            }
            else if(i==5){
              memset(npoke6,0,50);
              strcat(npoke6,npoke7);
              memset(npoke7,0,50);
            }
            else if(i==6){
              memset(npoke7,0,50);
            }
            jmlh_poke--;
          }
        }
      }
    }
}
void* cari_pokemon()
{
  int random;
  while(carpok==1){
    random = (rand() % 100) +1;
    if(random <=60 && carpok==1){
      cetekan = 1;
      carpok =0;
      nama_pokemon();
      printf("%s ditemukan\n", nama );
      pthread_create(&tid[3],NULL,&menu,NULL);
      pthread_join(tid[3],NULL);
    }
    else if(random>60 && carpok==1){
      if(carpok==0){return NULL;}
      printf("cari terus\n" );
      sleep(10);
    }
  }
}
void main()
{
  key_t pokek = 1111;
  key_t capk  = 1112;
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

  *shutsm = 0;
  *cmsm = 0;
  srand(time(NULL));
  pthread_create(&tid[7],NULL,&apred,NULL);

  while(pilihan != 5){
    pthread_create(&tid[0],NULL,&menu,NULL);
    pthread_join(tid[0],NULL);
    scanf("%d", &pilihan);
    if(carpok==1 && pilihan!=1){
      pthread_join(tid[2],NULL);
    }
    switch (pilihan) {
      case 1:
        printf("disini jalan\n" );
        sleep(1);
        if(carpok==0){
        carpok = 1;
        pthread_create(&tid[1],NULL,&menu,NULL);
        pthread_join(tid[1],NULL);
        pthread_create(&tid[2],NULL,&cari_pokemon,NULL);
        }
        else if(carpok==1){
          carpok=0;
          pthread_join(tid[2],NULL);
          pthread_create(&tid[4],NULL,&menu,NULL);
          pthread_join(tid[4],NULL);
        }
        break;
      case 2:
        pthread_create(&tid[5],NULL,&pokedex,NULL);
        pthread_join(tid[5],NULL);
        break;
      case 4:
        *cmsm = 1;
        if(cetekan==1){
        pthread_create(&tid[6],NULL,&menu2,NULL);
        pthread_join(tid[6],NULL);
        scanf("%d", &pilihan2);
        switch(pilihan2){
          case 1:
            if(item[1]<=0){}
            else{
              item[1] -= 1;
              *captur=pokeid;
              sleep(3);
              if(*captur == 0){
                strcat(message,"Pokemon lepas dari pokeball\n");
                message1 =1;
              }
              else if(*captur == 999){
                printf("pokemon ditangkap!\n" );
                strcat(message, "pokemon telah ditangkap");
                message1 = 1;
                *cmsm = 0;
                if(jmlh_poke==6){
                  strcat(npoke7,nama);
                  ap[6] = 100;
                }
                else if(jmlh_poke==5){
                  strcat(npoke6,nama);
                  ap[5]=100;
                }
                else if(jmlh_poke==4){
                  strcat(npoke5,nama);
                  ap[4] = 100;
                }
                else if(jmlh_poke==3){
                  strcat(npoke4,nama);
                  ap[3]=100;
                }
                else if(jmlh_poke==2){
                  strcat(npoke3,nama);
                  ap[2] = 100;
                }
                else if(jmlh_poke==1){
                  strcat(npoke2,nama);
                  ap[1]=100;
                }
                else if(jmlh_poke==0){
                  strcat(npoke1,nama);
                  ap[0] = 100;
                }
                else{
                  strcat(message,"Pokemon telah penuh\n");
                  message1 = 1;
                  dollar+=dolpok;
                  cmsm=0;
                }
              }
            }
            break;
          case 2:
            break;
          case 3:
            break;
          case 4:
            break;
        }
        cetekan=0;
        break;
        }
        else{
          printf("maaf anda harus mencari pokemon terlebih dulu nub\n" );
          break;
        }
    }
  }
}
