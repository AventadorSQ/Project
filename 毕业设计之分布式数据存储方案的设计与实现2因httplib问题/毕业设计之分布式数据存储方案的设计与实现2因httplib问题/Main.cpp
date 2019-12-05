#include "StructDataStorageClientRegister.hpp"

//²âÊÔÓÃ»§µÇÂ¼
int main()
{
	int num = 0;
	CreateClient Client;
	cout << "×¢²áÇëÊäÈë1£¬µÇÂ¼ÇëÊäÈë2" << endl;
	cin >> num;
	if (num == 1)
	{
		Client.ClientZhuCe();
	}
	Client.ClientRegister();
	system("pause");
	return 0;
}

