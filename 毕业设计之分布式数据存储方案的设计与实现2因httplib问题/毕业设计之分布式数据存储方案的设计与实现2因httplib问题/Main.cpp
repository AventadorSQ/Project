#include "StructDataStorageClientRegister.hpp"

//�����û���¼
int main()
{
	int num = 0;
	CreateClient Client;
	cout << "ע��������1����¼������2" << endl;
	cin >> num;
	if (num == 1)
	{
		Client.ClientZhuCe();
	}
	Client.ClientRegister();
	system("pause");
	return 0;
}

