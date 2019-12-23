#include "ClientRegister.hpp"
#include "ClientBackupFile.hpp"
#include "ClientGetBackupFileInfoAndPath.hpp"

//*******************************************************用户登录*******************************************************
void ClientRegister(string& EmailName)
{

	//用户登录成功标志位
	int DengLuFlag = 0;
	CreateClient Client;
	while (DengLuFlag == 0)
	{
		string num;
		num.resize(1);
		cout << "*********************************************************************************" << endl;
		cout << "*************     注册请输入:1，登录请输入:2，找回密码请输入:3      *************" << endl;
		cout << "*********************************************************************************" << endl;
		cout << "*** 请输入你的选择：";
		cin >> num;
		if (num[0] == '1' && num.size() == 1)
		{
			//用户注册
			Client.ClientZhuCe();
		}
		else if (num[0] == '2' && num.size() == 1)
		{
			//用户登录
			if (Client.ClientRegister(EmailName))
			{
				DengLuFlag = 1;
			}
		}
		else if (num[0] == '3' && num.size() == 1)
		{
			//找回密码
			Client.ClientFindPasswd();
		}
	}
}

//*******************************************************用户上传文件*******************************************************
void ClientBackupFileHandle(std::string& EmailName)
{
	//用户终止上传文件标志位
	string BackupFlag;
	BackupFlag.resize(1);
	//1.上传文件
	ClientBackupFile FileHandle;
	FileHandle.GetBackupFileInfo();
	while (1)
	{
		FileHandle.ListenFileDirectory(BACKUPFILE_PATH, EmailName);
		FileHandle.WriteBackFileInfo();
		cout << endl;
		cout << "***************************************************************************************************" << endl;
		cout << "**********      继续上传文件请输入:1       *******       退出上传文件请输入:q            **********" << endl;
		cout << "***************************************************************************************************" << endl;
		cout << "*** 请输入你的选择：";
		cin >> BackupFlag;
		if (!(BackupFlag[0] == '1' && BackupFlag.size() == 1))
		{
			break;
		}
	}
}

//*******************************************************用户查询文件*********************************************************
void GetBackupFileInfo(std::string& EmailName)
{
	string num;
	GetBackupInfoAndPath Handle(EmailName);
	while (1)
	{
		num.clear();
		num.resize(1);
		cout << endl;
		cout << "***************************************************************************************" << endl;
		cout << "****************           查找文件是否已经上传请输入:1               *****************" << endl;
		cout << "****************           获取全部已备份文件名请输入:2               *****************" << endl;
		cout << "****************         获取全部备份文件详细信息输入:3               *****************" << endl;
		cout << "****************               退出获取文件信息请输入:q               *****************" << endl;
		cout << "***************************************************************************************" << endl;
		cout << "*** 请输入你的选择：";
		cin >> num;
		if (num[0] == '1' && num.size() == 1)
		{
			std::cout << "请输入要查找的文件名：";
			string FileName;
			cin >> FileName;
			Handle.SelectClientFileIsBackup(FileName);
		}
		else if (num[0] == '2'&& num.size() == 1)
		{
			Handle.GetClientAllFileName();
		}
		else if (num[0] == '3' && num.size() == 1)
		{
			Handle.GetClientAllFileNameAndSize();
		}
		else if (num[0] == 'q' && num.size() == 1)
		{
			break;
		}
		else
		{
			cout << "！！！你的输入错误，请重新选择！！！" << endl;
		}
	}
}

//*******************************************************用户下载文件*********************************************************
void GetBackupFileDownLoadPath(std::string& EmailName)
{
	GetBackupInfoAndPath Handle(EmailName);
	string num;
	while (1)
	{
		num.clear();
		num.resize(1);
		cout << endl;
		cout << "***************************************************************************************" << endl;
		cout << "****************           获取指定文件下载路径请输入:1               *****************" << endl;
		cout << "****************           获取全部文件下载路径请输入:2               *****************" << endl;
		cout << "****************           退出获取文件下载地址请输入:q               *****************" << endl;
		cout << "***************************************************************************************" << endl;
		cout << "*** 请输入你的选择：";
		cin >> num;
		if (num[0] == '1' && num.size() == 1)
		{
			string FileName;
			cout << "请输入需要获取下载地址的文件名：";
			cin >> FileName;
			if (Handle.SelectClientFileIsBackup(FileName) == true)
			{
				Handle.GetClientThisFileDownloadPath(FileName);
			}
		}
		else if (num[0] == '2' && num.size() == 1)
		{
			Handle.GetClientAllFileDownloadPath();
		}
		else if (num[0] == 'q' && num.size() == 1)
		{
			break;
		}
		else
		{
			cout << "！！！你的输入错误，请重新选择！！！" << endl;
		}
	}
}

//****************************************************************用户操作******************************************************************
void ClientHandle(string& EmailName)
{
	string ClientQuitFlag;
	string num;
	num.resize(1);
	while (ClientQuitFlag != "quit")
	{
		cout << endl;
		cout << "********************************************************************************************************" << endl;
		cout << "********  上传文件请输入:1  ******   查看已备份文件请输入:2  ******  获取文件下载地址请输入:3  *********" << endl;
		cout << "********************************************************************************************************" << endl;
		cout << "*** 请输入你的选择：";
		cin >> num;
		if (num[0] == '1' && num.size() == 1)
		{
			//1.上传文件
			ClientBackupFileHandle(EmailName);
			cout << endl;
			cout << "****************************************************************************" << std::endl;
			cout << "******    继续操作请输入：666     ******     退出程序请输入：quit     ******" << std::endl;
			cout << "****************************************************************************" << std::endl;
			cout << "**请输入你的选择：" << std::endl;
			cin >> ClientQuitFlag;
		}
		else if (num[0] == '2' && num.size() == 1)
		{
			//2.获取已上传文件信息
			GetBackupFileInfo(EmailName);
			cout << endl;
			cout << "****************************************************************************" << std::endl;
			cout << "******    继续操作请输入：666     ******     退出程序请输入：quit     ******" << std::endl;
			cout << "****************************************************************************" << std::endl;
			cout << "**请输入你的选择：" << std::endl;
			cin >> ClientQuitFlag;
		}
		else if (num[0] == '3' && num.size() == 1)
		{
			//3.获取文件下载地址
			GetBackupFileDownLoadPath(EmailName);
			cout << endl;
			cout << "****************************************************************************" << std::endl;
			cout << "******    继续操作请输入：666     ******     退出程序请输入：quit     ******" << std::endl;
			cout << "****************************************************************************" << std::endl;
			cout << "**请输入你的选择：" << std::endl;
			cin >> ClientQuitFlag;
		}
	}
}

int main()
{
	//用户登录名
	string EmailName;
	//用户登录操作
	ClientRegister(EmailName);

	//用户文件操作
	ClientHandle(EmailName);
	system("pause");
	return 0;
}