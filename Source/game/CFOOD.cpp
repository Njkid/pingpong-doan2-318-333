#include "CFOOD.h"

CFOOD::CFOOD(int a, int b, int c, int d)
{
	_topLeft_x = a;
	_topLeft_y = b;
	_botRight_x = c;
	_botRight_y = d;
}


CFOOD::CFOOD()
{
}


CFOOD::~CFOOD()
{
}

int CFOOD::TopLeftX() {
	return _topLeft_x;
}

int CFOOD::TopLeftY() {
	return _topLeft_y;
}

int CFOOD::BotRightX() {
	return _botRight_x;
}

int CFOOD::BotRightY() {
	return _botRight_y;
}

void CFOOD::GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

eDir CFOOD ::Check_collision(CBALL* ball)
{
	for (int i = _topLeft_y; i <= _botRight_y; i++)
	{
		if (_topLeft_x - 1 == ball->getX() && i == ball->getY()) return ball->getDirection() == DOWNRIGHT ? DOWNLEFT : UPLEFT;
		if (_botRight_x + 1 == ball->getX() && i == ball->getY()) return ball->getDirection() == DOWNLEFT ? DOWNRIGHT : UPRIGHT;
	}

	for (int i = _topLeft_x; i <= _botRight_x; i++)
	{
		if (_topLeft_y - 1 == ball->getY() && i == ball->getX()) return ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT;
		if (_botRight_y + 1 == ball->getY() && i == ball->getX()) return ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT;
	}
	return STOP;
}

void CFOOD::Draw_food()
{
	GotoXY(_topLeft_x, _topLeft_y);
	for (int i = _topLeft_x; i <= _botRight_x; i++)
	{
		cout << "*";
	}
	cout << endl;
	for (int i = _topLeft_y + 1; i < _botRight_y; i++)
	{
		GotoXY(_topLeft_x, i);
		for (int j = _topLeft_x; j <= _botRight_x; j++)
		{
			if (j == _topLeft_x)
			{
				cout << "*";
			}
			else if (j == _botRight_x)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	GotoXY(_topLeft_x, _botRight_y);
	for (int i = _topLeft_x; i <= _botRight_x; i++)
	{
		cout << "*";
	}
}