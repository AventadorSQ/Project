#pragma once
#include<vector>
#include<string>
#include<iostream>
//自定义密钥类型
struct Key
{
	//公钥(PublicKey, PrimeProductKey)
	long PublicKey;
	//私钥(PrivateKey, PrimeProductKey)
	long PrivateKey;
	long PrimeProductKey;
};

class RSA
{
public:
	RSA();
public:
	//获取密钥
	Key GetKey();

	//对文件进行加密/解密
	void ecrept(const char* PlainFileIn, const char* EcreptFileOut, long PublicKey, long PrimeProductKey);
	void decrept(const char* EcreptFileIn, const char* PlainFileOut, long PrivateKey, long PrimeProductKey);

	//对一串数据进行加密/解密
	std::vector<long> ecrept(std::string& StrIn, long PublicKey, long PrimeProductKey);
	std::string decrept(std::vector<long>& EcreptStr, long PrivateKey, long PrimeProductKey);

	//对单独数据进行加解密
	long ecrept(long data, long key, long PrimeProductKey);

	//打印加密/解密数据
	void PrintEcreptInfo(std::vector<long>& EcreptStr);
private:
	//生成素数
	long CreatePrime();

	//是否为素数
	bool IsPrime(long num);

	//生成所需的密钥
	void CreateKey();

	//计算两个素数乘积
	long PrimeProduct(long prime1, long prime2);

	//计算欧拉函数$n
	long OrlaFunc(long prime1, long prime2);

	//生成公钥PublicKey
	long CreatePublicKey(long orla);

	//计算两个数的最大公约数
	long CreateGcd(long PublicKey, long orla);

	//生成私钥
	long CreatePrivateKey(long PublicKey, long orla);
private:
	Key _key;
};