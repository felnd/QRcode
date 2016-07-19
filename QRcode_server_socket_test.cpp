#include <iostream>
#include "QRcode_Socket.h"
#include "QRcodeManager.h"
#include <string.h>

using namespace std;

int main(int argc,char * argv[])
{
	QRcodeManager qrmg;
	QRcode_Socket qrsk;
	int n=0;
    string	result;
	string buffer_read;
	if(!qrsk.initQRcode_Socket())
	{
		return -1;	
	}
	while(1)
	{
		if(!qrsk.acceptQRcode_Socket())
		{
			return -1;
		}
		qrsk.recvQRcode_Socket();

		buffer_read = qrsk.readBufferQRcode_Socket();
		cout<<"buffer"<<buffer_read<<endl;

		qrmg.initConnection();
		if(qrmg.getConnectionStatus())
		{
			qrmg.runDetect(qrsk.readBufferQRcode_Socket().c_str());
			cout<<qrmg.getResult()<<endl;
			result=qrmg.getResult()?"1":"0";
			qrsk.sendQRcode_Socket(result.c_str(),2);
			qrmg.destroyConnection();	
			
		}
		else
			cout<<"connection failed"<<endl;

		qrsk.refuseQRcode_Socket();		
		if(n==10)
			break;
		n++;
	}
	return 1;


}
