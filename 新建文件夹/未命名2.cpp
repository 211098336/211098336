#include <conio.h>
#include <iostream>
using namespace std;
void deal_with_input()
{
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		cout << ch;
	}
}
const int ONE_SECOND = 1e9;
int Count = 0;
void init()
{
	;
}
void display()
{
	;
}
void deal_with_timer() 
{
	;
}
int main()
{
	init();
	display();
	while (1)
	{
		deal_with_input();
		Count++;
		if (Count == ONE_SECOND)
		{
			deal_with_timer();
			Count = 0;
		}
	}
	return 0;
}	
