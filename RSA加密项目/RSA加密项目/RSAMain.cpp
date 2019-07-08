#include"RSA.h"

void Test()
{
	RSA passwd;
	Key key = passwd.GetKey();
	std::string str;
	std::cout << "请输入加密数据：";
	std::cin >> str;
	//std::cout << "加密前数据:[" << str << "]\n";
	//加密
	std::vector<long> StrEcept = passwd.ecrept(str, key.PublicKey, key.PrimeProductKey);
	std::cout << "加密后信息："<< std::endl;
	passwd.PrintEcreptInfo(StrEcept);
	std::string StrOut = passwd.decrept(StrEcept, key.PrivateKey, key.PrimeProductKey);
	std::cout << "解密后信息" << std::endl;
	std::cout << StrOut << std::endl;
}

void TestFile()
{
	RSA f;
	Key key = f.GetKey();
	f.ecrept("图片1.png", "加密后文件.png", key.PublicKey, key.PrimeProductKey);
	f.decrept("加密后文件.png", "解密后文件.png", key.PrivateKey, key.PrimeProductKey);
}
int main()
{
	//Test();
	TestFile();
	system("pause");
	return 0;
}