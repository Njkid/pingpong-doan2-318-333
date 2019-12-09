#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;
//biến quản lý hướng bóng
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };
class CBALL
{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	CBALL(int,int);//vị trí ban đầu của bóng
	void Reset();//cập nhật vị trí bóng
	void changeDirection(eDir);//đổi hướng bóng
	void randomDirection();//tạo hướng bóng ngẫu nhiên đầu game
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }
	void Move();//xử lý di chuyển của bóng
	friend ostream& operator<<(ostream& o, CBALL c)
	{
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}

	void SetX(int a);
	void SetY(int b);
};
