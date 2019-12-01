#include "CBAR.h"
CBAR::CBAR()
{
	x = y = 0;
}
//vị trí ban đầu thanh chơi
CBAR::CBAR(int posX, int posY) : CBAR()
{
	originalX = posX;
	originalY = posY;
	x = posX;
	y = posY;
}