#pragma once
#include "CBALL.h"
#include <Windows.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <conio.h>

class CFOOD
{
private:
	int _topLeft_x;
	int _topLeft_y;
	int _botRight_x;
	int _botRight_y;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

public:
	CFOOD();
	~CFOOD();
	static void GotoXY(int x, int y);
	static vector<CFOOD> Generate();
	static vector<CFOOD> Obstacles();
	static vector<CFOOD> Prize();
public:
	int TopLeftX();
	int TopLeftY();
	int BotRightX();
	int BotRightY();
	void SetTopLeftX(int a);
	void SetTopLeftY(int a);
	void SetBotRightX(int a);
	void SetBotRightY(int a);

	CFOOD(int a, int b, int c, int d);
	eDir Check_collision(CBALL* ball);
	void Draw_food();
	bool Draw_food(int, int);
	bool IsCollision(CFOOD);
	bool IsCollisionball(CBALL*);
	void Draw_obstacles();
	bool Draw_obstacles(int,int);

	CFOOD CreatePrize();
	bool Draw_prize(int, int);
};
