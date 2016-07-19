#include <iostream>
#include <string.h>
#include "QRcode_Socket.h"

using namespace std;

int main()
{
	bool init_flag,accept_flag;
	int recv_len,n=0;
	string str_recive;
	QRcode_Socket server_socket;
	if(!server_socket.initQRcode_Socket())
	{
		return -1;
	};

	while(1)
	{
		if(!server_socket.acceptQRcode_Socket())
		{
			return -1;
		}
		recv_len = server_socket.recvQRcode_Socket();
		cout<<server_socket.readBufferQRcode_Socket()<<endl;
		server_socket.sendQRcode_Socket("world",6);
		server_socket.refuseQRcode_Socket();
		n++;
		if(n == 10) break;
	}
	return 0;
}
