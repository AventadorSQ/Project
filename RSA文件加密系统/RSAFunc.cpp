#include"BigPrimeRSA.h"
#include<time.h>
#include<math.h>
#include<fstream>

//��ȡ��Կ
Key RSA::GetKey()
{
	return _key;
}
//���ļ����м���/����
void RSA::ecrept(const char* PlainFileIn, const char* EcreptFileOut, BoostMu::int1024_t PublicKey, BoostMu::int1024_t PrimeProductKey)
{
	//std::cout << "����ǰ1" << std::endl;
	std::ifstream fin(PlainFileIn, std::ifstream::binary);
	std::ofstream fout(EcreptFileOut, std::ofstream::binary);
	if (!fin.is_open())
	{
		std::cout << "open file error!!!" << std::endl;
		return;
	}
	//���ļ�̫��ʱ
	const int size = 256;
	char buf[size];
	int CurSize;

	std::cout << "���ڼ��ܡ�����" << std::endl;
	BoostMu::int1024_t BufOut[size];
	while (!fin.eof())
	{
		fin.read(buf, size);
		//���˶����ֽ�
		CurSize = fin.gcount();
		for (int i = 0; i < CurSize; i++)
		{
			BufOut[i] = (ecrept(buf[i], PublicKey, PrimeProductKey));
		}
		fout.write((char*)BufOut, CurSize * sizeof(BoostMu::int1024_t));
	}
	std::cout << "���ܳɹ�������" << std::endl;
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

	//���ļ�̫��ʱ
	const int size = 256;
	BoostMu::int1024_t buf[size];
	int CurSize;

	char BufOut[size];
	std::cout << "���ڽ��ܡ�����" << std::endl;
	while (!fin.eof())
	{
		fin.read((char*)buf, size * sizeof(BoostMu::int1024_t));
		//���˶����ֽ�
		CurSize = fin.gcount();
		CurSize /= sizeof(BoostMu::int1024_t);
		for (int i = 0; i < CurSize; i++)
		{
			BufOut[i] = ((char)ecrept(buf[i], PrivateKey, PrimeProductKey));
		}
		fout.write((char*)BufOut, CurSize);
	}
	std::cout << "���ܳɹ�������" << std::endl;

	fin.close();
	fout.close();
}

//��һ�����ݽ��м���/����
std::vector<BoostMu::int1024_t> RSA::ecrept(std::string& StrIn, BoostMu::int1024_t PublicKey, BoostMu::int1024_t PrimeProductKey)
{
	std::vector<BoostMu::int1024_t> arr;
	for (const auto& e : StrIn)
	{
		//std::cout << "����e:[" << e << "]\n";
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

//�Ե������ݽ��мӽ���
BoostMu::int1024_t RSA::ecrept(BoostMu::int1024_t data, BoostMu::int1024_t key, BoostMu::int1024_t PrimeProductKey)
{
	//���������
	//BoostMu::int1024_t temp = (BoostMu::int1024_t)pow(data, key) % PrimeProductKey;
	//return temp;
	//������ȡģ
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

//��ӡ����/��������
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

//�����������
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

//�Ƿ�Ϊ����
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

//���Զ���Key��ֵ
void RSA::CreateKey()
{
	BoostMu::int1024_t prime1 = CreatePrime();
	std::cout << "����1" << std::endl;
	BoostMu::int1024_t prime2 = CreatePrime();
	while (prime1 == prime2)
	{
		prime2 = CreatePrime();
	}
	std::cout << "����2" << std::endl;
	_key.PrimeProductKey = PrimeProduct(prime1, prime2);
	BoostMu::int1024_t orla = OrlaFunc(prime1, prime2);
	_key.PublicKey = CreatePublicKey(orla);
	std::cout << "��Կ" << std::endl;
	_key.PrivateKey = CreatePrivateKey(_key.PublicKey, orla);
	std::cout << "˽Կ" << std::endl;
}

//�������������˻�
BoostMu::int1024_t RSA::PrimeProduct(BoostMu::int1024_t prime1, BoostMu::int1024_t prime2)
{
	return prime1 * prime2;
}

//����ŷ������$n
BoostMu::int1024_t RSA::OrlaFunc(BoostMu::int1024_t prime1, BoostMu::int1024_t prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}

//������ɹ�ԿPublicKey (1 < PublicKey < orla) && (PublicKey �� orla ����) 
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

//���������������Լ��
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


//����˽Կ
BoostMu::int1024_t RSA::CreatePrivateKey(BoostMu::int1024_t PublicKey, BoostMu::int1024_t orla)
{
	BoostMu::int1024_t x, y;
	ExGcd(PublicKey, orla, x, y);

	return (x % orla + orla) % orla;
}

//��չŷ������㷨
//�Ż�����˽Կ
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