#ifndef BOOM_H
#define BOOM_H
#include "Map.h"
#include <utility>
class Boom
{
private:
	
	int Last_time;
	//剩余爆炸时间
	
	char Symbol[4];
	//炸弹的标记 
	
	std::pair<int, int> Boom_Location;
	//炸弹的位置	
	
public:
	Boom(std::pair<int, int> location, int time, Map& Map);
	
	bool Destory(Map &Map);
	//炸弹这秒是否爆炸 
	
	std::pair<int, int> get_location();
	//返回炸弹位置 
};
#endif
