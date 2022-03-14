#ifndef MAP_H
#define MAP_H
#include <utility>
//#include "Player.h"
const int size = 20;
class Map
{
private:
	char map[size][size];
//	 = 
//	{
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    },
//		{                    }
//	};
public:
	Map();
	//���캯������ʼ����
	 
	void Print_Map();
	//��ӡ���º�ĵ�ͼ 
	
	void Change(std::pair<int, int> location, char c);
	//���ĵ�ͼ 
	
	char Search(std::pair<int, int> location);
	//��ѯ��λ�õ��ַ� 
	
	void Fire(std::pair<int, int> location, int r);
	//ը����ը 
};
#endif
