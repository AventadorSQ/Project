#include"BigPrimeRSA.h"
#include<time.h>
#include<math.h>
#include<fstream>

//获取密钥
Key RSA::GetKey()
{
	return _key;
}
//对文件进行加密/解密
void RSA::ecrept(const char* PlainFileIn, const char* EcreptFileOut, BoostMu::int1024_t PublicKey, BoostMu::int1024_t PrimeProductKey)
{
	//std::cout << "加密前1" << std::endl;
	std::ifstream fin(PlainFileIn, std::ifstream::binary);
	std::ofstream fout(EcreptFileOut, std::ofstream::binary);
	if (!fin.is_open())
	{
		std::cout << "open file error!!!" << std::endl;
		return;
	}
	//当文件太大时
	const int size = 256;
	char buf[size];
	int CurSize;

	std::cout << "正在加密。。。" << std::endl;
	BoostMu::int1024_t BufOut[size];
	while (!fin.eof())
	{
		fin.read(buf, size);
		//读了多少字节
		CurSize = fin.gcount();
		for (int i = 0; i < CurSize; i++)
		{
			BufOut[i] = (ecrept(buf[i], PublicKey, PrimeProductKey));
		}
		fout.write((char*)BufOut, CurSize * sizeof(BoostMu::int1024_t));
	}
	std::cout << "加密成功！！！" << std::endl;
	fin.close();
	fout.close();
}
void RSA::decrept(const char* EcreptFileIn, const char* PlainFileOut, BoostMu::int1024_t PrivateKey, BoostMu::int1024_t PrimeProductKey)
{
	std::ifstream fin(EcreptFileIn, std::ifstream::binary);
	std::ofstream fout(PlainFileOut, std::ofstream::binary);
	if (!fin.is_open())
	{
		std::cout << "open file error!!!" << std::endl;
		return;
	}

	//当文件太大时
	const int size = 256;
	BoostMu::int1024_t buf[size];
	int CurSize;

	char BufOut[size];
	std::cout << "正在解密。。。" << std::endl;
	while (!fin.eof())
	{
		fin.read((char*)buf, size * sizeof(BoostMu::int1024_t));
		//读了多少字节
		CurSize = fin.gcount();
		CurSize /= sizeof(BoostMu::int1024_t);
		for (int i = 0; i < CurSize; i++)
		{
			BufOut[i] = ((char)ecrept(buf[i], PrivateKey, PrimeProductKey));
		}
		fout.write((char*)BufOut, CurSize);
	}
	std::cout << "解密成功！！！" << std::endl;

	fin.close();
	fout.close();
}

//对一串数据进行加密/解密
std::vector<BoostMu::int1024_t> RSA::ecrept(std::string& StrIn, BoostMu::int1024_t PublicKey, BoostMu::int1024_t PrimeProductKey)
{
	std::vector<BoostMu::int1024_t> arr;
	for (const auto& e : StrIn)
	{
		//std::cout << "加密e:[" << e << "]\n";
		arr.push_back(ecrept(e, PublicKey, PrimeProductKey));
	}
	return arr;
}
std::string RSA::decrept(std::vector<BoostMu::int1024_t>& EcreptStr, BoostMu::int1024_t PrivateKey, BoostMu::int1024_t PrimeProductKey)
{
	std::string StrOut;

	for (const auto& e : EcreptStr)
	{
		StrOut.push_back((char)ecrept(e, PrivateKey, PrimeProductKey));
	}
	return StrOut;
}

//对单独数据进行加解密
BoostMu::int1024_t RSA::ecrept(BoostMu::int1024_t data, BoostMu::int1024_t key, BoostMu::int1024_t PrimeProductKey)
{
	//溢出得问题
	//BoostMu::int1024_t temp = (BoostMu::int1024_t)pow(data, key) % PrimeProductKey;
	//return temp;
	//快速幂取模
	BoostMu::int1024_t data_out = 1;
	while (key)
	{
		if ((key & 1) == 1)
		{
			data_out = (data_out * data) % PrimeProductKey;
		}
		key = key >> 1;
		data = (data * data) % PrimeProductKey;
	}
	return data_out;
}

