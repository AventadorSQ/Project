#pragma once

#define _SCL_SECURE_NO_WARNINGS
#include "SendEmail.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

//�û�ע���¼�Լ��һ�����
class CreateClient
{
public:
	CreateClient()
	{
		_VerificationCode.resize(6);
	}
public:
	//�û�ע��
	void ClientZhuCe()
	{
		string EmailName;
		cout << "��������ע�������ȫ��(����.com)��";
		cin >> EmailName;
		//�ж��Ƿ��Ѿ�ע��*************************************************
		//ͨ���������󵽷��������Ѿ�ע����û��в����Ƿ��и��û������û�м���ע�ᣬ��������û��Ѿ�ע��


		//���û��ע��
		_EmailName = EmailName;
		//��ȡ��λ�����֤��
		GetRandNumber();
		//������֤��
		SendVerificationCode(_VerificationCode);
		cout << "��֤���ѷ�������������������Ч" << endl;
		cout << "��������λ��֤�룺";

		string IsVerificationCode;
		cin >> IsVerificationCode;
		//�ж���֤���Ƿ���ȷ,����������·�����֤��
		while (!IsVerificationCodeSuccess(IsVerificationCode))
		{

			//��ȡ��λ�����֤��
			GetRandNumber();
			//������֤��
			SendVerificationCode(_VerificationCode);
			cout << "��֤�������·�������������������Ч" << endl;
			cout << "��������λ��֤�룺";
			cin >> IsVerificationCode;
		}

		//��������
		string passwd;
		passwd.resize(10);
		cout << "�����뵱ǰע���˺ŵ�������(����<=10)��";
		cin >> passwd;
		while (!IsClientZhuCeLengthSuccess(passwd))
		{
			cout << "���������뵱ǰע���˺ŵ�������(����<=10)��";
			cin >> passwd;
		}
		_passwd = passwd;
		cout << "******ע��ɹ�******" << endl;
	}
	//��֤��ķ���
	void SendVerificationCode(string VerificationCode)
	{
		CSmtp smtp(
			25,								 //smtp�˿�
			"smtp.163.com",					 //smtp��������ַ
			"18391433268@163.com",	         //��������ַ
			"yidingbu!123",					 //��������
			_EmailName,	                     //Ŀ�������ַ
			"�ֲ�ʽ���ݴ洢ϵͳע����",      //����
			VerificationCode                 //�ʼ�����
		);
		int err;
		if ((err = smtp.SendEmail_Ex()) != 0)
		{
			if (err == 1)
				cout << "����1: �������粻��ͨ������ʧ��!" << endl;
			if (err == 2)
				cout << "����2: �û�������,��˶�!" << endl;
			if (err == 3)
				cout << "����3: �û����������˶�!" << endl;
			if (err == 4)
				cout << "����4: ���鸽��Ŀ¼�Ƿ���ȷ���Լ��ļ��Ƿ����!" << endl;
		}
	}
	//����6λ�����
	void GetRandNumber()
	{
		//���ڱ������ɵ������
		vector<int> vRandNum;
		vRandNum.resize(6);
		//�����������
		srand((unsigned int)time(NULL));
		//����6λ�����
		for (int i = 0; i < 6; i++)
		{
			size_t num = rand() % 10;
			vRandNum[i] = num + '0';
			_VerificationCode[i] = vRandNum[i];
		}
	}

	//�ж���֤���Ƿ���ȷ
	bool IsVerificationCodeSuccess(string IsVerificationCode)
	{
		//���ж���֤�볤���Ƿ�һ��,���ж���֤���Ƿ�һ��
		if (IsVerificationCode.size() == _VerificationCode.size())
		{
			for (int i = 0; i < 6; i++)
			{
				if ((IsVerificationCode[i] - '0') != (_VerificationCode[i] - '0'))
				{
					cout << "��֤��������󣡣���" << endl;
					return false;
				}
			}
			return true;
		}
		return false;
	}

	//ע���û����볤���Ƿ�ϸ�
	bool IsClientZhuCeLengthSuccess(string passwd)
	{
		if (passwd.size() <= 10)
		{
			return true;
		}
		return false;
	}

	//�û���¼
	void ClientRegister()
	{
		string EmailName;
		string passwd;
		cout << "�������¼���û�����";
		cin >> EmailName;
		cout << "����������";
		cin >> passwd;

		//���ڼ�¼��¼ʧ�ܴ�������������ֱ�������һ�����
		int PasswdCount = 0;
		//��Ҫ���ӷ����������ж�*************************************

		while (!IsSuccessClientRegister(EmailName, passwd))
		{
			PasswdCount++;
			if (PasswdCount < 4)
			{
				cout << "�����µ�½��";
				cout << "�������¼���û�����";
				cin >> EmailName;
				cout << "����������";
				cin >> passwd;
			}
			else
			{
				//�һ�����
				ClientFindPasswd();
				break;
			}
		}

		cout << "******��½�ɹ�******" << endl;
	}

	//�жϵ�¼�û����������Ƿ���ȷ
	bool IsSuccessClientRegister(string& EmailName, string& passwd)
	{
		if ((EmailName == _EmailName) && (passwd == _passwd))
		{
			return true;
		}
		cout << "�û����������¼����" << endl;
		return false;
	}
	//�û��һ�����
	void ClientFindPasswd()
	{
		string EmailName;
		cout << "�������û�����";
		cin >> EmailName;
		//������֤��
		SendVerificationCode(_VerificationCode);
		cout << "��֤���ѷ�������������������Ч" << endl;
		cout << "��������λ��֤�룺";

		string IsVerificationCode;
		cin >> IsVerificationCode;
		//�ж���֤���Ƿ���ȷ,����������·�����֤��
		while (!IsVerificationCodeSuccess(IsVerificationCode))
		{

			//��ȡ��λ�����֤��
			GetRandNumber();
			//������֤��
			SendVerificationCode(_VerificationCode);
			cout << "��֤�������·�������������������Ч" << endl;
			cout << "��������λ��֤�룺";
			cin >> IsVerificationCode;
		}

		//��������
		string passwd;
		passwd.resize(10);
		cout << "�����뵱ǰ�һ������˺ŵ�������(����<=10)��";
		cin >> passwd;
		while (!IsClientZhuCeLengthSuccess(passwd))
		{
			cout << "���������뵱ǰ�һ����˺ŵ�������(����<=10)��";
			cin >> passwd;
		}
		_passwd = passwd;
		cout << "******�����������óɹ�******" << endl;
	}

private:
	string _EmailName;        //163����
	string _VerificationCode; //��֤��
	string _passwd;           //����
};

int main()
{
	int num = 0;
	CreateClient Client;
	cout << "ע��������1����¼������2" << endl;
	cin >> num;
	if (num == 1)
	{
		Client.ClientZhuCe();
	}
	Client.ClientRegister();
	system("pause");
	return 0;
}