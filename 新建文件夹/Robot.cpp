#include "Robot.h"

Robot::Robot(int x, int y, char symbol, int life, Map& Map, int r) :
	location(x, y),
	symbol(symbol),
	r(r),
	life(life)
	{
		Map.Change(location, symbol);
		for(int i = 0; i < 3; i++) MyBoom[i] = NULL;
		Clear = false;
		speed = 1;
		time = 4;
		buff_time[0] = buff_time[1] = 0;
		Over = false;
	}

bool Robot::Avoid_Boom(Map& Map, int direction)//上下左右，1234 
{
	int x = location.first, y = location.second;
	switch(direction)
	{
		case 1:
				x--;
				break;
		case 2:
				x++;
				break;
		case 3:
				y--;
				break;
		case 4:
				y++;
				break;		
	}
	if(x < 0 || x == size || y == size || y < 0) return true;
	bool status = false;
	for(int i = 1; i <= 2; i++)
	{
		if(x + i < size)
		{
			char c = Map.Search(std::pair<int, int>(x + i, y));
			if(c >= '1' && c <= '4') status = true;
		}
		if(x - i >= 0)
		{
			char c = Map.Search(std::pair<int, int>(x - i, y));
			if(c >= '1' && c <= '4') status = true;
		}
		if(y + i < size)
		{
			char c = Map.Search(std::pair<int, int>(x, y + i));
			if(c >= '1' && c <= '4') status = true;
		}
		if(y - i >= 0)
		{
			char c = Map.Search(std::pair<int, int>(x, y - i));
			if(c >= '1' && c <= '4') status = true;
		}
	}
	return status;
}

struct Node
{
	int x, y, d;
	Node(int x, int y, int d) :
		x(x),
		y(y),
		d(d)
	{}
};	

int Robot::Hunt_Player(Map& Map, Player& Player)
{
	if(location.first == Player.get_location().first && location.second + r >= Player.get_location().second && location.second - r <= Player.get_location().second)
	{
		Create_Boom(Map);
		return 0;
	} 
	if(location.second == Player.get_location().second && location.first + r >= Player.get_location().first && location.first - r <= Player.get_location().first)
	{
		Create_Boom(Map);
		return 0;
	} 
	int map[size][size];
	memset(map, -1, sizeof(map));
	queue<Node> q;
	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};
	q.push(Node(Player.get_location().first, Player.get_location().second, 0));
	int min = 1e7;
	while(!q.empty())
	{
		if(q.front().x == location.first && q.front().y == location.second)
		{
			if(q.front().d < min) min = q.front().d;
		}
		else
		{
			int x = q.front().x, y = q.front().y;
			for(int i = 0; i < 3; i++)
			{
				int tx = x + dx[i];
				int ty = y + dy[i];
				if(tx < 0 || tx == size || ty < 0 || ty == size) continue;
				if(Map.Search(std::pair<int, int>(tx, ty)) != '@')
				{
					int d;
					if(Map.Search(std::pair<int, int>(tx, ty)) == '#') d = 3;
					else d = 1;
					if(map[tx][ty] > q.front().d + d || map[tx][ty] == -1)
					{
						map[tx][ty] = q.front().d + d;
						q.push(Node(tx, ty, q.front().d + d));
					}
				}
			}
		}
		q.pop();
	}
	int up = 1e8, down = 1e8, left = 1e8, right = 1e8;
	if(location.first - 1 >= 0 && !Avoid_Boom(Map, 1)) if(map[location.first - 1][location.second] != -1) up = map[location.first - 1][location.second];
	if(location.first + 1 <size && !Avoid_Boom(Map, 2)) if(map[location.first + 1][location.second] != -1) down = map[location.first + 1][location.second];
	if(location.second - 1 >= 0 && !Avoid_Boom(Map, 3)) if(map[location.first][location.second - 1] != -1) left = map[location.first][location.second - 1];
	if(location.second + 1 < size && !Avoid_Boom(Map, 4)) if(map[location.first][location.second + 1] != -1) right = map[location.first][location.second + 1];
	if(up == 1e8 && down == 1e8 && left == 1e8 && right == 1e8) return 0;
	if(up <= down && up <= left && up <= right) return 1;
	if(down <= up && down <= left && down <= right) return 2;
	if(left <= up && left <= down && left <= right) return 3;
	if(right <= up && right <= down && right <= left) return 4;
} 

