#include "Boom.h"

Boom::Boom(std::pair<int, int> location, int time, Map& Map)
{
	Last_time = time;	
	Symbol[0] = '0';
	Symbol[1] = '1';
	Symbol[2] = '2';
	Symbol[3] = '3';
	Symbol[4] = '4';
	Symbol[5] = '5';
	Boom_Location = location;
	Map.Change(location, Symbol[Last_time]);
	//µ¹¼ÆÊ±·ûºÅ 
} 

bool Boom::Destory(Map &Map)
{
	if(Last_time > 0)
	{
		Last_time--;
		Map.Change(Boom_Location, Symbol[Last_time]);
		if(Last_time == 0) return true;
	}
	return false;
}

std::pair<int, int> Boom::get_location()
{
	return Boom_Location;	
} 
