#ifndef QRCODESOCKET_H_
#define QRCODESOCKET_H_

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

#define QUEUE  20
#define BUFFER_SIZE 1024

class QRcode_Socket
{
		public:
				QRcode_Socket();
				QRcode_Socket(unsigned int myport);
				~QRcode_Socket();
				bool initQRcode_Socket();
				int recvQRcode_Socket();
				void sendQRcode_Socket(const char * str_send,unsigned int len);
				bool acceptQRcode_Socket();
				void refuseQRcode_Socket();
				string readBufferQRcode_Socket();
		private:
				int server_socket,num_accept;
				struct sockaddr_in server_sockaddr,client_sockaddr;
				char buffer[BUFFER_SIZE];
				unsigned int port;

};
#endif

