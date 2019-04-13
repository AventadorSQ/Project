/*
  ���������Ŀ
  ��Ŀ���̣�
  1��������Դ
  2������ť
  3����ʾͼƬ
  4���û������������ť�¼���
*/

//C���Ա�׼ͷ�ļ�
//ͼ�ο�ͷ�ļ�: graphics.h
//��ѧ����: math.h
//��������:mmsystem.h
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

//*****************************************************
//3.����ť
//x,y ��ťλ�á�postion �����ҷ���ť
void DrawButton(int x, int y, char postion);
//4.�û��������
void UserMoveMouse();
//5.��������Ƿ��ڰ�ť��
void ClickButton(int x, int y, char postion);
//6.��ʾСͼƬ�߿��Է���֪���л�����һ��
void DrawRect(int flag);
//******************************************************


//**************************************
//��������Ҫһ������
//N�Ŵ�ͼƬ�����鳤��ΪN����
//N��СͼƬ�����鳤��ΪN����
//**************************************

//��ű���
IMAGE backImg;
//������Ŵ�ͼƬ
IMAGE BigPicture[6];
//�������СͼƬ
IMAGE SmallPicture[6];
//��¼����ͼƬ��ҳ��
int SmallNum = 0;

//**************************************
//��װ������ʼ�����ݣ���ʼ������
//������Դ
//loadResource()
//**************************************
//1.������Դ
void loadResource()
{

	//��������
	mciSendString("open 1.mp3 alias music", 0, 0, 0);
	mciSendString("play music repeat", 0, 0, 0);

	loadimage(&backImg, "background.jpg");
	//�������أ�ͨ���ļ����Ƹ�ʽ
	for (int i = 0; i < 6; i++)
	{
		char FileName[1024] = "";
		sprintf(FileName, "%d.jpg", i);
		loadimage(BigPicture + i, FileName, 250, 350);
		loadimage(SmallPicture + i, FileName, 100, 130);
	}
}

//**************************************
//��ʼ������
//������
//DrawMap();
//**************************************
//2.������
void DrawMap()
{
	//������
	putimage(0, 0, &backImg);
	//��Сͼ
	putimage(90, 160, SmallPicture + 0);
	putimage(90, 310, SmallPicture + 1);

	//����ͼ
	/*putimage(345, 310, BigPicture + 0);*/
	putimage(350, 105, BigPicture + 0);

	//3.����ť
	//x,y ��ťλ�á�postion �����ҷ���ť
	DrawButton(170, 130, 'r');
	DrawButton(110, 130, 'l');

	//���֣�����
	//����������ɫ
	settextcolor(LIGHTRED);
	//��������ʹ�С
	settextstyle(25, 0, "STXINGKA.TTF");
	//ȥ�����ֱ������������ֱ���Ϊ͸��
	setbkmode(TRANSPARENT);
	//��������
	outtextxy(365, 50, "�뱦��һ���߹�������");
}

//**************************************
//�����û�����
//������
//UserMoveMouse();
//**************************************
//4.�û��������
void UserMoveMouse()
{
	int flag = 1;
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
			//����ƶ�
		case WM_MOUSEMOVE:
			//����Ƿ��ڰ�ť�ϣ��ж�����ǲ�����Բ����
			if (sqrt((double)(m.x - 170)*(m.x - 170) + (m.y - 130)*(m.x - 130)) < 22)
			{
				ClickButton(170, 130, 'r');
			}
			else if (sqrt((double)(m.x - 110)*(m.x - 110) + (m.y - 130)*(m.x - 123)) < 22)
			{
				ClickButton(110, 130, 'l');
			}
			else //����겻�ڰ�ť��
			{
				DrawButton(170, 130, 'r');
				DrawButton(110, 130, 'l');
			}
			break;
			//��갴��
		case WM_LBUTTONDOWN:
			if (sqrt((double)(m.x - 170)*(m.x - 170) + (m.y - 130)*(m.x - 130)) < 22)
			{
				DrawRect(flag);
				//ͼƬȫ������ѭ��
				if (SmallNum == 6)
				{
					//��ʾǰ����СͼƬ
					putimage(90, 160, SmallPicture + 0);
					putimage(90, 310, SmallPicture + 1);
					SmallNum = 0;
				}
				if (SmallNum == 2)
				{
					putimage(90, 160, SmallPicture + 2);
					putimage(90, 310, SmallPicture + 3);
				}
				if (SmallNum == 4)
				{
					putimage(90, 160, SmallPicture + 4);
					putimage(90, 310, SmallPicture + 5);
				}
				putimage(350, 105, BigPicture + SmallNum);
				SmallNum++;
			}
			else if (sqrt((double)(m.x - 110)*(m.x - 110) + (m.y - 130)*(m.x - 123)) < 22)
			{
				DrawRect(flag);
				//ͼƬȫ������ѭ��
				if (SmallNum == -1)
				{
					//��ʾǰ����СͼƬ
					putimage(90, 160, SmallPicture + 5);
					putimage(90, 310, SmallPicture + 4);
					SmallNum = 5;
				}
				if (SmallNum == 3)
				{
					putimage(90, 160, SmallPicture + 3);
					putimage(90, 310, SmallPicture + 2);
				}
				if (SmallNum == 1)
				{
					putimage(90, 160, SmallPicture + 1);
					putimage(90, 310, SmallPicture + 0);
				}
				putimage(350, 105, BigPicture + SmallNum);
				SmallNum--;
			}
			flag++;
			if (flag > 2)
			{
				flag = 1;
			}
			break;
		}
	}
}

