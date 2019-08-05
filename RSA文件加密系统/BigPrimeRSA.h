#pragma once

#include<vector>
#include<string>
#include<iostream>
#include<boost/multiprecision/cpp_int.hpp>
namespace BoostMu = boost::multiprecision;
#include<boost/multiprecision/random.hpp>
namespace BoostRa = boost::random;
#include<boost/multiprecision/miller_rabin.hpp>

//自定义密钥类型
struct Key
{
	//公钥(PublicKey, PrimeProductKey)
	BoostMu::int1024_t PublicKey;
	//私钥(PrivateKey, PrimeProductKey)
	BoostMu::int1024_t PrivateKey;
	BoostMu::int1024_t PrimeProductKey;
};

class RSA
{
public:
	RSA();
public:
	//获取密钥
	Key GetKey();

	//对文件进行加密/解密
	void ecrept(const char* PlainFileIn, const char* EcreptFileOut, BoostMu::int1024_t PublicKey, BoostMu::int1024_t PrimeProductKey);
	void decrept(const char* EcreptFileIn, const char* PlainFileOut, BoostMu::int1024_t PrivateKey, BoostMu::int1024_t PrimeProductKey);

	//对一串数据进行加密/解密
	std::vector<BoostMu::int1024_t> ecrept(std::string& StrIn, BoostMu::int1024_t PublicKey, BoostMu::int1024_t PrimeProductKey);
	std::string decrept(std::vector<BoostMu::int1024_t>& EcreptStr, BoostMu::int1024_t PrivateKey, BoostMu::int1024_t PrimeProductKey);

	//对单独数据进行加解密
	BoostMu::int1024_t ecrept(BoostMu::int1024_t data, BoostMu::int1024_t key, BoostMu::int1024_t PrimeProductKey);

	//打印加密/解密数据
	void PrintEcreptInfo(std::vector<BoostMu::int1024_t>& EcreptStr);
private:
	//生成素数
	BoostMu::int1024_t CreatePrime();

	//是否为素数
	bool IsPrime(BoostMu::int1024_t num);

	//生成所需的密钥
	void CreateKey();

	//计算两个素数乘积
	BoostMu::int1024_t PrimeProduct(BoostMu::int1024_t prime1, BoostMu::int1024_t prime2);

	//计算欧拉函数$n
	BoostMu::int1024_t OrlaFunc(BoostMu::int1024_t prime1, BoostMu::int1024_t prime2);

	//生成公钥PublicKey
	BoostMu::int1024_t CreatePublicKey(BoostMu::int1024_t orla);

	//计算两个数的最大公约数
	BoostMu::int1024_t CreateGcd(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla);

	//扩展欧几里得算法
	//优化生成私钥
	BoostMu::int1024_t ExGcd(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla, BoostMu::int1024_t& x, BoostMu::int1024_t& y);

	//生成私钥
	BoostMu::int1024_t CreatePrivateKey(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla);
private:
	Key _key;
};