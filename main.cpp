#include <conio.h>
#include <iostream>
#include <utility>
#include "Player.h"
#include "Map.h"
using namespace std;
bool GameOver = false;
bool Clear = false;
Map Map1;
Player P1(0, 0, '*', 2, Map1, 2);
//Player p2;
void deal_with_input()//�������ַ����д��� 
{
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		switch (ch)
		{
			case 'w':
					P1.update_location(1, Map1);
					break;
			case 's':
					P1.update_location(2, Map1);
					break;
			case 'a':
					P1.update_location(3, Map1);
					break;
			case 'd':
					P1.update_location(4, Map1);
					break;
			case ' '://��ը��
					P1.Create_Boom(Map1); 
					break;
			default:
					break;
		}
	}
}
const long long int ONE_SECOND = 5e8;
int Count = 0;
void display()//�ַ���ʾ 
{
	system("cls");
	//�����Ļ
	
	Map1.Print_Map();
	//��ӡ��ʾ����Ϣ 
	
	printf("��ҵ�����ʣ�ࣺ%d\n", P1.get_life());
}
void deal_with_timer()//��ʱ�¼���ɨ��������ʱ����� 
{
	P1.Check_Boom(Map1);
	if(P1.get_life() == 0) GameOver = true;
	if(Clear) P1.Clear_Boom(Map1);
	Clear = false;
}
int main()
{
	display();
	while (1)
	{	
		Count++;
		if (Count == ONE_SECOND)//ÿһ�������� 
		{
			deal_with_input();
			deal_with_timer();	
			display();
			if(P1.Clear) Clear = true;
			if(GameOver)
			{
				printf("GameOver!\n");
				break;	
			} 
			Count = 0;
		}
	}
	return 0;
}	
