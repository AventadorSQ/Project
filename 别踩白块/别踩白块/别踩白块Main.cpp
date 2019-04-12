#include"��Ȱ׿�.h"

#define BLOCK 100
//���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




//WinMain  GUI����Ӧ�ó���
//WINAPI:�����ĵ���Լ��

//HINSTANCE hInstance ��ǰӦ�ó����ʵ�����
//HINSTANCE hPreInstance ��ǰӦ�ó����ǰһ��ʵ��
//LPSTR lpCmdLine �����в���
//int nCmdShow ������ʾ��ʽ����󻯻�����С��
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//һ����һ������
	TCHAR szAppClassName[] = TEXT("��Ȱ׿�---Sissors_����(������Ʒ)");
	//1.��ƴ�����
	WNDCLASS wc;
	//��������չ�ռ��С
	wc.cbClsExtra = 0;                                        
	//���ڵ���չ�ռ��С
	wc.cbWndExtra = 0;                                         
	 //���ذ�ɫ������ˢ��
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  
    //���ع��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//����ͼ��
	wc.hIcon = NULL;
	//Ӧ�ó���ʵ�����
	wc.hInstance = hInstance;
	//���ڴ�����
	wc.lpfnWndProc = WindowProc;
	//����������
	wc.lpszClassName = szAppClassName;
	//�˵���
	wc.lpszMenuName = NULL;
	//������ķ��
	wc.style = CS_HREDRAW | CS_VREDRAW;

	//2.ע�ᴰ��
	RegisterClass(&wc);

	//3.��������
	HWND hWnd = CreateWindow(
		//����������
		szAppClassName,
		//���ڱ���
		TEXT("��Ȱ׿�---Sissors_����(������Ʒ)"),
		//���ڷ��
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		//�������Ͻ�����
		500,100,
		//���ڵĿ�͸�
		//417,440,
		417,640,
		//�����ھ��
		NULL,
		//�˵����
		NULL,
		//Ӧ�ó���ʵ�����
		hInstance,
		//����
		NULL
	);

	//4.��ʾ����
	ShowWindow(hWnd, SW_SHOW);

	//5.���´���
	UpdateWindow(hWnd);

	//6.��Ϣѭ��
	//��Ϣ������������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//���������Ϣת�����ַ���Ϣ
		TranslateMessage(&msg);
		//����Ϣ�ַ������ڴ�����
		DispatchMessage(&msg);
	}
	return 0;
}


//���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	//��ͼ���  DC �豸������---΢���ṩһ�׿⣬��װ���������ʾ��������ؽӿ�
	HDC hDC;
	//ÿ����Ļ���ĸ���ɫ����
	static int bw[4];
	//��������
	RECT rect;

	//��ˢ���
	HBRUSH hBrush;

	//�����
	POINT point;

	//���˵ĸ�����
	static int n = 0;

	//����ʱ��
	static int tm = 0;

	TCHAR szMsg[200];
	switch (uMsg)
	{
	case WM_CREATE:
	{
		srand((unsigned int)time(NULL));
		for (int i = 0; i < 4; i++)
		{
			bw[i] = rand() % 4;
		}
		//������ʱ��
		SetTimer(hWnd, 1, 10, NULL);
	}
			break;

			//��ʱ��
	case WM_TIMER:
		tm++;
		break;
		//���ڻ�ͼ��Ϣ
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		//��ͼ
		for (int i = 0; i < 5; i++)
		{
			////ˮƽ
			//MoveToEx(hDC, 0, i*BLOCK, NULL);
			//LineTo(hDC, 4*BLOCK, i*BLOCK);

			////��ֱ
			//MoveToEx(hDC, i*BLOCK,0,NULL);
			//LineTo(hDC, i*BLOCK, 4 * BLOCK);
			//ˮƽ
			//���
			MoveToEx(hDC, 0, 1.5 * i * BLOCK, NULL);
			//�յ�
			LineTo(hDC, 4 * BLOCK, 1.5 * i * BLOCK);

			//��ֱ
			MoveToEx(hDC, i * BLOCK, 0, NULL);
			LineTo(hDC, i * BLOCK, 6 * BLOCK);
		}
		//����ɫ����
		for (int i = 0; i < 4; i++)
		{
			SetRect(&rect, bw[i] * BLOCK, 1.5 * i * BLOCK, bw[i] * BLOCK + 100, 1.5 * i * BLOCK + 150);
			//���ú�ˢ��
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			//�ú�ˢ��ˢ��Ӧ����
			SelectObject(hDC, hBrush);
			Rectangle(hDC, rect.left,rect.top, rect.right, rect.bottom);

			//�ͷ���Դ
			DeleteObject(hBrush);
		}

		EndPaint(hWnd, &ps);
		break;
		//�����������Ϣ
	case WM_LBUTTONDOWN:
	{
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);

		if (point.y / (BLOCK * 1.5) >= 3)
		{
			if (point.x / BLOCK != bw[3])
			{
				wsprintf(szMsg, L"�����ˣ�����  ��ʱ��%d.%d ��  ������%d��", tm/100, tm-(tm/100)*100, n);
				MessageBox(hWnd, szMsg, L"��ܰ��ʾ:", MB_OK);
				//�˳�
				PostQuitMessage(0);
			}
			//ÿ��һ��Ҫ������һ��
			for (int i = 3; i > 0; i--)
			{
				bw[i] = bw[i - 1];
			}
			bw[0] = rand() % 4;
			n++;
			//��������
			ScrollWindow(hWnd, 0, 1.5 * BLOCK, NULL, NULL);
		}
	}
		break;
		//���ڹر���Ϣ���ر�ֻ�ǰѴ�����С���������Իָ�
	case WM_CLOSE:
		DestroyWindow(hWnd);//���ٴ��ڣ������Իָ���
		break;
		//����������Ϣ
	case WM_DESTROY:
		PostQuitMessage(0);//�˳�����
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}