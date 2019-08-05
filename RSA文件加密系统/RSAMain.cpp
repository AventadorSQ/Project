#include"BigPrimeRSA.h"

void Test()
{
	RSA passwd;
	std::cout << "RSA" << std::endl;
	Key key = passwd.GetKey();
	std::string str;
	std::cout << "������������ݣ�";
	std::cin >> str;
	//std::cout << "����ǰ����:[" << str << "]\n";
	//����
	std::vector<BoostMu::int1024_t> StrEcept = passwd.ecrept(str, key.PublicKey, key.PrimeProductKey);
	std::cout << "���ܺ���Ϣ��" << std::endl;
	passwd.PrintEcreptInfo(StrEcept);
	std::string StrOut = passwd.decrept(StrEcept, key.PrivateKey, key.PrimeProductKey);
	std::cout << "���ܺ���Ϣ" << std::endl;
	std::cout << StrOut << std::endl;
}

void TestFile()
{
	RSA f;
	Key key = f.GetKey();//���.png
	f.ecrept("Դ�ļ�.txt", "���ܺ��ļ�.txt", key.PublicKey, key.PrimeProductKey);
	f.decrept("���ܺ��ļ�.txt", "���ܺ��ļ�.txt", key.PrivateKey, key.PrimeProductKey);
}

void TestBigInter()
{
	BoostMu::cpp_int num("123456789987654321001234567899876543210");
	std::cout << num / 2 << std::endl;
	std::cout << num << std::endl;
	std::cout << pow(num, 15)<< std::endl;
}

int main()
{
	//Test();
	TestFile();
	//TestBigInter();
	system("pause");
	return 0;
}