//**************************************
//���ͣ���ڰ�ť�ϣ��Լ�����뿪��ť�Ĵ���
//�����û�����
//ClickButton();
//**************************************
//5.��������Ƿ��ڰ�ť��
void ClickButton(int x,int y,char postion)
{
	//���������ɫ
	setfillcolor(BLUE);
	//��xyΪ���껭һ��22�뾶��Բ
	solidcircle(x, y, 22);
	//�����ߵ���ɫ��ɫ
	setlinecolor(LIGHTRED);
	//�����ߵĸ�ʽ
	setlinestyle(PS_SOLID, 4, 0);
	if (postion == 'l')
	{
		circle(x, y, 16);
		line(x - 10, y, x + 10, y);
		line(x - 4, y - 4, x - 10, y);
		line(x - 4, y + 4, x - 10, y);
	}
	else if (postion == 'r')
	{
		circle(x, y, 16);
		line(x - 10, y, x + 10, y);
		line(x + 4, y - 4, x + 10, y);
		line(x + 4, y + 4, x + 10, y);
	}
}

//**************************************
//������
//СͼƬ�ľ���
//DrawRect();
//**************************************
//6.��ʾСͼƬ�߿��Է���֪���л�����һ��
void DrawRect(int flag)
{
	if (flag == 1)
	{
		setlinecolor(LIGHTRED);
		//��Сͼ
		//putimage(90, 160, SmallPicture + 0);
		//putimage(90, 310, SmallPicture + 1);
		//�߿��λ�ô�С
		rectangle(85, 155, 90 + 100 + 5, 130 + 160 + 5);
		setlinecolor(WHITE);
		rectangle(85, 305, 90 + 100 + 5, 130 + 310 + 5);
	}
	else if (flag == 2)
	{
		setlinecolor(LIGHTRED);
		//��Сͼ
		//putimage(90, 160, SmallPicture + 0);
		//putimage(90, 310, SmallPicture + 1);
		//�߿��λ�ô�С
		rectangle(85, 305, 90 + 100 + 5, 130 + 310 + 5);
		setlinecolor(WHITE);
		rectangle(85, 155, 90 + 100 + 5, 130 + 160 + 5);
	}
}

//**************************************
//��ť����
//����ť
//DrawButton();
//**************************************
//3.����ť
//x,y ��ťλ�á�postion �����ҷ���ť
void DrawButton(int x,int y,char postion)  
{
	//���������ɫ
	setfillcolor(BLUE);
	//��xyΪ���껭һ��22�뾶��Բ
	solidcircle(x, y, 22);
	//�����ߵ���ɫ��ɫ
	setlinecolor(WHITE);
	//�����ߵĸ�ʽ
	setlinestyle(PS_SOLID, 4, 0);
	if (postion == 'l')
	{
		circle(x, y, 16);
		line(x - 10, y, x + 10, y);
		line(x - 4, y - 4, x - 10, y);
		line(x - 4, y + 4, x - 10, y);
	}
	else if (postion == 'r')
	{
		circle(x, y, 16);
		line(x - 10, y, x + 10, y);
		line(x + 4, y - 4, x + 10, y);
		line(x + 4, y + 4, x + 10, y);
	}
}

int main()
{
	//���ô��ڴ�С
	initgraph(932, 538);
	//����IMAGE����ȥ�洢ͼƬ
	//1.������Դ
	loadResource();

	//2.������
	DrawMap();

	//4.�û��������
	UserMoveMouse();


	system("pause");
	return 0;
}
//IMAGE img;
////����ͼƬ
////loadimage(&img, "background.jpg"); 

////�����ŵ���ʽ����ͼƬ
//loadimage(&img, "background.jpg", 932, 538);
////��ʾͼƬ
//putimage(0, 0, &img);