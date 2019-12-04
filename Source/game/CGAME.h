#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
#include <vector>
#include "CBALL.h"
#include "CBAR.h"
#include "CFOOD.h"

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

	float speed;
	bool playing_Normal;
	bool playing_Food;
	vector<CFOOD> foods;
	vector<CFOOD> obstacles;

	int time1 = -1;
	clock_t t;
	int stylePlay = 0;
public:
	CGAME(int, int);//truyền vào phím chơi game, căn chỉnh bóng và thanh chơi
	~CGAME();
	void ScoreUp(CBAR*);//Tăng điểm khi đối phương để lọt bóng
	void Draw();//Vẽ màn hình game
	void Input();//hàm bắt phím khi chơi
	void Logic();//hàm xử lý chính
	void Run();//hàm chạy game
	int ShowMenu();
	void hidecursor();
};

