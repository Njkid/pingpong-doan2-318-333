#include "CBALL.h"
//vị trí ban đầu của bóng
CBALL::CBALL(int posX, int posY)
{
	originalX = posX;
	originalY = posY;
	x = posX; y = posY;
	direction = STOP;
}
//cập nhật vị trí bóng
void CBALL::Reset()
{
	x = originalX; y = originalY;
	direction = STOP;
}
//đổi hướng bóng
void CBALL::changeDirection(eDir d)
{
	direction = d;
}
//tạo hướng bóng ngẫu nhiên đầu game
void CBALL::randomDirection()
{
	direction = (eDir)((rand() % 6) + 1);
}
//xử lý di chuyển của bóng
void CBALL::Move()
{
	switch (direction)
	{
	case STOP:
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UPLEFT:
		x--; y--;
		break;
	case DOWNLEFT:
		x--; y++;
		break;
	case UPRIGHT:
		x++; y--;
		break;
	case DOWNRIGHT:
		x++; y++;
		break;
	default:
		break;
	}
}