#ifndef PLAYER_H
#define PLAYER_H
#include <utility>
#include <stdio.h>
#include "Map.h" 
#include "Boom.h"
class Player
{
private:
	
	std::pair<int, int> location;//���ڵ�λ��
	
	char symbol; //�������ҵ��ַ�
	
	int life;//ʣ������� 
	
	Boom* MyBoom;//������ը��,��ʱ�����һ�� 
	
	int time;//ը����ըʱ�� 
	
	int r;//ը���뾶 
	
	

public:
	bool Clear;//�Ƿ���Ҫ���ը�� 
	
	Player(int x, int y, char symbol, int life, Map& Map, int r);
	//��ʼ��
	
	void update_location(int type, Map& Map);
	//����λ��
	
	std::pair<int, int> get_location(); 
	//��ȡλ��
	
	bool move(int x, int y, Map& Map);
	//(x,y)λ���Ƿ���Է������
	
	void hurt();
	//�������
	
	int get_life();
	//��ѯ���ʣ��Ѫ�� 
	
	void Create_Boom(Map& Map);
	//�ڽ��´���һ��ը�� 
	
	void Check_Boom(Map& Map);
	//���ը���Ƿ�ը
	
	void Clear_Boom(Map& Map); 
	
};

#endif