//打印加密/解密数据
void RSA::PrintEcreptInfo(std::vector<BoostMu::int1024_t>& EcreptStr)
{
	for (const auto& e : EcreptStr)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

RSA::RSA()
{
	CreateKey();
}

//随机生成素数
BoostMu::int1024_t RSA::CreatePrime()
{
	BoostMu::int1024_t prime;
	BoostRa::mt19937 gen(time(nullptr));
	BoostRa::uniform_int_distribution<BoostMu::int1024_t> primeS(2, BoostMu::int1024_t(1) << 128);
	while (1)
	{
		prime = primeS(gen);
		if (IsPrime(prime))
		{
			break;
		}
	}
	return prime;
}

//是否为素数
bool RSA::IsPrime(BoostMu::int1024_t num)
{
	if (num < 2)
	{
		return false;
	}

	BoostRa::mt11213b gen(time(nullptr));
	if (miller_rabin_test(num, 25, gen))
	{
		if (miller_rabin_test((num - 1) / 2, 25, gen))
		{
			return true;
		}
	}
	return false;
	//for (BoostMu::int1024_t i = 2; i <= sqrt(num); i++)
	//{
	//	if (num % i == 0)
	//	{
	//		return false;
	//	}
	//}
	//return true;
}

//对自定义Key赋值
void RSA::CreateKey()
{
	BoostMu::int1024_t prime1 = CreatePrime();
	std::cout << "素数1" << std::endl;
	BoostMu::int1024_t prime2 = CreatePrime();
	while (prime1 == prime2)
	{
		prime2 = CreatePrime();
	}
	std::cout << "素数2" << std::endl;
	_key.PrimeProductKey = PrimeProduct(prime1, prime2);
	BoostMu::int1024_t orla = OrlaFunc(prime1, prime2);
	_key.PublicKey = CreatePublicKey(orla);
	std::cout << "公钥" << std::endl;
	_key.PrivateKey = CreatePrivateKey(_key.PublicKey, orla);
	std::cout << "私钥" << std::endl;
}

//计算两个素数乘积
BoostMu::int1024_t RSA::PrimeProduct(BoostMu::int1024_t prime1, BoostMu::int1024_t prime2)
{
	return prime1 * prime2;
}

//计算欧拉函数$n
BoostMu::int1024_t RSA::OrlaFunc(BoostMu::int1024_t prime1, BoostMu::int1024_t prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}

//随机生成公钥PublicKey (1 < PublicKey < orla) && (PublicKey 与 orla 互质) 
BoostMu::int1024_t RSA::CreatePublicKey(BoostMu::int1024_t orla)
{
	BoostMu::int1024_t PublicKey;
	srand(time(nullptr));
	while (1)
	{
		PublicKey = rand() % orla;
		if ((PublicKey > 1) && (CreateGcd(PublicKey, orla) == 1))
		{
			break;
		}
	}
	return PublicKey;
}

//计算两个数的最大公约数
BoostMu::int1024_t RSA::CreateGcd(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla)
{
	BoostMu::int1024_t temp;
	while (temp = PublicKey % orla)
	{
		PublicKey = orla;
		orla = temp;
	}
	return orla;
}


//生成私钥
BoostMu::int1024_t RSA::CreatePrivateKey(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla)
{
	BoostMu::int1024_t x, y;
	ExGcd(PublicKey, orla, x, y);

	return (x % orla + orla) % orla;
}

//扩展欧几里得算法
//优化生成私钥
BoostMu::int1024_t RSA::ExGcd(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla, BoostMu::int1024_t& x, BoostMu::int1024_t& y)
{
	if (orla == 0)
	{
		x = 1;
		y = 0;
		return PublicKey;
	}
	BoostMu::int1024_t ret = ExGcd(orla, PublicKey % orla, x, y);
	BoostMu::int1024_t x1 = x, y1 = y;
	x = y1;
	y = x1 - (PublicKey / orla) * y1;
	return ret;
}