void Robot::update_location(int type, Map& Map)//上下左右移动 
{
	if(Over) return;
	switch(type)
	{
		case 1://向上 
				Map.Change(location, ' ');
				location.first--;
				Map.Change(location, symbol);
				break;
		case 2://向下 
				Map.Change(location, ' ');
				location.first++;
				Map.Change(location, symbol);
				break;
		case 3://向左 
				Map.Change(location, ' ');
				location.second--;
				Map.Change(location, symbol);
				break;
		case 4://向右 
				Map.Change(location, ' ');
				location.second++;
				Map.Change(location, symbol);
				break;
		default:
				break;
	}
}
	
void Robot::Auto_action(Map& Map, Player& Player)
{
	char c = Map.Search(location);
	if(c >= '1' && c <= '5')//躲脚下的炸弹
	{
		if(location.first - 1 >= 0)
		{
			if(location.second - 1 >= 0)//考虑左上角 
			{
				char c1, c2, c3;
				c1 = Map.Search(std::pair<int, int>(location.first - 1, location.second));//上 
				c2 = Map.Search(std::pair<int, int>(location.first, location.second - 1));//左
				c3 = Map.Search(std::pair<int, int>(location.first - 1, location.second - 1));//左上 
				if(c1 != '#' && c1 != '@' && c3 != '#' && c3 != '@') update_location(1, Map); 
				else if(c2 != '#' && c2 != '@' && c3 != '#' && c3 != '@') update_location(3, Map);
			}
			else if(location.second + 1 < size)//考虑右上角 
			{
				char c1, c2, c3;
				c1 = Map.Search(std::pair<int, int>(location.first - 1, location.second));//上 
				c2 = Map.Search(std::pair<int, int>(location.first, location.second + 1));//右 
				c3 = Map.Search(std::pair<int, int>(location.first - 1, location.second + 1));//右上 
				if(c1 != '#' && c1 != '@' && c3 != '#' && c3 != '@') update_location(1, Map); 
				else if(c2 != '#' && c2 != '@' && c3 != '#' && c3 != '@') update_location(4, Map);
			}
		}
		else if(location.first + 1 < size)
		{
			if(location.second - 1 >= 0)//考虑左下角 
			{
				char c1, c2, c3;
				c1 = Map.Search(std::pair<int, int>(location.first + 1, location.second));//下 
				c2 = Map.Search(std::pair<int, int>(location.first, location.second - 1));//左
				c3 = Map.Search(std::pair<int, int>(location.first + 1, location.second - 1));//左下 
				if(c1 != '#' && c1 != '@' && c3 != '#' && c3 != '@') update_location(1, Map); 
				else if(c2 != '#' && c2 != '@' && c3 != '#' && c3 != '@') update_location(3, Map);
			}
			else if(location.second + 1 < size)//考虑右下角 
			{
				char c1, c2, c3;
				c1 = Map.Search(std::pair<int, int>(location.first + 1, location.second));//下 
				c2 = Map.Search(std::pair<int, int>(location.first, location.second + 1));//右 
				c3 = Map.Search(std::pair<int, int>(location.first + 1, location.second + 1));//右下 
				if(c1 != '#' && c1 != '@' && c3 != '#' && c3 != '@') update_location(1, Map); 
				else if(c2 != '#' && c2 != '@' && c3 != '#' && c3 != '@') update_location(4, Map);
			}
		}
		return; 
	}
	bool status = false;
	for(int i = 1; i <= 2; i++)
	{
		if(location.first + i < size)
		{
			char c = Map.Search(std::pair<int, int>(location.first + i, location.second));
			if(c >= '1' && c <= '4')
			{
				status = true;
				break; 
			} 
		}
		else if(location.first - i >= 0)
		{
			char c = Map.Search(std::pair<int, int>(location.first - i, location.second));
			if(c >= '1' && c <= '4')
			{
				status = true;
				break; 
			}
		}
	}
	if(status)//躲上下的    
	{
		if(location.second - 1 >= 0)
		{
			char q = Map.Search(std::pair<int, int>(location.first, location.second - 1));
			if(q != '#' && q != '@') update_location(3, Map);
			return; 
		} 
		if(location.second + 1 < size)
		{
			char q = Map.Search(std::pair<int, int>(location.first, location.second + 1));
			if(q != '#' && q != '@') update_location(4, Map);
			return; 
		}
	}
	for(int i = 1; i <= 2; i++)
	{
		if(location.second + i < size)
		{
			char c = Map.Search(std::pair<int, int>(location.first, location.second + i));
			if(c >= '1' && c <= '4')
			{
				status = true;
				break; 
			}
		}
		else if(location.second - i >= 0)
		{
			char c = Map.Search(std::pair<int, int>(location.first, location.second - i));
			if(c >= '1' && c <= '4')
			{
				status = true;
				break; 
			}
		}
	}
	if(status)//躲左右的 
	{
		if(location.first - 1 >= 0)
		{
			char q = Map.Search(std::pair<int, int>(location.first - 1, location.second));
			if(q != '#' && q != '@') update_location(1, Map);
			return; 
		} 
		if(location.first + 1 < size)
		{
			char q = Map.Search(std::pair<int, int>(location.first + 1, location.second));
			if(q != '#' && q != '@') update_location(4, Map);
			return; 
		}
	}
	int x = Hunt_Player(Map, Player);
	switch(x)
	{
		case 1:
				if(Map.Search(std::pair<int, int>(location.first - 1, location.second)) == '#')
				{
					Create_Boom(Map);
					return;
				}
				break;
		case 2:
				if(Map.Search(std::pair<int, int>(location.first + 1, location.second)) == '#')
				{
					Create_Boom(Map);
					return;
				}
				break;
		case 3:
				if(Map.Search(std::pair<int, int>(location.first, location.second - 1)) == '#')
				{
					Create_Boom(Map);
					return;
				}
				break;
		case 4:
				if(Map.Search(std::pair<int, int>(location.first, location.second + 1)) == '#')
				{
					Create_Boom(Map);
					return;
				}
				break;
		default:
				break;
	}
	update_location(x, Map);
} 

