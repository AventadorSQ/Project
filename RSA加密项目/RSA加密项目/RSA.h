#pragma once
#include<vector>
#include<string>
#include<iostream>
//�Զ�����Կ����
struct Key
{
	//��Կ(PublicKey, PrimeProductKey)
	long PublicKey;
	//˽Կ(PrivateKey, PrimeProductKey)
	long PrivateKey;
	long PrimeProductKey;
};

class RSA
{
public:
	RSA();
public:
	//��ȡ��Կ
	Key GetKey();

	//���ļ����м���/����
	void ecrept(const char* PlainFileIn, const char* EcreptFileOut, long PublicKey, long PrimeProductKey);
	void decrept(const char* EcreptFileIn, const char* PlainFileOut, long PrivateKey, long PrimeProductKey);

	//��һ�����ݽ��м���/����
	std::vector<long> ecrept(std::string& StrIn, long PublicKey, long PrimeProductKey);
	std::string decrept(std::vector<long>& EcreptStr, long PrivateKey, long PrimeProductKey);

	//�Ե������ݽ��мӽ���
	long ecrept(long data, long key, long PrimeProductKey);

	//��ӡ����/��������
	void PrintEcreptInfo(std::vector<long>& EcreptStr);
private:
	//��������
	long CreatePrime();

	//�Ƿ�Ϊ����
	bool IsPrime(long num);

	//�����������Կ
	void CreateKey();

	//�������������˻�
	long PrimeProduct(long prime1, long prime2);

	//����ŷ������$n
	long OrlaFunc(long prime1, long prime2);

	//���ɹ�ԿPublicKey
	long CreatePublicKey(long orla);

	//���������������Լ��
	long CreateGcd(long PublicKey, long orla);

	//����˽Կ
	long CreatePrivateKey(long PublicKey, long orla);
private:
	Key _key;
};