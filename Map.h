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
	//构造函数，初始化？
	 
	void Print_Map();
	//打印更新后的地图 
	
	void Change(std::pair<int, int> location, char c);
	//更改地图 
	
	char Search(std::pair<int, int> location);
	//查询此位置的字符 
	
	void Fire(std::pair<int, int> location, int r);
	//炸弹爆炸 
};
#endif
