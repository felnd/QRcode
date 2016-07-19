//#include <stdlib.h>  
//#include <sys/types.h>  
//#include <stdio.h>  
//#include <sys/socket.h>  
//#include <linux/in.h>  
//#include <arpa/inet.h>
//#include <string.h>
//#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

#define BUFFER_SIZE 1024
#define SERVER_PORT_NUM 8887

int main()
{
	int iClientFd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == iClientFd)
	{
		cout<<"socket open failed!"<<endl;
		return -1;
	}
	cout<<"socket open is ok!"<<endl;

	struct sockaddr_in s_add;
	bzero(&s_add , sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;  
	s_add.sin_addr.s_addr = inet_addr("192.168.1.101");
	s_add.sin_port = htons(SERVER_PORT_NUM);

	if(-1 == connect(iClientFd , (struct sockaddr *)(&s_add) , sizeof(struct sockaddr)))  
	{  
		cout<<"connect server fail!"<<endl;  
		return -2;  
	}
	cout<<"connect server ok!"<<endl;  

	int iRecBytesSize = 0;
	char cRecBuffer[BUFFER_SIZE] = {0};
	if(-1 == (iRecBytesSize = read(iClientFd , cRecBuffer , BUFFER_SIZE)))  
	{  
	    cout<<"read data fail!"<<endl;  
	    return -3;  
	}	
	cout<<"read is ok!"<<endl;
	cout<<"info from server is "<<cRecBuffer<<endl;
	return 0;
}
