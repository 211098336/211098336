#ifndef ROBOT_H
#define ROBOT_H
#include <utility>
#include <stdio.h>
#include <string.h>
#include <queue>
#include "Map.h" 
#include "Boom.h"
#include "Player.h"
using namespace std;

class Robot
{
	private:
	
	std::pair<int, int> location;//现在的位置
	
	char symbol; //代表该玩家的字符
	
	int life;//剩余的生命 
	
	Boom* MyBoom[3];//创建的炸弹,暂时最多有3个 
	
	int time;//炸弹爆炸时间 
	
	int r;//炸弹半径 
	
	int speed;//玩家速度 
	
	int buff_time[2];//0为速度，1为炸弹半径 
	
	bool Over;

public:
	bool Clear;//是否需要清除炸弹 
	
	Robot(int x, int y, char symbol, int life, Map& Map, int r);
	//初始化
	
	bool Avoid_Boom(Map& Map, int direction);
	//躲避炸弹 
	
	void update_location(int type, Map& Map); 
	
	int Hunt_Player(Map& Map, Player& Player);
	//追杀玩家 
	
	void Auto_action(Map& Map, Player& Player);
	//自动指令 
	
	std::pair<int, int> get_location(); 
	//获取位置
	
	void Is_Hurt(std::pair<int, int> Location, int r);
	//玩家受伤
	
	int get_life();
	//查询玩家剩余血量 
	
	void Create_Boom(Map& Map);
	//在脚下创建一个炸弹 
	
	std::pair<int, int> Check_Boom(Map& Map);
	//检查炸弹是否爆炸
	
	void Clear_Boom(Map& Map); 
	//清除自己炸弹爆炸后的火光 
	
	void Get_Buff(int type, int time, int level);
	//buff类型（速度，炸弹半径），持续时间，buff等级
	 
	void Clear_Buff();
	//每一帧减少一秒buff时间 
	
	int Get_Speed();
	//玩家速度帧数 
	
	int Get_R();
	//玩家炸弹半径 
	
	void Reset();
};
#endif
