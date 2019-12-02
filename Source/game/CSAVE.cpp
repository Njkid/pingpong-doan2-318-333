#include "CSAVE.h"



CSAVE::CSAVE()
{
}


CSAVE::~CSAVE()
{
}

void CSAVE::Save(CBALL ball, CBAR bar_left, CBAR bar_right, vector<CFOOD> food)
{
	ofstream file;
	file.open("Save_game.txt");
	file << ball.getX();
	file << ball.getY();
	file << ball.getDirection();
	file << bar_left.getX();
	file << bar_left.getY();
	file << bar_right.getX();
	file << bar_right.getY();
	for (int i = 0; i<int(food.size()); i++)
	{
		file << food[i].TopLeftX();
		file << food[i].TopLeftY();
		file << food[i].BotRightX();
		file << food[i].BotRightY();
	}
}

void CSAVE::High_scores(int score)
{
	fstream file;
	vector <string> table;
	vector <string> name;
	string line;
	file.open("High_scores.txt", ios::in);
	if (file.fail() == false)
	{
		while (getline(file, line))
		{
			name.push_back(line);
			getline(file, line);
			table.push_back(line);
		}
		file.close();
		file.open("High_scores.txt", ios::out);
		for (int i = 0; i<int(table.size()) - 1; i++)
		{
			for (int j = i + 1; j<int(table.size()); j++)
			{
				if (table[j] > table[i])
				{
					string c;
					c = table[i];
					table[i] = table[j];
					table[j] = c;
					c = name[i];
					name[i] = name[j];
					name[j] = c;
				}
			}
		}
		for (int i = 0; i<int(table.size()); i++)
		{
			file << name[i] << "\n";
			file << table[i] << "\n";
		}
		file.close();
	}
}