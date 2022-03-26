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
	
	Boom* MyBoom[3];//������ը��,��ʱ�����3�� 
	
	int time;//ը����ըʱ�� 
	
	int r;//ը���뾶 
	
	int speed;//����ٶ� 
	
	int buff_time[2];//0Ϊ�ٶȣ�1Ϊը���뾶 
	
	bool Over;

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
	
	void Is_Hurt(std::pair<int, int> Location, int r);
	//�������
	
	int get_life();
	//��ѯ���ʣ��Ѫ�� 
	
	void Create_Boom(Map& Map);
	//�ڽ��´���һ��ը�� 
	
	std::pair<int, int> Check_Boom(Map& Map);
	//���ը���Ƿ�ը
	
	void Clear_Boom(Map& Map); 
	//����Լ�ը����ը��Ļ�� 
	
	void Get_Buff(int type, int time, int level);
	//buff���ͣ��ٶȣ�ը���뾶��������ʱ�䣬buff�ȼ�
	 
	void Clear_Buff();
	//ÿһ֡����һ��buffʱ�� 
	
	int Get_Speed();
	//����ٶ�֡�� 
	
	int Get_R();
	//���ը���뾶 
};

#endif
