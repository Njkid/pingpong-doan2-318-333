#include "CGAME.h"
//truyền vào phím chơi game, căn chỉnh bóng và thanh chơi
CGAME::CGAME(int w, int h)
{
	srand(time(NULL));
	hidecursor();
	console = GetStdHandle(STD_OUTPUT_HANDLE);

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
	ball = new CBALL(w / 4, h / 2);
	//căn chỉnh thanh chơi game
	player1 = new CBAR(1, h / 2 - 3);
	player2 = new CBAR(w - 2, h / 2 - 3);

	//điều chỉnh thời gian update frame
	speed = 1000.f / 30.f;

	//cài đặt chế độ chơi
	playing_Food = false;
	playing_Normal = false;

	//khởi tạo foods
	foods = CFOOD::Generate();
	prizes = CFOOD::Prize();
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
			// Update coordinate ball and player1 when save
			if (save == true)
			{
				ball->SetX(file_save[0]);
				ball->SetY(file_save[1]);
				switch (file_save[2])
				{
				case 0:
					ball->changeDirection(STOP);
					break;
				case 1:
					ball->changeDirection(LEFT);
					break;
				case 2:
					ball->changeDirection(RIGHT);
					break;
				case 3:
					ball->changeDirection(UPLEFT);
					break;
				case 4:
					ball->changeDirection(DOWNLEFT);
					break;
				case 5:
					ball->changeDirection(UPRIGHT);
					break;
				case 6:
					ball->changeDirection(DOWNRIGHT);
					break;
				}
			}

			if (j == 0)
				printf("%c", 177);
			if (ballx == j && bally == i && save != true) {
				if (ball->isDestroyer()) cout << "x";
				else cout << "o"; //ball
			}
			else if(save == true && file_save[0] == j && file_save[1]== i)
				cout << "O"; //ball saved
			else if (player1x == j && player1y == i && save != true)
				printf("%c", 219); //player1
			else if (save == true && file_save[3] == j && file_save[4] == i)
				printf("%c", 219); //player1 saved
			else if (player2x == j && player2y == i && playing_Normal)
				printf("%c", 219); //player2

			else if (player1x == j && player1y + 1 == i && save != true)
				printf("%c", 219); //player1
			else if (player1x == j && player1y + 2 == i && save != true)
				printf("%c", 219); //player1
			else if (player1x == j && player1y + 3 == i && save != true)
				printf("%c", 219); //player1
			else if (save == true && file_save[3] == j && file_save[4] + 1 == i)
				printf("%c", 219); //player1 saved
			else if (save == true && file_save[3] == j && file_save[4] + 2 == i)
				printf("%c", 219); //player1 saved
			else if (save == true && file_save[3] == j && file_save[4] + 3 == i)
				printf("%c", 219); //player1 saved
			else if (player2x == j && player2y + 1 == i && playing_Normal)
				printf("%c", 219); //player2
			else if (player2x == j && player2y + 2 == i && playing_Normal)
				printf("%c", 219); //player2
			else if (player2x == j && player2y + 3 == i && playing_Normal)
				printf("%c", 219); //player2
			else {

				// Draw food or obstacles
				bool space = true;
				if (playing_Food) {
					
					for (int k = 0; k < foods.size(); k++)
					{
						space = !(foods[k].Draw_food(j, i));
						if (!space) break;
					}
					
					if (space) {

						for (int k = 0; k < time1; k++)
						{
							space = !(obstacles[k].Draw_obstacles(j, i));
							if (!space) break;
						}

						if (space)
						if (obstacles.size() > 5) {
							for (int k = 5; k < obstacles.size(); k++)
							{
								space = !(obstacles[k].Draw_obstacles(j, i));
								if (!space) break;
							}
						}
						
					}

					if (space) {
						
						for (int k = 0; k < prizes.size(); k++)
						{
							space = !(prizes[k].Draw_prize(j, i));
							if (!space) break;
						}
				
					}

				}

				// There is nothing to draw
				if (space) cout << " ";
			}

			if (j == width - 1)
				printf("%c", 177);
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		printf("%c", 177);
	cout << endl;

	//Process information for playing with style Normal
	if (playing_Normal) {
		cout << "Player 1: " << score1 << endl << "Player 2: " << score2 << endl;
		if (score1 == 5 || score2 == 5) {
			cout << " Congrats,you won!!!";
			cout << "\n Press any key to play again ^^";
			system("pause");
			ball->Reset();
			player1->Reset();
			player2->Reset();
			time1 = -1;
			time2 = -1;
			score1 = 0;
			score2 = 0;
		};
	}

	//Process information for playing with style Eating Food
	if (playing_Food) {
		cout << "YOUR SCORE: " << score1 << endl;

		// WIN for playing with style Eating Food
		if (foods.size() == 0) {
			cout << " Congrats,you won!!!";
			cout << " Enter your name:                                      " << endl;
			string name = "";
			while (name[0] < 32) {
				getline(cin, name);
			}
			CSAVE::High_scores(score1,name);
			ShowTopScore();
			cout << "\n Press any key to play again ^^";
			system("pause");
			system("cls");
			ball->Reset();
			player1->Reset();
			player2->Reset();
			time1 = -1;
			time2 = -1;
			foods = CFOOD::Generate();
			prizes = CFOOD::Prize();
			obstacles = CFOOD::Obstacles();
			t = clock();
			score1 = 0;
			score2 = 0;
			speed = 1000.f / 30.f;
		}

		// LOSE because of time over
		if (time1 == 5)
		{
			// ket qua choi
			/*high_scores = CSAVE::Load_highscores();
			for (int i = 0; i < high_scores.size(); i = i + 2)
			{
				cout << high_scores[i] << "         " << high_scores[i + 1] << endl;
			}*/

			ShowTopScore();


			cout << " TIME OVER,you lose!!!";
			cout << "\n Press any key to play again ^^";

			system("pause");
			system("cls");
			ball->Reset();
			player1->Reset();
			player2->Reset();
			foods = CFOOD::Generate();
			prizes = CFOOD::Prize();
			obstacles = CFOOD::Obstacles();
			time1 = -1;
			time2 = -1;
			t = clock();
			score1 = 0;
			score2 = 0;
			speed = 1000.f / 30.f;
		}

		cout << "Key input: | 'W' : move up | 'S' : move down | 'L' : save game |";
	}

	// Update coordinate food when save
	if (save == true)
	{
		score1 = file_save[5];

		foods.clear();
		int size_food = file_save[6]*4 + 7;
		CFOOD food;
		for (int i = 7; i < size_food; i = i + 4)
		{
			food.SetTopLeftX(file_save[i]);
			food.SetTopLeftY(file_save[i + 1]);
			food.SetBotRightX(file_save[i + 2]);
			food.SetBotRightY(file_save[i + 3]);
			foods.push_back(food);
		}

		obstacles.clear();
		int size_obs = file_save[size_food]*4 + size_food + 1;

		for (int i = size_food + 1; i < size_obs; i = i + 4)
		{
			food.SetTopLeftX(file_save[i]);
			food.SetTopLeftY(file_save[i + 1]);
			food.SetBotRightX(file_save[i + 2]);
			food.SetBotRightY(file_save[i + 3]);
			obstacles.push_back(food);
		}

		prizes.clear();
		int size_prize = file_save[size_obs]*4 + size_obs + 1;

		for (int i = size_obs + 1; i < size_prize; i = i + 4)
		{
			food.SetTopLeftX(file_save[i]);
			food.SetTopLeftY(file_save[i + 1]);
			food.SetBotRightX(file_save[i + 2]);
			food.SetBotRightY(file_save[i + 3]);
			prizes.push_back(food);
		}
	}

	//// Draw food
	//if (playing_Food) {
	//	for (int i = 0; i < foods.size(); i++)
	//	{
	//		foods[i].Draw_food();
	//	}
	//}

	//// Draw obstacles
	if (playing_Food) {
		if (time1 < int(obstacles.size()) && time2 < (clock() - t) / 10000)
		{
			time2 = (clock() - t) / 10000;
			time1++;
		}

	//	for (int i = 0; i < time1; i++)
	//	{
	//		obstacles[i].Draw_obstacles();
	//	}
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

		if (current == 'l')
		{
			CSAVE::Save(ball, player1, score1, foods, obstacles, prizes, time1); // save game
		}
	}

	//Let CPU play for player2
	/*if (bally > player2y + 2 && player2y < 17) {
		player2->moveDown();
	}
	if (bally < player2y + 2 && player2y > 0) {
		player2->moveUp();
	}*/

	//Let CPU play for player1
	if (bally > player1y + 1 && player1y < 16) {
		player1->moveDown();
	}
	if (bally < player1y + 1 && player1y > 0) {
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
			if (bally == player1y + i) {
				speed *= 0.9f;
				if (ball->getDirection() == LEFT) {
					ball->changeDirection((eDir)(RIGHT));
					if (player1->getOldY() > player1y) {
						ball->changeDirection((eDir)(UPRIGHT));
					}
					if (player1->getOldY() < player1y) {
						ball->changeDirection((eDir)(DOWNRIGHT));
					}
				}

				if (ball->getDirection() == UPLEFT) {
					ball->changeDirection((eDir)(UPRIGHT));
					if (player1->getOldY() < player1y) {
						ball->changeDirection((eDir)(RIGHT));
					}
				}

				if (ball->getDirection() == DOWNLEFT) {
					ball->changeDirection((eDir)(DOWNRIGHT));
					if (player1->getOldY() > player1y) {
						ball->changeDirection((eDir)(RIGHT));
					}
				}
			}

	//right bar
	for (int i = 0; i < 4; i++)
		if (ballx == player2x - 1)
			if (bally == player2y + i)
			{
				if (ball->getDirection() == RIGHT) {
					ball->changeDirection((eDir)(LEFT));
				}

				if (ball->getDirection() == UPRIGHT) {
					ball->changeDirection((eDir)(UPLEFT));
				}

				if (ball->getDirection() == DOWNRIGHT) {
					ball->changeDirection((eDir)(DOWNLEFT));
				}
			}

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

	if (playing_Food) {
		//collision with food
		eDir collisionFood = (eDir)0;
		for (int i = 0; i < foods.size(); i++)
		{
			collisionFood = foods[i].Check_collision(ball);
			if (collisionFood == 0) continue;
			ball->changeDirection(collisionFood);

			//Effect when collsion a food
			//examble delete food
			for (int j = i; j < foods.size() - 1; j++)
			{
				foods[j] = foods[j + 1];
			}
			foods.pop_back();

			// Gain score
			score1 += 1;
		}

		//collision with prizes
		collisionFood = (eDir)0;
		for (int i = 0; i < prizes.size(); i++)
		{
			collisionFood = prizes[i].Check_collision(ball);
			if (collisionFood == 0) continue;
			//ball->changeDirection(collisionFood);

			//Effect when collsion a food

			// Add buff
			int buff = rand() % 6;
			switch (buff)
			{
			case 0:
				score1 *= 2;
				SetConsoleTextAttribute(console, 236);
				CFOOD::GotoXY(ballx - 5, bally);
				cout << "BUFF SCOREx2";
				Sleep(600);
				CFOOD::GotoXY(ballx - 5, bally);
				SetConsoleTextAttribute(console, 7);
				cout << "             ";
				CFOOD::GotoXY(0, 0);
				
				break;
			case 1:
				score1 *= 3;
				SetConsoleTextAttribute(console, 236);
				CFOOD::GotoXY(ballx - 5, bally);
				cout << "BUFF SCOREx3";
				Sleep(600);
				CFOOD::GotoXY(ballx - 5, bally);
				SetConsoleTextAttribute(console, 7);
				cout << "             ";
				
				CFOOD::GotoXY(0, 0);
				break;
			case 2:
				SetConsoleTextAttribute(console, 192);
				CFOOD::GotoXY(ballx - 5, bally);
				cout << "WALL! :v";
				obstacles.push_back(prizes[i]);
				Sleep(600);
				CFOOD::GotoXY(ballx - 5, bally);
				SetConsoleTextAttribute(console, 7);
				cout << "             ";
				
				CFOOD::GotoXY(0, 0);
				
				break;

			case 3:
				SetConsoleTextAttribute(console, 236);
				CFOOD::GotoXY(ballx - 5, bally);
				cout << "ADD 3 FOODS";
				Sleep(600);
				CFOOD::GotoXY(ballx - 5, bally);
				SetConsoleTextAttribute(console, 7);
				cout << "             ";
				CFOOD::GotoXY(0, 0);

				CFOOD::AddFoods(foods, 3);
				break;

			case 4:

				SetConsoleTextAttribute(console, 236);
				CFOOD::GotoXY(ballx - 5, bally);
				cout << "ADD 2 PRIZES";
				Sleep(600);
				CFOOD::GotoXY(ballx - 5, bally);
				SetConsoleTextAttribute(console, 7);
				cout << "             ";
				CFOOD::GotoXY(0, 0);

				CFOOD::AddPrizes(prizes, 2);
				break;

			case 5:

				SetConsoleTextAttribute(console, 236);
				CFOOD::GotoXY(ballx - 5, bally);
				cout << ">DESTROYER!<";
				Sleep(600);
				CFOOD::GotoXY(ballx - 5, bally);
				SetConsoleTextAttribute(console, 7);
				cout << "             ";
				CFOOD::GotoXY(0, 0);

				ball->SetDestroyer(true);
				break;
			default:
				break;
			}

			//delete prizes
			for (int j = i; j < prizes.size() - 1; j++)
			{
				prizes[j] = prizes[j + 1];
			}
			prizes.pop_back();
		}

		// check collision with obstacles
		for (int i = 0; i < time1; i++)
		{
			if (obstacles[i].Check_collision(ball) != STOP)
			{
				ball->changeDirection(obstacles[i].Check_collision(ball));
				if (ball->isDestroyer()) obstacles[i].SetTopLeftX(-1);
			}
		}

		if (obstacles.size() > 5) {
			for (int k = 5; k < obstacles.size(); k++)
			{
				if (obstacles[k].Check_collision(ball) != STOP)
				{
					ball->changeDirection(obstacles[k].Check_collision(ball));
					if (ball->isDestroyer()) obstacles[k].SetTopLeftX(-1);
				}
			}
		}
	}

	//CHECK AND DELETE----------------------------------------

	/*for (int i = 0; i < time1; i++)
	{
		if (obstacles[i].Check_collision(ball) != STOP)
		{
			ball->changeDirection(obstacles[i].Check_collision(ball));
			for (int j = i; j < int(obstacles.size()) - 1; j++)
			{
				obstacles[j] = obstacles[j + 1];
			}
			obstacles.pop_back();
			time1--;
		}
	}*/

}
//hàm chạy game
void CGAME::Run()
{
	// Unit obstacles
	obstacles = CFOOD::Obstacles();



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
		t = clock();
		break;
	case 3:
		save = true;
		player2->setOriX(player2->getX() + 1);
		player2->Reset();
		file_save = CSAVE::Load_game();
		time1 = file_save[file_save.size() - 1] - 1;
		playing_Normal = false;
		playing_Food = true;
		
		break;
	case 4:
		quit = true;
	}
	
	while (!quit)
	{
		Draw();
		Input();
		Logic();
		save = false;
	}
}

void CGAME::ShowTopScore()
{
	cout << "==TOP HIGH SCORES===" << endl;
	vector<string> table = CSAVE::Load_highscores();
	for (int i = 0; i < table.size(); i++)
	{
		cout << "Top " << i / 2 + 1 << ": ";
		cout << table[i++];
		cout << "   >>  " << table[i] << endl;
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
	cout << "|                3. Load game                      |" << endl;
	cout << "|                4. Quit                           |" << endl;
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
