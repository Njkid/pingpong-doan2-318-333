#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;
class CBAR
{
private:
	int x, y;
	int old_x, old_y;
	int originalX, originalY;
public:
	CBAR();
	CBAR(int, int);//vị trí ban đầu thanh chơi
	inline void Reset() { old_x = x = originalX; old_y = y = originalY; }//cập nhật vị trí thanh chơi khi người chơi di chuyển
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline int getOldY() { return old_y; }
	//xử lý di chuyển thanh chơi của 2 player khi chơi
	inline void moveUp() { old_y = y;  y--; }
	inline void moveDown() { old_y = y; y++; }
	//cài đặt cho chế dộ eat food
	inline void setOriX(int value) { originalX = value; }
	inline void setX(int value) { x = value; }

	friend ostream& operator<<(ostream& o, CBAR c)
	{
		o << "BAR [" << c.x << "," << c.y << "]";
		return o;
	}
};