std::pair<int, int> Robot::get_location()//保留 
{
	return location;
}

void Robot::Is_Hurt(std::pair<int, int> Location, int r)//保留 
{
	if(Over) return;
	bool S1 = (location.first == Location.first) && (location.second - Location.second <= r) && (Location.second - location.second <= r);
	bool S2 = (location.second == Location.second) && (location.first - Location.first <= r) && (Location.first - location.first <= r);
	if(S1 || S2) life--;
}

int Robot::get_life()//保留 
{
	if(life == 0) Over = true;
	return life;
}

void Robot::Create_Boom(Map& Map)//保留 
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

std::pair<int, int> Robot::Check_Boom(Map &Map)//保留 
{
	for(int i = 0; i < 3; i++)
	{
		if(MyBoom[i])
		{
			if(MyBoom[i] -> Destory(Map))
			{
				Map.Fire(MyBoom[i] -> get_location(), r);//
				Clear = true;
				return MyBoom[i] -> get_location();
			} 
		}
	}
	std::pair<int, int> Default(-1, -1);
	return Default;
}

void Robot::Clear_Boom(Map& Map)//保留 
{
	for(int k = 0; k < 3; k++)
	{
		if(MyBoom[k])
		{
			if(Map.Search(MyBoom[k] -> get_location()) == '0')
			{
				int x = MyBoom[k] -> get_location().first;
				int y = MyBoom[k] -> get_location().second;
				for(int i = 1; i <= r; i++)
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

void Robot::Get_Buff(int type, int time, int level)//保留 
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

void Robot::Clear_Buff()//保留 
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

int Robot::Get_Speed()//保留 
{
	return speed;
} 

int Robot::Get_R()//保留 
{
	return r;
}
