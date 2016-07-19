#include "QRcodeManager.h"
#include <string.h>
#include <mysql/mysql.h>


QRcodeManager::QRcodeManager():
IsConnected(false),DetectFlag(false),result(NULL),row(NULL)
{
}

QRcodeManager::~QRcodeManager()
{
	if(getConnectionStatus())   //如果保持链接则断开链接
	{
			this->destroyConnection();
	}		
}
//初始化mysql链接
void QRcodeManager::initConnection()
{
	if(!getConnectionStatus())
	{
		mysql_init(&mysql);
    	if(mysql_real_connect(
						&mysql,
						"localhost",
						"zhoufeizhou",
						NULL,
						"QRcode_base",
						3306,
						NULL,
						0))
		{
		this->IsConnected = true;

		mysql_query(&mysql,"SET NAMES UTF8");
		}
	}
}
//断开mysql链接
void QRcodeManager::destroyConnection()
{
	this->IsConnected = false;
	mysql_close(&mysql);	
}
//输出链接状态
bool QRcodeManager::getConnectionStatus()
{
	return this->IsConnected;
}
//输出搜索结果
bool QRcodeManager::getResult()
{
	return this->DetectFlag;
}
//执行查找与检测真伪性
bool QRcodeManager::runDetect(const char * numbers)
{
	string str_num(numbers);
	if(!numDetect(str_num)||(str_num.size()!=NUMLEN))
    {
		cout<<numbers<<str_num<<"input numbers wrong"<<endl;
		this->DetectFlag = false;
			return false;      //输出错误
	}
	string sql = "call QRcode_scan('"+str_num+"',@a)";
	mysql_query(&mysql,sql.c_str());
	mysql_query(&mysql,"SELECT @a");
	this->result = mysql_store_result(&mysql);
	int row_count = mysql_num_rows(result);
	if(row_count ==1)            //此ID存在且仅有一条记录
	{
		row = mysql_fetch_row( result);    //typedef char **MYSQL_ROW
		string flag = "F";	
		cout<<row[0][0]<<"\t"<<endl;//strcmp(static_cast<string>(row[0]),flag)<<endl;
//		if(strcmp(row[0],"F"))         //此ID未曾检测过，true
		if(row[0][0]=='F')//此ID未曾检测过，true
		{
			cout<<row[0]<<endl;
			this->DetectFlag = true;
			sql = "call QRcode_set('"+str_num+"')";    //设置此ID被检测
			mysql_query(&mysql,sql.c_str());
		}
		else                    //此ID曾被检测过,false
		{
			this->DetectFlag = false;
		}
			return true;         //正常执行
	}
	else if(row_count > 1)      //此ID存在但包含多条记录，数据库出错,false
	{
		this->DetectFlag = false;
		cout<<"DataBase_error at ProductID = "<<str_num <<endl;
			return false;         //不正常执行
	}
	else                        //此ID不存在,false
	{
		this->DetectFlag = false;
			return false;         //不正常执行
	}
}

bool QRcodeManager::numDetect(const string num)
{
	for (int i =0 ;i < NUMLEN;i++)
	{
		if(!isdigit(num[i])) return false;
	}
	return true;
}
