#ifndef BOOM_H
#define BOOM_H
#include "Map.h"
#include <utility>
class Boom
{
private:
	
	int Last_time;
	//ʣ�౬ըʱ��
	
	char Symbol[6];
	//ը���ı�� 
	
	std::pair<int, int> Boom_Location;
	//ը����λ��	
	
	int r;
	
public:
	Boom(std::pair<int, int> location, int time, Map& Map);
	
	bool Destory(Map &Map);
	//ը�������Ƿ�ը 
	
	std::pair<int, int> get_location();
	//����ը��λ�� 
	
	int get_r();
};
#endif
