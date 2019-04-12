#include"别踩白块.h"

#define BLOCK 100
//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




//WinMain  GUI窗口应用程序
//WINAPI:函数的调用约定

//HINSTANCE hInstance 当前应用程序的实例句柄
//HINSTANCE hPreInstance 当前应用程序的前一个实例
//LPSTR lpCmdLine 命令行参数
//int nCmdShow 窗口显示方式，最大化还是最小化
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//一、做一个窗口
	TCHAR szAppClassName[] = TEXT("别踩白块---Sissors_初夏(琪哥作品)");
	//1.设计窗口类
	WNDCLASS wc;
	//窗口类扩展空间大小
	wc.cbClsExtra = 0;                                        
	//窗口的扩展空间大小
	wc.cbWndExtra = 0;                                         
	 //加载白色背景画刷子
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  
    //加载光标
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//加载图标
	wc.hIcon = NULL;
	//应用程序实例句柄
	wc.hInstance = hInstance;
	//窗口处理函数
	wc.lpfnWndProc = WindowProc;
	//窗口类型名
	wc.lpszClassName = szAppClassName;
	//菜单名
	wc.lpszMenuName = NULL;
	//窗口类的风格
	wc.style = CS_HREDRAW | CS_VREDRAW;

	//2.注册窗口
	RegisterClass(&wc);

	//3.创建窗口
	HWND hWnd = CreateWindow(
		//窗口类型名
		szAppClassName,
		//窗口标题
		TEXT("别踩白块---Sissors_初夏(琪哥作品)"),
		//窗口风格
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		//窗口左上角坐标
		500,100,
		//窗口的宽和高
		//417,440,
		417,640,
		//父窗口句柄
		NULL,
		//菜单句柄
		NULL,
		//应用程序实例句柄
		hInstance,
		//参数
		NULL
	);

	//4.显示窗口
	ShowWindow(hWnd, SW_SHOW);

	//5.更新窗口
	UpdateWindow(hWnd);

	//6.消息循环
	//消息机制驱动运行
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//将虚拟键消息转换成字符信息
		TranslateMessage(&msg);
		//将消息分发给窗口处理函数
		DispatchMessage(&msg);
	}
	return 0;
}


//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	//绘图句柄  DC 设备上下文---微软提供一套库，封装好与各种显示器兼容相关接口
	HDC hDC;
	//每个屏幕有四个黑色方块
	static int bw[4];
	//矩形区域
	RECT rect;

	//画刷句柄
	HBRUSH hBrush;

	//鼠标点击
	POINT point;

	//踩了的格子数
	static int n = 0;

	//所耗时间
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
		//开启定时器
		SetTimer(hWnd, 1, 10, NULL);
	}
			break;

			//定时器
	case WM_TIMER:
		tm++;
		break;
		//窗口绘图消息
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		//画图
		for (int i = 0; i < 5; i++)
		{
			////水平
			//MoveToEx(hDC, 0, i*BLOCK, NULL);
			//LineTo(hDC, 4*BLOCK, i*BLOCK);

			////竖直
			//MoveToEx(hDC, i*BLOCK,0,NULL);
			//LineTo(hDC, i*BLOCK, 4 * BLOCK);
			//水平
			//起点
			MoveToEx(hDC, 0, 1.5 * i * BLOCK, NULL);
			//终点
			LineTo(hDC, 4 * BLOCK, 1.5 * i * BLOCK);

			//竖直
			MoveToEx(hDC, i * BLOCK, 0, NULL);
			LineTo(hDC, i * BLOCK, 6 * BLOCK);
		}
		//画黑色方块
		for (int i = 0; i < 4; i++)
		{
			SetRect(&rect, bw[i] * BLOCK, 1.5 * i * BLOCK, bw[i] * BLOCK + 100, 1.5 * i * BLOCK + 150);
			//设置黑刷子
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			//用黑刷子刷对应方块
			SelectObject(hDC, hBrush);
			Rectangle(hDC, rect.left,rect.top, rect.right, rect.bottom);

			//释放资源
			DeleteObject(hBrush);
		}

		EndPaint(hWnd, &ps);
		break;
		//鼠标左键点击信息
	case WM_LBUTTONDOWN:
	{
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);

		if (point.y / (BLOCK * 1.5) >= 3)
		{
			if (point.x / BLOCK != bw[3])
			{
				wsprintf(szMsg, L"您输了！！！  用时：%d.%d 秒  块数：%d个", tm/100, tm-(tm/100)*100, n);
				MessageBox(hWnd, szMsg, L"温馨提示:", MB_OK);
				//退出
				PostQuitMessage(0);
			}
			//每按一次要往下走一个
			for (int i = 3; i > 0; i--)
			{
				bw[i] = bw[i - 1];
			}
			bw[0] = rand() % 4;
			n++;
			//滚动窗口
			ScrollWindow(hWnd, 0, 1.5 * BLOCK, NULL, NULL);
		}
	}
		break;
		//窗口关闭消息，关闭只是把窗口最小化，还可以恢复
	case WM_CLOSE:
		DestroyWindow(hWnd);//销毁窗口，不可以恢复了
		break;
		//窗口销毁消息
	case WM_DESTROY:
		PostQuitMessage(0);//退出进程
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}