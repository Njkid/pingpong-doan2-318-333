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

void CFOOD::SetTopLeftX( int a) {
	_topLeft_x = a;
}

void CFOOD::SetTopLeftY(int a) {
	_topLeft_y = a;
}

void CFOOD::SetBotRightX(int a) {
	_botRight_x = a;
}

void CFOOD::SetBotRightY(int a) {
	_botRight_y = a;
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

vector<CFOOD> CFOOD::Generate()
{
	vector<CFOOD> result;
	srand(time(NULL));

	for (int i = 0; i < 12; i++)
	{
		int x = rand() % 30 + 26;
		int y = rand() % 15 + 2;
		CFOOD f(x, y, x + 3, y + 2);

		int j = 0;
		for (; j < result.size(); j++)
		{
			if (f.IsCollision(result[j])) {
				i--;
				break;
			}
		}

		if (j == result.size()) result.push_back(f);
	}


	return result;
}


vector<CFOOD> CFOOD::Obstacles()
{
	vector<CFOOD> result;
	for (int i = 0; i < 5; i++)
	{
		CFOOD a(21, 1 + 4*i, 25, 4 + 4*i);
		result.push_back(a);
	}

	return result;
}

vector<CFOOD> CFOOD::Prize()
{
	vector<CFOOD> result;

	for (int i = 0; i < 4; i++)
	{
		int x = rand() % 30 + 26;
		int y = rand() % 15 + 2;
		CFOOD f(x, y, x + 2, y + 1);

		int j = 0;
		for (; j < result.size(); j++)
		{
			if (f.IsCollision(result[j])) {
				i--;
				break;
			}
		}

		if (j == result.size()) result.push_back(f);
	}

	return result;
}

CFOOD CFOOD::CreatePrize() {
	int x = rand() % 30 + 26;
	int y = rand() % 15 + 2;
	CFOOD f(x, y, x+2, y+1);

	return f;
}

bool CFOOD::Draw_prize(int x, int y)
{
	x += 1;
	y += 1;

	CFOOD pos(x, y, x, y);
	if (pos.IsCollision(*this)) {
		SetConsoleTextAttribute(console, 236);
		cout << "?";
		SetConsoleTextAttribute(console, 7);
		return true;
	}
	return false;
}

void CFOOD::AddFoods(vector<CFOOD>& vec, int num)
{
	for (int i = 0; i < num; i++)
	{
		int x = rand() % 30 + 26;
		int y = rand() % 15 + 2;
		CFOOD f(x, y, x + 3, y + 2);

		int j = 0;
		for (; j < vec.size(); j++)
		{
			if (f.IsCollision(vec[j])) {
				i--;
				break;
			}
		}

		if (j == vec.size()) vec.push_back(f);
	}
}

void CFOOD::AddPrizes(vector<CFOOD>& vec, int num)
{
	for (int i = 0; i < num; i++)
	{
		int x = rand() % 30 + 26;
		int y = rand() % 15 + 2;
		CFOOD f(x, y, x + 2, y + 1);

		int j = 0;
		for (; j < vec.size(); j++)
		{
			if (f.IsCollision(vec[j])) {
				i--;
				break;
			}
		}

		if (j == vec.size()) vec.push_back(f);
	}
}

eDir CFOOD ::Check_collision(CBALL* ball)
{
	if (_topLeft_x < 0) return STOP;

	for (int i = _topLeft_y - 1; i < _botRight_y; i++)
	{
		if (_topLeft_x - 1 == ball->getX() && i == ball->getY() && ball->getDirection() == RIGHT) return LEFT;
		if (_botRight_x == ball->getX() && i == ball->getY() && ball->getDirection() == LEFT) return RIGHT;
	}


	for (int i = _topLeft_y - 1 ; i < _botRight_y; i++)
	{
		if (_topLeft_x -1== ball->getX() && i == ball->getY()) return ball->getDirection() == DOWNRIGHT ? DOWNLEFT : UPLEFT;
		if (_botRight_x == ball->getX() && i == ball->getY()) return ball->getDirection() == DOWNLEFT ? DOWNRIGHT : UPRIGHT;
	}


	for (int i = _topLeft_x -1; i <= _botRight_x; i++)
	{
		if (_topLeft_y - 1 == ball->getY() && i == ball->getX()) return ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT;
		if (_botRight_y  -1 == ball->getY() && i == ball->getX()) return ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT;
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

bool CFOOD::Draw_food(int x, int y)
{
	x += 1;
	y += 1;
	if (((x == _topLeft_x || x == _botRight_x) && y >= _topLeft_y && y <= _botRight_y) ||
		((y == _topLeft_y || y == _botRight_y) && x >= _topLeft_x && x <= _botRight_x)) {
		SetConsoleTextAttribute(console, 42);
		cout << "*";
		SetConsoleTextAttribute(console, 7);
		return true;
	}

	CFOOD pos(x, y, x, y);
	if (pos.IsCollision(*this)) {
		SetConsoleTextAttribute(console, 175);
		cout << " ";
		SetConsoleTextAttribute(console, 7);
		return true;
	}

	return false;
}

bool CFOOD::IsCollision(CFOOD another) {

	if (_topLeft_x < 0) return false;

	if (_topLeft_x < another._topLeft_x && _botRight_x < another._topLeft_x) return false;
	if (_topLeft_y < another._topLeft_y && _botRight_y < another._topLeft_y) return false;
	if (_topLeft_x > another._botRight_x&& _botRight_x > another._botRight_x) return false;
	if (_topLeft_y > another._botRight_y&& _botRight_y > another._botRight_y) return false;

	return true;
}

bool CFOOD::IsCollisionball(CBALL* another) {
	if (_topLeft_x < 0) return false;
	if (_topLeft_x < another->getX() && _botRight_x > another->getX()) return false;
	if (_topLeft_y < another->getY() && _botRight_y > another->getY()) return false;
	return true;
}

void CFOOD::Draw_obstacles()
{
	if (_topLeft_x < 0) return;

	GotoXY(_topLeft_x, _topLeft_y);
	for (int i = _topLeft_x; i <= _botRight_x; i++)
	{
		cout << "#";
	}
	cout << endl;
	for (int i = _topLeft_y + 1; i < _botRight_y; i++)
	{
		GotoXY(_topLeft_x, i);
		for (int j = _topLeft_x; j <= _botRight_x; j++)
		{
			if (j == _topLeft_x)
			{
				cout << "#";
			}
			else if (j == _botRight_x)
			{
				cout << "#";
			}
			else
			{
				cout << "#";
			}
		}
		cout << endl;
	}
	GotoXY(_topLeft_x, _botRight_y);
	for (int i = _topLeft_x; i <= _botRight_x; i++)
	{
		cout << "#";
	}
}

bool CFOOD::Draw_obstacles(int x, int y)
{
	if (_topLeft_x < 0) return false;

	x += 1;
	y += 1;

	CFOOD pos(x, y, x, y);
	if (pos.IsCollision(*this)) {
		SetConsoleTextAttribute(console, 12);
		cout << "#";
		SetConsoleTextAttribute(console, 7);
		return true;
	}
	return false;
}
