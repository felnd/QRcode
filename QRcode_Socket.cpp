#include "QRcode_Socket.h"

using namespace std;

QRcode_Socket::QRcode_Socket():
port(8887),server_socket(0),num_accept(0)
{
}

QRcode_Socket::QRcode_Socket(unsigned int myport):
port(myport),server_socket(0),num_accept(0)
{

}

QRcode_Socket::~QRcode_Socket()
{
	close(server_socket);	
}

bool QRcode_Socket::initQRcode_Socket()
{
	this->server_socket = socket(AF_INET,SOCK_STREAM,0);
	this->server_sockaddr.sin_family = AF_INET;
	this->server_sockaddr.sin_port = htons(this->port);
	this->server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//bind,成功返回0，出错返回-1
	if(-1 == bind(server_socket,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr)))
	{
		perror("error at bind");
		return false;
	}
//listen，成功返回0，出错返回-1
	if(-1 == listen(server_socket,QUEUE))
	{
		perror("error at listen");
		return false;
	}
		return true;	
}

int QRcode_Socket::recvQRcode_Socket()
{
	memset(this->buffer,0,sizeof(buffer));
	int len = recv(num_accept,this->buffer,sizeof(buffer),0);
	return len;
}

void QRcode_Socket::sendQRcode_Socket(const char * str_send,unsigned int len)
{
	send(num_accept,str_send,len,0);	
}

bool QRcode_Socket::acceptQRcode_Socket()
{
	int sockaddr_size = sizeof(struct sockaddr_in);	
	num_accept = accept(server_socket,(struct sockaddr *)&client_sockaddr,(socklen_t *)&sockaddr_size);
	if (-1 == num_accept)
	{
		perror("accept failed!");
		return false;
	}
		return true;
}

void QRcode_Socket::refuseQRcode_Socket()
{
	close(num_accept);
}

string QRcode_Socket::readBufferQRcode_Socket()
{
	string str_buffer(this->buffer);
	return str_buffer;
}














