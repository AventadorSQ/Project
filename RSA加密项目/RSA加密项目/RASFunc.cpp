#include"RSA.h"
#include<time.h>
#include<math.h>
#include<fstream>

//��ȡ��Կ
Key RSA::GetKey()
{
	return _key;
}
//���ļ����м���/����
void RSA::ecrept(const char* PlainFileIn, const char* EcreptFileOut, long PublicKey, long PrimeProductKey)
{
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

	long BufOut[size];
	while (!fin.eof())
	{
		fin.read(buf, size);
		//���˶����ֽ�
		CurSize = fin.gcount();
		for (int i = 0; i < CurSize; i++)
		{
			BufOut[i] = (ecrept(buf[i], PublicKey, PrimeProductKey));
		}
		fout.write((char*)BufOut, CurSize * sizeof(long));
	}

	fin.close();
	fout.close();
}
void RSA::decrept(const char* EcreptFileIn, const char* PlainFileOut, long PrivateKey, long PrimeProductKey)
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
	long buf[size];
	int CurSize;

	char BufOut[size];
	while (!fin.eof())
	{
		fin.read((char*)buf, size * sizeof(long));
		//���˶����ֽ�
		CurSize = fin.gcount();
		CurSize /= sizeof(long);
		for (int i = 0; i < CurSize; i++)
		{
			BufOut[i] = ((char)ecrept(buf[i], PrivateKey, PrimeProductKey));
		}
		fout.write((char*)BufOut, CurSize);
	}

	fin.close();
	fout.close();
}

//��һ�����ݽ��м���/����
std::vector<long> RSA::ecrept(std::string& StrIn, long PublicKey, long PrimeProductKey)
{
	std::vector<long> arr;
	for (const auto& e : StrIn)
	{
		//std::cout << "����e:[" << e << "]\n";
		arr.push_back(ecrept(e, PublicKey, PrimeProductKey));
	}
	return arr;
}
std::string RSA::decrept(std::vector<long>& EcreptStr, long PrivateKey, long PrimeProductKey)
{
	std::string StrOut;
	//char tmp[4096] = { 0 };
	//int i = 0;
	for (const auto& e : EcreptStr)
	{
		//char ch = ecrept(e, PrivateKey, PrimeProductKey);
		//tmp[i++] = ch;
		//std::cout << "����c:[" << ch << "[\n";
		StrOut.push_back(ecrept(e, PrivateKey, PrimeProductKey));
	}
	//std::cout << "����tmp:[" << tmp << "]\n";
	//StrOut.assign(tmp, i);
	return StrOut;
}

//�Ե������ݽ��мӽ���
long RSA::ecrept(long data, long key, long PrimeProductKey)
{
	//���������
	//long temp = (long)pow(data, key) % PrimeProductKey;
	//return temp;
	//������ȡģ
	long data_out = 1;
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
void RSA::PrintEcreptInfo(std::vector<long>& EcreptStr)
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
long RSA::CreatePrime()
{
	srand(time(nullptr));
	long prime = 2;
	while (1)
	{
		prime = rand() % 50 + 2;
		if (IsPrime(prime))
		{
			break;
		}
	}
	return prime;
}

//�Ƿ�Ϊ����
bool RSA::IsPrime(long num)
{
	if (num < 2)
	{
		return false;
	}

	for (int i = 2; i <= sqrt(num); i++)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}

//���Զ���Key��ֵ
void RSA::CreateKey()
{
	long prime1 = CreatePrime();
	long prime2 = CreatePrime();
	while (prime1 == prime2)
	{
		prime2 = CreatePrime();
	}
	_key.PrimeProductKey = PrimeProduct(prime1, prime2);
	long orla = OrlaFunc(prime1, prime2);
	_key.PublicKey = CreatePublicKey(orla);
	_key.PrivateKey = CreatePrivateKey(_key.PublicKey, orla);
}

//�������������˻�
long RSA::PrimeProduct(long prime1, long prime2)
{
	return prime1 * prime2;
}

//����ŷ������$n
long RSA::OrlaFunc(long prime1, long prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}

//������ɹ�ԿPublicKey (1 < PublicKey < orla) && (PublicKey �� orla ����) 
long RSA::CreatePublicKey(long orla)
{
	long PublicKey;
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
long RSA::CreateGcd(long PublicKey, long orla)
{
	long temp;
	while (temp = PublicKey % orla)
	{
		PublicKey = orla;
		orla = temp;
	}
	return orla;
}

//����˽Կ
long RSA::CreatePrivateKey(long PublicKey, long orla)
{
	long PrivateKey = orla / PublicKey;
	while (1)
	{
		if ((PrivateKey * PublicKey) % orla == 1)
		{
			break;
		}
		PrivateKey++;
	}
	return PrivateKey;
}