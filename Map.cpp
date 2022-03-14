#include "Map.h"
#include <stdio.h>
#include <string.h>
Map::Map()
{
	memset(map, ' ', sizeof(map));
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
		if(x + i < size) if(map[x + i][y] == ' ' || map[x + i][y] == '#') Change(std::pair<int, int>(x + i, y), '+');
		if(x - i >= 0) if(map[x - i][y] == ' ' || map[x + i][y] == '#') Change(std::pair<int, int>(x - i, y), '+');
		if(y + i < size) if(map[x][y + i] == ' ' || map[x + i][y] == '#') Change(std::pair<int, int>(x, y + i), '+');
		if(y - i >= 0) if(map[x][y - i] == ' ' || map[x + i][y] == '#') Change(std::pair<int, int>(x, y - i), '+');
	}
}
