#include "CGAME.h"
//truyền vào phím chơi game, căn chỉnh bóng và thanh chơi
CGAME::CGAME(int w, int h)
{
	srand(time(NULL));
	quit = false;
	//phím chơi game
	//player 1
	up1 = 'w'; 
	down1 = 's';
	//player 2
	up2 = 'i';
	down2 = 'k';
	score1 = score2 = 0;
	width = w; height = h;
	//xếp bóng chính giữa màn hình
	ball = new CBALL(w / 2, h / 2);
	//căn chỉnh thanh chơi game
	player1 = new CBAR(1, h / 2 - 3);
	player2 = new CBAR(w - 2, h / 2 - 3);
}

CGAME::~CGAME()
{
	delete ball, player1, player2;
}
//Tăng điểm khi đối phương để lọt bóng
void CGAME::ScoreUp(CBAR* player)
{
	if (player == player1)
		score1++;
	else if (player == player2)
		score2++;

	ball->Reset();
	player1->Reset();
	player2->Reset();
}

//Vẽ màn hình game
void CGAME::Draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		printf("%c", 177);
	cout << endl;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int ballx = ball->getX();
			int bally = ball->getY();
			int player1x = player1->getX();
			int player2x = player2->getX();
			int player1y = player1->getY();
			int player2y = player2->getY();

			if (j == 0)
				printf("%c", 177);
			if (ballx == j && bally == i)
				cout << "o"; //ball
			else if (player1x == j && player1y == i)
				printf("%c", 219); //player1
			else if (player2x == j && player2y == i)
				printf("%c", 219); //player2

			else if (player1x == j && player1y + 1 == i)
				printf("%c", 219); //player1
			else if (player1x == j && player1y + 2 == i)
				printf("%c", 219); //player1
			else if (player1x == j && player1y + 3 == i)
				printf("%c", 219); //player1

			else if (player2x == j && player2y + 1 == i)
				printf("%c", 219); //player1
			else if (player2x == j && player2y + 2 == i)
				printf("%c", 219); //player1
			else if (player2x == j && player2y + 3 == i)
				printf("%c", 219); //player1
			else
				cout << " ";

			if (j == width - 1)
				printf("%c", 177);
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		printf("%c", 177);
	cout << endl;

	cout << "Player 1: " << score1 << endl << "Player 2: " << score2 << endl;
	if (score1 == 5 || score2 == 5) {
		cout << " Congrats,you won!!!";
		cout << "\n Press any key to play again ^^";
		system("pause");
		ball->Reset();
		player1->Reset();
		player2->Reset();
		score1 = 0;
		score2 = 0;
	};
}
//hàm bắt phím khi chơi
void CGAME::Input()
{
	ball->Move();

	int ballx = ball->getX();
	int bally = ball->getY();
	int player1x = player1->getX();
	int player2x = player2->getX();
	int player1y = player1->getY();
	int player2y = player2->getY();

	if (_kbhit())
	{
		char current = _getch();
		if (current == up1)
			if (player1y > 0)
				player1->moveUp();
		if (current == up2)
			if (player2y > 0)
				player2->moveUp();
		if (current == down1)
			if (player1y + 4 < height)
				player1->moveDown();
		if (current == down2)
			if (player2y + 4 < height)
				player2->moveDown();

		if (ball->getDirection() == STOP)
			ball->randomDirection();

		if (current == 'q')
			quit = true;
	}
}
//hàm xử lý chính
void CGAME::Logic()
{
	int ballx = ball->getX();
	int bally = ball->getY();
	int player1x = player1->getX();
	int player2x = player2->getX();
	int player1y = player1->getY();
	int player2y = player2->getY();

	//left bar
	for (int i = 0; i < 4; i++)
		if (ballx == player1x + 1)
			if (bally == player1y + i)
				ball->changeDirection((eDir)((rand() % 3) + 4));

	//right bar
	for (int i = 0; i < 4; i++)
		if (ballx == player2x - 1)
			if (bally == player2y + i)
				ball->changeDirection((eDir)((rand() % 3) + 1));

	//bottom wall
	if (bally == height - 1)
		ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
	//top wall
	if (bally == 0)
		ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
	//right wall
	if (ballx == width - 1)
		ScoreUp(player1);
	//left wall
	if (ballx == 0)
		ScoreUp(player2);
}
//hàm chạy game
void CGAME::Run()
{
	while (!quit)
	{
		Draw();
		Input();
		Logic();
	}
}

