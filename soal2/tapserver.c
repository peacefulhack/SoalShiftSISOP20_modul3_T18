#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include<pthread.h>
#define PORT 4444

int main(){
  int token=0;
  int fd1[2];
  int fd2[2];
  if (pipe(fd1)==-1)
	{
		fprintf(stderr, "Pipe Failed" );
		return 1;
	}
	if (pipe(fd2)==-1)
	{
		fprintf(stderr, "Pipe Failed" );
		return 1;
	}
	int sockfd, ret;
	 struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
  memset(buffer,0,1024);
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}

  char terima[100];

	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}
    token++;
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);
      //fd1[0]read 1 write hp player 2
        char hpp1a[1024];
        char hpp1s[1024];
        char hpp2a[1024];
        char hpp2s[1024];
        strcpy(hpp1a,"100");
        strcpy(hpp1s,"100");
        strcpy(hpp2a,"100");
        strcpy(hpp2s,"100");
			while(1){
        //menerima hp sendiri
        if(token==1){
          read(fd1[0],hpp1s,1024);
          if(strcmp(hpp1a,hpp1s)!=0){
            send(newSocket, hpp1s,1024,0);
            memset(hpp1a,0,1024);
            strcpy(hpp1a,hpp1s);
          }
          if(strcmp(terima,"0")==0){
            printf("player 1 kalah\n");
            send(newSocket, "player 1 kalah", 100, 0);
            printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
            break;
          }
          //menerima hp musuh
          memset(buffer,0,1024);
    			recv(newSocket, buffer, 1024, 0);
          //mengirimkan hp musuh
          write(fd2[1],buffer,1024);
          if(strcmp(buffer, ":exit") == 0){
  					break;
          }
        }
        else if(token==2){
          read(fd2[0],hpp1s,1024);
          if(strcmp(hpp2a,hpp2s)!=0){
            send(newSocket, hpp2s,1024,0);
            memset(hpp2a,0,1024);
            strcpy(hpp2a,hpp2s);
          }
          if(strcmp(terima,"0")==0){
            printf("player 2 kalah\n");
            send(newSocket, "player 2 kalah", 100, 0);
            printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
            break;
          }
          //menerima hp musuh
          memset(buffer,0,1024);
    			recv(newSocket, buffer, 1024, 0);
          //mengirimkan hp musuh
          write(fd1[1],buffer,1024);
          if(strcmp(buffer, ":exit") == 0){
  					break;
          }
        }
			}
		}

	}

	close(newSocket);


	return 0;
}
