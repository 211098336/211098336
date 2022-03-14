#ifndef PLAYER_H
#define PLAYER_H
#include <utility>
#include <stdio.h>
#include "Map.h" 
#include "Boom.h"
class Player
{
private:
	
	std::pair<int, int> location;//现在的位置
	
	char symbol; //代表该玩家的字符
	
	int life;//剩余的生命 
	
	Boom* MyBoom;//创建的炸弹,暂时最多有一个 
	
	int time;//炸弹爆炸时间 
	
	int r;//炸弹半径 
	
	

public:
	bool Clear;//是否需要清除炸弹 
	
	Player(int x, int y, char symbol, int life, Map& Map, int r);
	//初始化
	
	void update_location(int type, Map& Map);
	//更新位置
	
	std::pair<int, int> get_location(); 
	//获取位置
	
	bool move(int x, int y, Map& Map);
	//(x,y)位置是否可以放置玩家
	
	void hurt();
	//玩家受伤
	
	int get_life();
	//查询玩家剩余血量 
	
	void Create_Boom(Map& Map);
	//在脚下创建一个炸弹 
	
	void Check_Boom(Map& Map);
	//检查炸弹是否爆炸
	
	void Clear_Boom(Map& Map); 
	
};

#endif
