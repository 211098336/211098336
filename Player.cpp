#include "Player.h"

Player::Player(int x, int y, char symbol, int life, Map& Map, int r) :
	location(x, y),
	symbol(symbol),
	r(r),
	life(life)
	{
		Map.Change(location, symbol);
		time = 3; 
		MyBoom = NULL;
		Clear = false;
	}

void Player::update_location(int type, Map& Map)//上下左右移动 
{
	switch(type)
	{
		case 1://向上 
				if(move(location.first - 1, location.second, Map))//如果移动成功，清空原位置 
				{
					Map.Change(location, ' ');
					location.first--;
				}
				break;
		case 2://向下 
				if(move(location.first + 1, location.second, Map))//如果移动成功，清空原位置 
				{
					Map.Change(location, ' ');
					location.first++;
				}
				break;
		case 3://向左 
				if(move(location.first, location.second - 1, Map))//如果移动成功，清空原位置 
				{
					Map.Change(location, ' ');
					location.second--;
				}
				break;
		case 4://向右 
				if(move(location.first, location.second + 1, Map))//如果移动成功，清空原位置 
				{
					Map.Change(location, ' ');
					location.second++;
				}
				break;
		default:
				break;
	}
}

std::pair<int, int> Player::get_location()
{
	return location;
}

bool Player::move(int x, int y, Map& Map)
{
	if(x < 0 || y < 0 || x >= size || y >= size)	return false;//超过边界，拒绝执行 
	std::pair<int, int> target(x, y);
	if(Map.Search(target) == '#' || Map.Search(target) == '@')	return false;//软墙或硬墙,拒绝执行 
	else
	{
		Map.Change(target, symbol);//替换为玩家字符 
		return true;
	}
}

void Player::hurt()
{
	life--;
}

int Player::get_life()
{
	return life;
}

void Player::Create_Boom(Map& Map)
{
	if(!MyBoom) MyBoom = new Boom(location, time, Map);
}

void Player::Check_Boom(Map &Map)
{
	if(MyBoom)
	{
		if(MyBoom -> Destory(Map))
		{
//			int r = 2;//临时赋值 
			Map.Fire(MyBoom -> get_location(), r);//
			bool x = location.first + r >= MyBoom -> get_location().first && location.first - r <= MyBoom -> get_location().first;
			bool y = location.second + r >= MyBoom -> get_location().second && location.second - r <= MyBoom -> get_location().second;
			if((x && location.second == MyBoom -> get_location().second) || (y && location.first == MyBoom -> get_location().second)) hurt();
			Clear = true;
		} 
	}
}

void Player::Clear_Boom(Map& Map)
{
	int x = MyBoom -> get_location().first;
	int y = MyBoom -> get_location().second;
	for(int i = 1; i <= r; i++)
	{
		if(x + i < size) if(Map.Search(std::pair<int, int>(x + i, y)) == '+') Map.Change(std::pair<int, int>(x + i, y), ' ');
		if(x - i >= 0) if(Map.Search(std::pair<int, int>(x - i, y)) == '+') Map.Change(std::pair<int, int>(x - i, y), ' ');
		if(y + i < size) if(Map.Search(std::pair<int, int>(x, y + i)) == '+') Map.Change(std::pair<int, int>(x, y + i), ' ');
		if(y - i >= 0) if(Map.Search(std::pair<int, int>(x, y - i)) == '+') Map.Change(std::pair<int, int>(x, y - i), ' ');
	}
	Clear = false;
	delete(MyBoom);
	MyBoom = NULL;
}
