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
#include <netinet/in.h>
#include <sys/socket.h>
//client
#include <arpa/inet.h>
//shared memory
//#include <sys/ipc.h>
//#include <sys/shm.h>
#define PORT 8080
#include<ncurses.h>

//pilihan menu
int screen=0;
int pilihan=0;
int pilihan2=0;

//UserData
char pass[100];
char usern[100];
char bucket[5000];
//feedback
int regstat=0;
int logstat=0;
int jmlh_akun=0;

//pthread
pthread_t tid[2];

int player=0;

void pesan()
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
      if(regstat==1){
        printf("\nregister berhasil\n" );
        regstat=0;
        sleep(2);
      }
      else if(logstat==1){
        printf("\nLogin berhasil\n");
        logstat=0;
        screen=1;
        sleep(2);
      }
      else if(logstat==2){
        printf("login gagal, akun tidak ditemukan\n");
        logstat=0;
        sleep(2);
      }
    }
  }
}

void regis()
{
  FILE *fp;
  fp = fopen( "file.txt" , "a+" );
  fprintf(fp, "%s-%s||", usern,pass);
  fclose(fp);
  regstat=1;
  pesan();
}

void login()
{
  char nampas[200];
  memset(nampas,0,200);
  int c;
  strcpy(nampas,usern);
  strcat(nampas,"-");
  strcat(nampas,pass);
  int count=0;
  FILE *fp;
  fp=fopen("file.txt","r");
  while(1) {
    c = fgetc(fp);
    if( feof(fp) ) {
       break ;
    }
    bucket[count] = c;
    count++;
  }
  char *akun = strtok(bucket, "||");
  while(akun != NULL)
	{
    if(strcmp(akun,nampas)==0){
      jmlh_akun++;
    }
		akun = strtok(NULL, "||");
	}
  if(jmlh_akun!=0){
    logstat=1;
    pesan();
  }
  else{
    logstat=2;
    pesan();
  }
}
void* menu(void *arg)
{
  pid_t child;
  char *argv1[] = {"clear", NULL};
    child = fork();
    if(child==0){
      execv("/usr/bin/clear", argv1);
    }
    else{
      child =wait(NULL);
      printf("TapTap T18:\n" );
      printf("1: Login\n" );
      printf("2: Register\n" );
      printf("3: exit\n" );
      printf("%d\n", screen);
      if(pilihan==0){
        printf("Choices: ");
      }
      else if(pilihan==1){
        printf("Choices: Login\n");
        printf("Username: ");
        scanf("%s", usern);
        printf("password: ");
        scanf("%s", pass);
        login();
        pilihan=0;
      }
      else if(pilihan==2){
        printf("choices: Register\n");
        printf("Username: ");
        scanf("%s", usern);
        printf("password: ");
        scanf("%s", pass);
        regis();
        pilihan=0;
      }
    }
}
void waiting()
{
  while(player!=0){
    printf("waiting for player...\n" );
    sleep(2);
  }
}
void battle()
{
  printf("Game dimulai silahkan ​ tap ​ ​ tap ​ secepat mungkin !!\n");
  sleep(1);
  int ch,hp=100;
  initscr();
  while ((ch = getch()) != EOF && ch != 'q' && hp>0){
      if(ch==' '){
        hp-=10;
        printf("hit!!\n");
      }
      else{
      printf ("%c\n", ch);
    }
  }
  endwin();
}
void* menu2()
{
  pid_t child;
  char *argv1[] = {"clear", NULL};
    child = fork();
    if(child==0){
      execv("/usr/bin/clear", argv1);
    }
    else{
      child =wait(NULL);
      printf("TapTap T18:\n" );
      printf("1: Find Match\n" );
      printf("2: Logout\n" );
      if(pilihan2==0){
        printf("Choices: ");
      }
      else if(pilihan2==1){
        printf("Choices: battle\n");
        sleep(1);
        battle();
        pilihan2=0;
      }
      else if(pilihan2==2){
        printf("Choices: battle\n");
        memset(pass,0,100);
        memset(usern,0,100);
        memset(bucket,0,5000);
        screen=0;
      }
    }
}

int main(int argc, char const *argv[]) {
    //struct sockaddr_in address;
    //int sock = 0, valread;
    //struct sockaddr_in serv_addr;
    //char *hello = "Hello from client";
    //char buffer[1024] = {0};
    //if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    //    printf("\n Socket creation error \n");
    //    return -1;
    //}

    //memset(&serv_addr, '0', sizeof(serv_addr));

    //serv_addr.sin_family = AF_INET;
    //serv_addr.sin_port = htons(PORT);

    //if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
    //    printf("\nInvalid address/ Address not supported \n");
    //    return -1;
    //}

    //if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    //    printf("\nConnection Failed \n");
    //    return -1;
    //}

    //send(sock , hello , strlen(hello) , 0 );
    //printf("Hello message sent\n");
    //valread = read( sock , buffer, 1024);
    //printf("%s\n",buffer );
    //return 0;
    while(pilihan!=3){
      while(screen==0){
        if(screen==0){
          pthread_create( &tid[0], NULL, &menu, NULL);
          pthread_join(tid[0],NULL);
          scanf("%d", &pilihan);
          if(screen==1){break;}
            pthread_create( &tid[0], NULL, &menu, NULL);
            pthread_join(tid[0],NULL);
        }
      }
      while(pilihan2!=2){
        pthread_create(&tid[1],NULL,&menu2,NULL);
        pthread_join(tid[1],NULL);
        scanf("%d", &pilihan2);
        pthread_create(&tid[1],NULL,&menu2,NULL);
        pthread_join(tid[1],NULL);
      }
    }
}
