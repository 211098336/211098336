#include <conio.h>
#include <iostream>
#include <utility>
#include "Player.h"
#include "Map.h"
#include "Robot.h"
using namespace std;
const long long int ONE_SECOND = 1e4;
bool GameOver = false;
bool Clear1 = false;
bool Clear2 = false;
bool Clear3 = false;
bool Clear4 = false; 
bool P1_Move = true;
bool P2_Move = true;
bool R1_Move = true;
bool R2_Move = true;
int Count = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
Map Map1;
Player P1(0, 0, 'y', 2, Map1, 2);
Player P2(19, 0, 'x', 2, Map1, 2);
Robot R1(0, 19, 'z', 2, Map1, 2);
Robot R2(19, 19, 'i', 2, Map1, 2);
void deal_with_input()//对输入字符进行传输
{
	char ch;
	if(count1 == P1.Get_Speed()) P1_Move = false;
	if(count2 == P2.Get_Speed()) P2_Move = false;
	if(count3 == R1.Get_Speed()) R1_Move = false;
	if(count4 == R2.Get_Speed()) R2_Move = false;
	if (_kbhit())
	{
		ch = _getch();
		switch (ch)
		{
			case 'w':
					if(P1_Move)
					{
						P1.update_location(1, Map1);
						count1++;	
					} 
					break;
			case 's':
					if(P1_Move)
					{
						P1.update_location(2, Map1);
						count1++;
					} 
					break;
			case 'a':
					if(P1_Move)
					{
						P1.update_location(3, Map1);
						count1++;
					} 
					break;
			case 'd':
					if(P1_Move)
					{
						P1.update_location(4, Map1);
						count1++;
					} 
					break;
			case ' ':
					P1.Create_Boom(Map1); 
					break;
			case 'i':
					if(P2_Move)
					{
						P2.update_location(1, Map1);
						count2++;
					} 
					break;
			case 'k':
					if(P2_Move)
					{
						P2.update_location(2, Map1);
						count2++;
					} 
					break;
			case 'j':
					if(P2_Move)
					{
						P2.update_location(3, Map1);
						count2++;
					} 
					break;
			case 'l':
					if(P2_Move)
					{
						P2.update_location(4, Map1);
						count2++;
					} 
					break;
			case 13:
					P2.Create_Boom(Map1);
					break;
			default:
					break;
		}
	}
}
void display()//字符显示 
{
	system("cls");
	//清空屏幕
	
	Map1.Print_Map();
	//打印显示的信息 
	
	printf("玩家1的生命剩余：%d\n", P1.get_life());
	printf("玩家2的生命剩余：%d\n", P2.get_life());
	printf("机器人1的生命剩余: %d\n", R1.get_life());
	printf("机器人2的生命剩余: %d\n", R2.get_life());
}
void deal_with_timer()//定时事件，扫描所有类时间队列 
{
	int x1 = R1.Get_Speed();
//	int x2 = R2.Get_Speed();
	for(; x1 > 0; x1--)
	{
		R1.Auto_action(Map1, P1);
	}
	std::pair<int, int> b1 = P1.Check_Boom(Map1);
	std::pair<int, int> b2 = P2.Check_Boom(Map1);
	std::pair<int, int> b3 = R1.Check_Boom(Map1);
	std::pair<int, int> b4 = R2.Check_Boom(Map1);
	if(b1.first != -1)
	{
		P1.Is_Hurt(b1, P1.Get_R());
		P2.Is_Hurt(b1, P1.Get_R());	
		R1.Is_Hurt(b1, P1.Get_R());
		R2.Is_Hurt(b1, P1.Get_R());
	}
	if(b2.first != -1)
	{
		P1.Is_Hurt(b2, P2.Get_R());
		P2.Is_Hurt(b2, P2.Get_R());
		R1.Is_Hurt(b2, P2.Get_R());
		R2.Is_Hurt(b2, P2.Get_R());	
	}
	if(b3.first != -1)
	{
		P1.Is_Hurt(b3, R1.Get_R());
		P2.Is_Hurt(b3, R1.Get_R());	
		R1.Is_Hurt(b3, R1.Get_R());
		R2.Is_Hurt(b3, R1.Get_R());
	}
	if(b4.first != -1)
	{
		P1.Is_Hurt(b4, R2.Get_R());
		P2.Is_Hurt(b4, R2.Get_R());	
		R1.Is_Hurt(b4, R2.Get_R());
		R2.Is_Hurt(b4, R2.Get_R());
	}	
	P1.Clear_Buff();
	P2.Clear_Buff();
	R1.Clear_Buff();
	R2.Clear_Buff();
	P1_Move = true;
	P2_Move = true; 
	R1_Move = true;
	R2_Move = true;
	count1 = 0;
	count2 = 0;
	count3 = 0;
	count4 = 0;
	if((P1.get_life() == 0) + (P2.get_life() == 0) + (R1.get_life() == 0) + (R2.get_life() == 0) == 3) GameOver = true;
	if(Clear1)
	{
		P1.Clear_Boom(Map1);
		Clear1 = false;	
	} 
	if(Clear2)
	{
		P2.Clear_Boom(Map1);
		Clear2 = false;
	} 
	if(Clear3)
	{
		R1.Clear_Boom(Map1);
		Clear3 = false;
	}
	if(Clear4)
	{
		R2.Clear_Boom(Map1);
	}
}
int main()
{
	display();
	while (1)
	{	
		Count++;
		deal_with_input();
		if (Count == ONE_SECOND)//每一秒做的事 
		{
			deal_with_timer();	
			display();
			if(P1.Clear) Clear1 = true;
			if(P2.Clear) Clear2 = true;
			if(R1.Clear) Clear3 = true;
			if(R2.Clear) Clear4 = true;
			if(GameOver)
			{
				printf("GameOver!\n");
				if(P1.get_life()) printf("The winner is P1\n");
				if(P2.get_life()) printf("The winner is P2\n");
				if(R1.get_life()) printf("The winner is R1\n");
				if(R2.get_life()) printf("The winner is R2\n");
				break;	
			} 
			Count = 0;
		}
	}
	return 0;
}	
