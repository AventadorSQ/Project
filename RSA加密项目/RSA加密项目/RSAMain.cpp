#include"RSA.h"

void Test()
{
	RSA passwd;
	Key key = passwd.GetKey();
	std::string str;
	std::cout << "������������ݣ�";
	std::cin >> str;
	//std::cout << "����ǰ����:[" << str << "]\n";
	//����
	std::vector<long> StrEcept = passwd.ecrept(str, key.PublicKey, key.PrimeProductKey);
	std::cout << "���ܺ���Ϣ��"<< std::endl;
	passwd.PrintEcreptInfo(StrEcept);
	std::string StrOut = passwd.decrept(StrEcept, key.PrivateKey, key.PrimeProductKey);
	std::cout << "���ܺ���Ϣ" << std::endl;
	std::cout << StrOut << std::endl;
}

void TestFile()
{
	RSA f;
	Key key = f.GetKey();
	f.ecrept("ͼƬ1.png", "���ܺ��ļ�.png", key.PublicKey, key.PrimeProductKey);
	f.decrept("���ܺ��ļ�.png", "���ܺ��ļ�.png", key.PrivateKey, key.PrimeProductKey);
}
int main()
{
	//Test();
	TestFile();
	system("pause");
	return 0;
}