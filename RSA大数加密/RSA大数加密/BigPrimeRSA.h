#pragma once

#include<vector>
#include<string>
#include<iostream>
#include<boost/multiprecision/cpp_int.hpp>
namespace BoostMu = boost::multiprecision;
#include<boost/multiprecision/random.hpp>
namespace BoostRa = boost::random;
#include<boost/multiprecision/miller_rabin.hpp>

//�Զ�����Կ����
struct Key
{
	//��Կ(PublicKey, PrimeProductKey)
	BoostMu::int1024_t PublicKey;
	//˽Կ(PrivateKey, PrimeProductKey)
	BoostMu::int1024_t PrivateKey;
	BoostMu::int1024_t PrimeProductKey;
};

class RSA
{
public:
	RSA();
public:
	//��ȡ��Կ
	Key GetKey();

	//���ļ����м���/����
	void ecrept(const char* PlainFileIn, const char* EcreptFileOut, BoostMu::int1024_t PublicKey, BoostMu::int1024_t PrimeProductKey);
	void decrept(const char* EcreptFileIn, const char* PlainFileOut, BoostMu::int1024_t PrivateKey, BoostMu::int1024_t PrimeProductKey);

	//��һ�����ݽ��м���/����
	std::vector<BoostMu::int1024_t> ecrept(std::string& StrIn, BoostMu::int1024_t PublicKey, BoostMu::int1024_t PrimeProductKey);
	std::string decrept(std::vector<BoostMu::int1024_t>& EcreptStr, BoostMu::int1024_t PrivateKey, BoostMu::int1024_t PrimeProductKey);

	//�Ե������ݽ��мӽ���
	BoostMu::int1024_t ecrept(BoostMu::int1024_t data, BoostMu::int1024_t key, BoostMu::int1024_t PrimeProductKey);

	//��ӡ����/��������
	void PrintEcreptInfo(std::vector<BoostMu::int1024_t>& EcreptStr);
private:
	//��������
	BoostMu::int1024_t CreatePrime();

	//�Ƿ�Ϊ����
	bool IsPrime(BoostMu::int1024_t num);

	//�����������Կ
	void CreateKey();

	//�������������˻�
	BoostMu::int1024_t PrimeProduct(BoostMu::int1024_t prime1, BoostMu::int1024_t prime2);

	//����ŷ������$n
	BoostMu::int1024_t OrlaFunc(BoostMu::int1024_t prime1, BoostMu::int1024_t prime2);

	//���ɹ�ԿPublicKey
	BoostMu::int1024_t CreatePublicKey(BoostMu::int1024_t orla);

	//���������������Լ��
	BoostMu::int1024_t CreateGcd(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla);

	//��չŷ������㷨
	//�Ż�����˽Կ
	BoostMu::int1024_t ExGcd(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla, BoostMu::int1024_t& x, BoostMu::int1024_t& y);

	//����˽Կ
	BoostMu::int1024_t CreatePrivateKey(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla);
private:
	Key _key;
};