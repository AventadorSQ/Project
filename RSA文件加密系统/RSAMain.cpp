#include"BigPrimeRSA.h"

void Test()
{
	RSA passwd;
	std::cout << "RSA" << std::endl;
	Key key = passwd.GetKey();
	std::string str;
	std::cout << "请输入加密数据：";
	std::cin >> str;
	//std::cout << "加密前数据:[" << str << "]\n";
	//加密
	std::vector<BoostMu::int1024_t> StrEcept = passwd.ecrept(str, key.PublicKey, key.PrimeProductKey);
	std::cout << "加密后信息：" << std::endl;
	passwd.PrintEcreptInfo(StrEcept);
	std::string StrOut = passwd.decrept(StrEcept, key.PrivateKey, key.PrimeProductKey);
	std::cout << "解密后信息" << std::endl;
	std::cout << StrOut << std::endl;
}

void TestFile()
{
	RSA f;
	Key key = f.GetKey();//李白.png
	f.ecrept("源文件.txt", "加密后文件.txt", key.PublicKey, key.PrimeProductKey);
	f.decrept("加密后文件.txt", "解密后文件.txt", key.PrivateKey, key.PrimeProductKey);
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