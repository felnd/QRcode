#include <iostream>
#include "QRcodeManager.h"

using namespace std;

int main(int argc,char * argv[])
{
	QRcodeManager QRMg;
	QRMg.initConnection();
	if (QRMg.getConnectionStatus())
	{
		QRMg.runDetect("1001");
		cout<<QRMg.getResult()<<endl;
	}
	else
		cout<<"connection failed"<<endl;
	return 0;
}
