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

pthread_t tid[9];

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
int dump;

//Uang
int dollar=10000;
int dolpok=0;

//pokemon
int pokeid = 0;
int pokmon[7];

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
void* shutdown()
{
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
    char *argv[] = {"pkill", "-9", "traizone", NULL};
    execv("/bin/pkill", argv);
  }
}
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
void dowhat(int i)
{
    if(ap[i]!=0){
      dollar += pokmon[i];
      pokmon[i]=0;
    }
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
        printf("=====================\n" );
        printf("jumlah pokemon : %d\n", jmlh_poke);
        printf("jumlah Uang    : %d\n", dollar);
        printf("jumlah pokeball: %d\n", item[0]);
        printf("jumlah lullaby : %d\n", item[1]);
        printf("jumlah berry   : %d\n", item[2]);
        printf("=====================\n" );
        printf("pilihan anda:\n");
        if(message1==1){
          printf("%s\n", message);
          message1 = 0;
        }

    }
  }
}
void* shop(void *arg)
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
        printf("Kang pokeball bulat dadakan 500an:\n\n" );
        printf("=====================\n" );
        printf("opsi dagangan:\n");
        printf("1.jumlah Stok pokeball : %d\n", *pokeball);
        printf("2.jumlah Stok lullaby : %d\n", *lp);
        printf("3.jumlah stok berry   : %d\n", *berry);
        printf("=====================\n" );
        printf("=====================\n" );
        printf("Inventory:\n" );
        printf("jumlah pokeball     : %d\n", item[0]);
        printf("jumlah lullaby      : %d\n", item[1]);
        printf("jumlah berry        : %d\n", item[2]);
        printf("=====================\n" );
        printf("pilihan anda:\n");
        printf("1.beli pokeball\n" );
        printf("2.beli lullaby\n" );
        printf("3.beli berry\n" );
        printf("4.exit\n" );
        if(message1==1){
          printf("%s\n", message);
          memset(message,0,50);
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
      printf("1*%s\n", npoke1);
      printf(" *%d\n", ap[0]);
      printf("2*%s\n", npoke2);
      printf(" *%d\n", ap[1]);
      printf("3*%s\n", npoke3);
      printf(" *%d\n", ap[2]);
      printf("4*%s\n", npoke4);
      printf(" *%d\n", ap[3]);
      printf("5*%s\n", npoke5);
      printf(" *%d\n", ap[4]);
      printf("6*%s\n", npoke6);
      printf(" *%d\n", ap[5]);
      printf("7*%s\n", npoke7);
      printf(" *%d\n", ap[6]);
      printf("\njumlah berry %d\n", item[2]);
      printf("Untuk menghapus pokemon, tekan pilihan 1-7\n" );
      printf("tekan 8 untuk memberi berry\n");
      printf("untuk keluar tekan 9\n" );
      int pilgan=0;
        scanf("%d", &pilgan);
        switch (pilgan) {
          case 1:
            dowhat(0);
            jmlh_poke--;
            break;
          case 2:
            dowhat(1);
            jmlh_poke--;
            break;
          case 3:
            dowhat(2);
            jmlh_poke--;
            break;
          case 4:
            dowhat(3);
            jmlh_poke--;
            break;
          case 5:
            dowhat(4);
            jmlh_poke--;
            break;
          case 6:
            dowhat(5);
            jmlh_poke--;
            break;
          case 7:
            dowhat(6);
            jmlh_poke--;
            break;
          case 8:
            if(item[2]>0){
              item[2]--;
              for(int p=0;p<jmlh_poke;p++){
                ap[p]+=10;
              }
            }
            break;
          case 9:
            return NULL;
            break;
        }
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
        printf("status ulpsm : %d\n", *ulpsm);
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
      while(*cmsm!=1){
        sleep(10);
        for(int i=0;i<jmlh_poke;i++){
          if(ap[i]>10){
            ap[i]-=10;
          }
          else{
            ap[i]=0;
            cek = rand() % 99;
            if(cek<10){
              ap[i]+=50;
            }
            else{
              dowhat(i);
              jmlh_poke--;
            }
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

    int pilgan2=0;
  while(pilihan != 5){
    pilgan2=0;
    pthread_create(&tid[0],NULL,&menu,NULL);
    pthread_join(tid[0],NULL);
    scanf("%d", &pilihan);
    if(carpok==1 && pilihan!=1){
      pthread_join(tid[2],NULL);
      printf("ketemu!\n" );
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
      case 3:
        while(pilgan2!=4){
          pthread_create(&tid[8],NULL,&shop,NULL);
          pthread_join(tid[8],NULL);
          scanf("%d", &pilgan2);
          switch (pilgan2) {
            case 1:
              //5
              if(dollar<5){
                strcat(message,"uang tidak cukup");
                message1++;
              }
              else{
                dollar-=5;
                item[0]++;
                dump = *pokeball;
                dump--;
                *pokeball = dump;
              }
              break;
            case 2:
              if(dollar<60){
                strcat(message,"uang tidak cukup");
                message1++;
              }
              else{
                dollar-=60;
                item[1]++;
                dump = *lp;
                dump--;
                *lp = dump;
              }
              break;
            case 3:
              if(dollar<15){
                strcat(message,"uang tidak cukup");
                message1++;
              }
              else{
                dollar-=15;
                item[2]++;
                dump = *berry;
                dump--;
                *berry = dump;
              }
              break;
          }
        }
        break;
      case 4:
        *cmsm = 1;
        if(cetekan==1){
          while(pilihan2!=3){
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
                    break;
                  }
                  else if(*captur == 999){
                    strcat(message, "pokemon telah ditangkap");
                    pokmon[jmlh_poke] = dolpok;
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
                      strcat(message,"Pokemon dilepas\n");
                      message1 = 1;
                      dollar+=dolpok;
                      cmsm=0;
                    }
                    jmlh_poke++;
                    break;
                  }
                }
                break;
              case 2:
                *ulpsm = 1;
                break;
              case 3:
                *cmsm = 0;
                break;
              case 4:
                //exit(EXIT_SUCCESS);
                break;
            }
        }
        cetekan=0;
        break;
        }
        else{
          printf("maaf anda harus mencari pokemon terlebih dulu nub\n" );
          break;
        }
    case 5:
      *shutsm=1;
      sleep(5);
      shutdown();
      exit(EXIT_SUCCESS);
      break;
    }
  }
}
