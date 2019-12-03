﻿#pragma once
#include "CBALL.h"
#include <Windows.h>
class CFOOD
{
private:
	int _topLeft_x;
	int _topLeft_y;
	int _botRight_x;
	int _botRight_y;

public:
	CFOOD();
	~CFOOD();
	static void GotoXY(int x, int y);
public:
	int TopLeftX();
	int TopLeftY();
	int BotRightX();
	int BotRightY();


	
	CFOOD(int a, int b, int c, int d);
	eDir Check_collision(CBALL* ball);
	void Draw_food();
};
