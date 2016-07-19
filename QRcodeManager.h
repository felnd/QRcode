#ifndef QRCODEMANAGER_H_
#define QRCODEMANAGER_H_

#include "QRcodeManager.h"
#include <iostream>
#include <mysql/mysql.h>

#define NUMLEN 4
using namespace std;

class QRcodeManager
{
		public:
				QRcodeManager();
				~QRcodeManager();
				void initConnection();
				bool runDetect(const char * numbers);
				void destroyConnection();
				bool getConnectionStatus();
				bool getResult();
				bool numDetect(const string num);
		private:
				bool IsConnected;
				bool DetectFlag;
				MYSQL_RES *result;
				MYSQL mysql;
				MYSQL_ROW row;
};

#endif 

