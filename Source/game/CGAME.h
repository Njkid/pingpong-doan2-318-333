#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
#include "CBALL.h"
#include "CBAR.h"

class CGAME
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	CBALL* ball;
	CBAR* player1;
	CBAR* player2;
public:
	CGAME(int, int);//truyền vào phím chơi game, căn chỉnh bóng và thanh chơi
	~CGAME();
	void ScoreUp(CBAR*);//Tăng điểm khi đối phương để lọt bóng
	void Draw();//Vẽ màn hình game
	void Input();//hàm bắt phím khi chơi
	void Logic();//hàm xử lý chính
	void Run();//hàm chạy game
};

