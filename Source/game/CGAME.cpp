#include "CGAME.h"
//truyền vào phím chơi game, căn chỉnh bóng và thanh chơi
CGAME::CGAME(int w, int h)
{
	srand(time(NULL));
	hidecursor();

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

	//điều chỉnh thời gian update frame
	speed = 1000.f / 120.f;

	//cài đặt chế độ chơi
	playing_Food = false;
	playing_Normal = false;

	//khởi tạo foods
	foods = CFOOD::Generate();
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
	//system("cls");
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
				cout << "O"; //ball
			else if (player1x == j && player1y == i)
				printf("%c", 219); //player1
			else if (player2x == j && player2y == i && playing_Normal)
				printf("%c", 219); //player2

			else if (player1x == j && player1y + 1 == i)
				printf("%c", 219); //player1
			else if (player1x == j && player1y + 2 == i)
				printf("%c", 219); //player1
			else if (player1x == j && player1y + 3 == i)
				printf("%c", 219); //player1

			else if (player2x == j && player2y + 1 == i && playing_Normal)
				printf("%c", 219); //player1
			else if (player2x == j && player2y + 2 == i && playing_Normal)
				printf("%c", 219); //player1
			else if (player2x == j && player2y + 3 == i && playing_Normal)
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

	//Win for playing with style Normal
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


	// WIN for playing with style Eating Food
	if (foods.size() == 0) {
		cout << " Congrats,you won!!!";
		cout << "\n Press any key to play again ^^";
		system("pause");
		ball->Reset();
		player1->Reset();
		player2->Reset();
		foods = CFOOD::Generate();
		score1 = 0;
		score2 = 0;
	}

	// LOSE because of time over
	if (time1 == 5)
	{
		cout << " TIME OVER,you lose!!!";
		cout << "\n Press any key to play again ^^";
		system("pause");
		ball->Reset();
		player1->Reset();
		player2->Reset();
		foods = CFOOD::Generate();
		time1 = -1;
		t = clock();
		score1 = 0;
		score2 = 0;
	}

	// Draw food
	for (int i = 0; i < foods.size(); i++)
	{
		foods[i].Draw_food();
	}

	// Draw obstacles
	if (time1 < 5)
	{
		time1 = (clock() - t) / 10000;
	}
	obstacles = CFOOD::Obstacles();
	for (int i = 0; i < time1; i++)
	{
		obstacles[i].Draw_obstacles();
	}


	CFOOD::GotoXY(0, 0);
	Sleep(int(speed));
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

	//Let CPU play for player2
	/*if (bally > player2y + 2 && player2y < 17) {
		player2->moveDown();
	}
	if (bally < player2y + 2 && player2y > 0) {
		player2->moveUp();
	}*/

	//Let CPU play for player1
	if (bally > player1y + 2 && player1y < 17) {
		player1->moveDown();
	}
	if (bally < player1y + 2 && player1y > 0) {
		player1->moveUp();
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
	if (ballx == width - 1 && stylePlay == 1)
		ScoreUp(player1);
	if (ballx == width - 1)
	{
		ball->changeDirection(ball->getDirection() == DOWNRIGHT ? DOWNLEFT : UPLEFT);
	}
	//left wall
	if (ballx == 0)
		ScoreUp(player2);

	//collision with food
	eDir collisionFood = (eDir)0;
	for (int i = 0; i < foods.size(); i++)
	{
		collisionFood = foods[i].Check_collision(ball);
		if (collisionFood == 0) continue;
		ball->changeDirection(collisionFood);

		//Effect when collsion a food
		//examble delete food
		for (int j = i; j < foods.size() -1; j++)
		{
			foods[j] = foods[j + 1];
		}
		foods.pop_back();

	}

	// check collision with obstacles
	for (int i = 0; i < time1; i++)
	{
		if (obstacles[i].Check_collision(ball) != STOP)
		{
			ball->changeDirection(obstacles[i].Check_collision(ball));
		}
	}
}
//hàm chạy game
void CGAME::Run()
{
	while (stylePlay < 1 || stylePlay > 3) {
		stylePlay = ShowMenu();
	}

	switch (stylePlay)
	{
	case 1:
		playing_Normal = true;
		break;
	case 2:
		playing_Food = true;
		player2->setOriX(player2->getX() + 1);
		player2->Reset();
		break;
	case 3:
		quit = true;
	}
	
	t = clock();
	while (!quit)
	{
		Draw();
		Input();
		Logic();
	}
}

int CGAME::ShowMenu()
{
	int choose = 0;
	cout << "====================================================" << endl;
	cout << "|                   @ PING PONG @                  |" << endl;
	cout << "|--------------------------------------------------|" << endl;
	cout << "|                1. Play Normal Style              |" << endl;
	cout << "|                2. Play Eat Food Style            |" << endl;
	cout << "|                3. Quit                           |" << endl;
	cout << "====================================================" << endl;
	cout << "==  YOUR CHOOSE? "; 
	cin >> choose;
	system("cls");
	return choose;
}

// https://stackoverflow.com/questions/30126490/how-to-hide-console-cursor-in-c
void CGAME::hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
