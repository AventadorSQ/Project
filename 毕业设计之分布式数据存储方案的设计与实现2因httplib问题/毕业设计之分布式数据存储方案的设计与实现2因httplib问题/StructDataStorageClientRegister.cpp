#pragma once

#define _SCL_SECURE_NO_WARNINGS
#include "SendEmail.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

//用户注册登录以及找回密码
class CreateClient
{
public:
	CreateClient()
	{
		_VerificationCode.resize(6);
	}
public:
	//用户注册
	void ClientZhuCe()
	{
		string EmailName;
		cout << "请输入所注册的邮箱全名(包括.com)：";
		cin >> EmailName;
		//判断是否已经注册*************************************************
		//通过发送请求到服务器在已经注册的用户中查找是否有该用户，如果没有继续注册，如果告诉用户已经注册


		//如果没有注册
		_EmailName = EmailName;
		//获取六位随机验证码
		GetRandNumber();
		//发送验证码
		SendVerificationCode(_VerificationCode);
		cout << "验证码已发到你的邮箱五分钟内有效" << endl;
		cout << "请输入六位验证码：";

		string IsVerificationCode;
		cin >> IsVerificationCode;
		//判断验证码是否正确,如果错误重新发送验证码
		while (!IsVerificationCodeSuccess(IsVerificationCode))
		{

			//获取六位随机验证码
			GetRandNumber();
			//发送验证码
			SendVerificationCode(_VerificationCode);
			cout << "验证码已重新发到你的邮箱五分钟内有效" << endl;
			cout << "请输入六位验证码：";
			cin >> IsVerificationCode;
		}

		//设置密码
		string passwd;
		passwd.resize(10);
		cout << "请输入当前注册账号的新密码(长度<=10)：";
		cin >> passwd;
		while (!IsClientZhuCeLengthSuccess(passwd))
		{
			cout << "请重新输入当前注册账号的新密码(长度<=10)：";
			cin >> passwd;
		}
		_passwd = passwd;
		cout << "******注册成功******" << endl;
	}
	//验证码的发送
	void SendVerificationCode(string VerificationCode)
	{
		CSmtp smtp(
			25,								 //smtp端口
			"smtp.163.com",					 //smtp服务器地址
			"18391433268@163.com",	         //你的邮箱地址
			"yidingbu!123",					 //邮箱密码
			_EmailName,	                     //目的邮箱地址
			"分布式数据存储系统注册码",      //主题
			VerificationCode                 //邮件正文
		);
		int err;
		if ((err = smtp.SendEmail_Ex()) != 0)
		{
			if (err == 1)
				cout << "错误1: 由于网络不畅通，发送失败!" << endl;
			if (err == 2)
				cout << "错误2: 用户名错误,请核对!" << endl;
			if (err == 3)
				cout << "错误3: 用户密码错误，请核对!" << endl;
			if (err == 4)
				cout << "错误4: 请检查附件目录是否正确，以及文件是否存在!" << endl;
		}
	}
	//生成6位随机数
	void GetRandNumber()
	{
		//用于保存生成的随机数
		vector<int> vRandNum;
		vRandNum.resize(6);
		//种随机数种子
		srand((unsigned int)time(NULL));
		//生成6位随机数
		for (int i = 0; i < 6; i++)
		{
			size_t num = rand() % 10;
			vRandNum[i] = num + '0';
			_VerificationCode[i] = vRandNum[i];
		}
	}

	//判断验证码是否正确
	bool IsVerificationCodeSuccess(string IsVerificationCode)
	{
		//先判断验证码长度是否一致,再判断验证码是否一致
		if (IsVerificationCode.size() == _VerificationCode.size())
		{
			for (int i = 0; i < 6; i++)
			{
				if ((IsVerificationCode[i] - '0') != (_VerificationCode[i] - '0'))
				{
					cout << "验证码输入错误！！！" << endl;
					return false;
				}
			}
			return true;
		}
		return false;
	}

	//注册用户密码长度是否合格
	bool IsClientZhuCeLengthSuccess(string passwd)
	{
		if (passwd.size() <= 10)
		{
			return true;
		}
		return false;
	}

	//用户登录
	void ClientRegister()
	{
		string EmailName;
		string passwd;
		cout << "请输入登录的用户名：";
		cin >> EmailName;
		cout << "请输入密码";
		cin >> passwd;

		//用于记录登录失败次数，超过三次直接跳入找回密码
		int PasswdCount = 0;
		//需要连接服务器进行判断*************************************

		while (!IsSuccessClientRegister(EmailName, passwd))
		{
			PasswdCount++;
			if (PasswdCount < 4)
			{
				cout << "请重新登陆：";
				cout << "请输入登录的用户名：";
				cin >> EmailName;
				cout << "请输入密码";
				cin >> passwd;
			}
			else
			{
				//找回密码
				ClientFindPasswd();
				break;
			}
		}

		cout << "******登陆成功******" << endl;
	}

	//判断登录用户名与密码是否正确
	bool IsSuccessClientRegister(string& EmailName, string& passwd)
	{
		if ((EmailName == _EmailName) && (passwd == _passwd))
		{
			return true;
		}
		cout << "用户名或密码登录错误" << endl;
		return false;
	}
	//用户找回密码
	void ClientFindPasswd()
	{
		string EmailName;
		cout << "请输入用户名：";
		cin >> EmailName;
		//发送验证码
		SendVerificationCode(_VerificationCode);
		cout << "验证码已发到你的邮箱五分钟内有效" << endl;
		cout << "请输入六位验证码：";

		string IsVerificationCode;
		cin >> IsVerificationCode;
		//判断验证码是否正确,如果错误重新发送验证码
		while (!IsVerificationCodeSuccess(IsVerificationCode))
		{

			//获取六位随机验证码
			GetRandNumber();
			//发送验证码
			SendVerificationCode(_VerificationCode);
			cout << "验证码已重新发到你的邮箱五分钟内有效" << endl;
			cout << "请输入六位验证码：";
			cin >> IsVerificationCode;
		}

		//设置密码
		string passwd;
		passwd.resize(10);
		cout << "请输入当前找回密码账号的新密码(长度<=10)：";
		cin >> passwd;
		while (!IsClientZhuCeLengthSuccess(passwd))
		{
			cout << "请重新输入当前找回面账号的新密码(长度<=10)：";
			cin >> passwd;
		}
		_passwd = passwd;
		cout << "******密码重新设置成功******" << endl;
	}

private:
	string _EmailName;        //163邮箱
	string _VerificationCode; //验证码
	string _passwd;           //密码
};

int main()
{
	int num = 0;
	CreateClient Client;
	cout << "注册请输入1，登录请输入2" << endl;
	cin >> num;
	if (num == 1)
	{
		Client.ClientZhuCe();
	}
	Client.ClientRegister();
	system("pause");
	return 0;
}