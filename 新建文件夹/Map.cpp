#include "Map.h"
#include <stdio.h>
#include <string.h>
Map::Map()
{
	memset(map, ' ', sizeof(map));
	Reset();
}

void Map::Reset()
{
	srand((int)time(0));
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{	
			
			int x = rand() % 8;
			switch(x)
			{
				case 1:
						Change(std::pair<int, int>(i, j), '@');
						break;
				case 2: 
						break;
				case 3:
						break;
				default:
						Change(std::pair<int, int>(i, j), '#');
			}
		}
	}
	map[0][1] = map[1][0] = ' ';
	map[0][size - 2] = map[1][size - 1] = ' ';
	map[size - 1][1] = map[size - 2][0] = ' ';
	map[size - 1][size - 2] = map[size - 2][size - 1] = ' ';
}

void Map::Print_Map() 
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

void Map::Change(std::pair<int, int> location, char c)
{
	map[location.first][location.second] = c;
}

char Map::Search(std::pair<int, int> location)
{
	return map[location.first][location.second];
}

void Map::Fire(std::pair<int, int> location, int r)
{
	int x = location.first;
	int y = location.second;
	for(int i = 1; i <= r; i++)
	{
		if(x + i < size) if(map[x + i][y] == ' ') Change(std::pair<int, int>(x + i, y), '+');
		if(x - i >= 0) if(map[x - i][y] == ' ') Change(std::pair<int, int>(x - i, y), '+');
		if(y + i < size) if(map[x][y + i] == ' ') Change(std::pair<int, int>(x, y + i), '+');
		if(y - i >= 0) if(map[x][y - i] == ' ') Change(std::pair<int, int>(x, y - i), '+');
		//随机道具生成 
		if(x + i < size) if(map[x + i][y] == '#')
		{
			if(!Range(std::pair<int, int>(x + i, y))) Change(std::pair<int, int>(x + i, y), '+');	
		} 
		if(x - i >= 0) if(map[x - i][y] == '#')
		{
			if(!Range(std::pair<int, int>(x - i, y))) Change(std::pair<int, int>(x - i, y), '+');	
		} 
		if(y + i < size) if(map[x][y + i] == '#')
		{
			if(!Range(std::pair<int, int>(x, y + i))) Change(std::pair<int, int>(x, y + i), '+');
		} 
		if(y - i >= 0) if(map[x][y - i] == '#')
		{
			if(!Range(std::pair<int, int>(x, y - i))) Change(std::pair<int, int>(x, y - i), '+');
		} 
	}
}

bool Map::Range(std::pair<int, int> location)
{
	srand((int)time(0));
	int x = rand() % 30;
	switch(x)
	{
		case 1: 
				Change(location, 's');
				return true;
		case 2: 
				Change(location, 'r');
				return true;
		case 3:	
				Change(location, 'S');
				return true;
		case 4:	
				Change(location, 'R');
				return true;
		default:
				return false;
	}
}
