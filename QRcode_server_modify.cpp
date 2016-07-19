#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>

using namespace std;


#define MYPORT  8887
#define QUEUE   20
#define BUFFER_SIZE 1024

int main()
{
    ///定义sockfd
   	int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

   ///定义sockaddr_in
   struct sockaddr_in server_sockaddr;
   server_sockaddr.sin_family = AF_INET;
   server_sockaddr.sin_port = htons(MYPORT);
   server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

 ///bind，成功返回0，出错返回-1
 	if (-1 == bind(server_sockfd , (struct sockaddr *)&server_sockaddr , sizeof(server_sockaddr)))
 	{
     	perror("bind");
     	return -1;
 	}

   ///listen，成功返回0，出错返回-1
   if(-1 == listen(server_sockfd , QUEUE))
   {
       perror("listen");
	   return -2;
   }

  	///客户端套接字
  	char buffer[BUFFER_SIZE];
  	struct sockaddr_in client_addr;
  	//socklen_t length = sizeof(client_addr);
		int n=0;
		int iSinSize = sizeof(struct sockaddr_in);
		int nEachAccptFd = accept(server_sockfd , (struct sockaddr *)&client_addr , (socklen_t *)&iSinSize);
	while (1)
	{
		if (-1 == nEachAccptFd)
		{
			cout<<"accept failed!"<<endl;
			return -3;
		}
		cout<<"accept is ok!"<<endl;
//
//		if (-1 == write(nEachAccptFd , "HELLO WORLD!" , 12))
//		{
//			cout<<"write failed!"<<endl;
//			return -4;
//		}
		memset(buffer,0,sizeof(buffer));
		int len = recv(nEachAccptFd,buffer,sizeof(buffer),0);
		cout<<buffer<<'\t'<<n<<endl;
		if(n == 10) return -4;
		n++;
		send(nEachAccptFd,"world",6,0);
//		if (-1 == write(nEachAccptFd , buffer, len))
//		{
//			cout<<"write failed!"<<endl;
//			return -4;
//		}
			
		//close(nEachAccptFd);
	}
		close(nEachAccptFd);
	close(server_sockfd);
   	return 0;
}
