#include "Player.h"

Player::Player(int x, int y, char symbol, int life, Map& Map, int r) :
	location(x, y),
	symbol(symbol),
	r(r),
	life(life)
	{
		Map.Change(location, symbol);
		for(int i = 0; i < 3; i++) MyBoom[i] = NULL;
		Clear = false;
		speed = 1;
		time = 5;
		buff_time[0] = buff_time[1] = 0;
		Over = false;
	}

void Player::update_location(int type, Map& Map)//上下左右移动 
{
	if(Over) return;
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
		switch(Map.Search(target))//捡道具 
		{
			case 's':
						Get_Buff(0, 10, 1);
						break;
			case 'S':
						Get_Buff(0, 10, 2);
						break;
			case 'r':
						Get_Buff(1, 10, 1);
						break;
			case 'R':
						Get_Buff(1, 10, 2);
						break;
			default:	break;	
		}
		Map.Change(target, symbol);//替换为玩家字符 
		return true;
	}
}

void Player::Is_Hurt(std::pair<int, int> Location, int r)
{
	if(Over) return;	
	bool S1 = (location.first == Location.first) && (location.second - Location.second <= r) && (Location.second - location.second <= r);
	bool S2 = (location.second == Location.second) && (location.first - Location.first <= r) && (Location.first - location.first <= r);
	if(S1 || S2) life--;
}

int Player::get_life()
{
	if(life == 0) Over = true;
	return life;
}

void Player::Create_Boom(Map& Map)
{
	if(Over) return;
	for(int i = 0; i < 3; i++)
	{
		if(!MyBoom[i])
		{
			MyBoom[i] = new Boom(location, time, Map);
			break;
		} 	
	}
}

std::pair<int, int> Player::Check_Boom(Map &Map)
{
	for(int i = 0; i < 3; i++)
	{
		if(MyBoom[i])
		{
			if(MyBoom[i] -> Destory(Map))
			{
				Map.Fire(MyBoom[i] -> get_location(), r);
				Clear = true;
				return MyBoom[i] -> get_location();
			} 
		}
	}
	std::pair<int, int> Default(-1, -1);
	return Default;
}

void Player::Clear_Boom(Map& Map)
{
	for(int k = 0; k < 3; k++)
	{
		if(MyBoom[k])
		{
			if(Map.Search(MyBoom[k] -> get_location()) == '0')
			{
				int x = MyBoom[k] -> get_location().first;
				int y = MyBoom[k] -> get_location().second;
				for(int i = 1; i <= Get_R(); i++)
				{
					if(x + i < size) if(Map.Search(std::pair<int, int>(x + i, y)) == '+') Map.Change(std::pair<int, int>(x + i, y), ' ');
					if(x - i >= 0) if(Map.Search(std::pair<int, int>(x - i, y)) == '+') Map.Change(std::pair<int, int>(x - i, y), ' ');
					if(y + i < size) if(Map.Search(std::pair<int, int>(x, y + i)) == '+') Map.Change(std::pair<int, int>(x, y + i), ' ');
					if(y - i >= 0) if(Map.Search(std::pair<int, int>(x, y - i)) == '+') Map.Change(std::pair<int, int>(x, y - i), ' ');
				}
				Map.Change(MyBoom[k] -> get_location(), ' ');
				Clear = false;
				delete(MyBoom[k]);
				MyBoom[k] = NULL;
			}
			
		}
	}
}

void Player::Get_Buff(int type, int time, int level)
{
	if(type == 0)//速度类型
	{
		if(time > buff_time[0])	buff_time[0] = time;
		if(level == 1 && speed < 2) speed = 2;
		if(level == 2 && speed < 3) speed = 3;	
	} 
	if(type == 1)//炸弹半径类型
	{
		if(time > buff_time[1]) buff_time[1] = time;
		if(level == 1 && r < 3) r = 3;
		if(level == 2 && r < 4) r = 4;	
	} 
}

void Player::Clear_Buff()
{
	if(buff_time[0] > 0)
	{
		buff_time[0]--;
		if(!buff_time[0]) speed = 1;
	} 
	if(buff_time[1] > 0)
	{
		buff_time[1]--;
		if(!buff_time[1]) r = 2;
	} 
}

int Player::Get_Speed()
{
	return speed;
} 

int Player::Get_R()
{
	return r;
}
