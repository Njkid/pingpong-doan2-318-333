#include "CSAVE.h"



CSAVE::CSAVE()
{
}


CSAVE::~CSAVE()
{
}

void CSAVE::Save(CBALL *ball, CBAR *bar_left, int score, vector<CFOOD> food, vector<CFOOD> obs, vector<CFOOD> prize, int time1)
{
	ofstream file;
	file.open("Save_game.txt");
	file << ball->getX() << "\n";
	file << ball->getY() << "\n";
	file << ball->getDirection() << "\n";
	file << bar_left->getX() << "\n";
	file << bar_left->getY() << "\n";
	file << score << "\n";
	file << int(food.size()) << "\n";
	for (int i = 0; i<int(food.size()); i++)
	{
		file << food[i].TopLeftX() << "\n";
		file << food[i].TopLeftY() << "\n";
		file << food[i].BotRightX() << "\n";
		file << food[i].BotRightY() << "\n";
	}

	file << int(obs.size()) << "\n";
	for (int i = 0; i<int(obs.size()); i++)
	{
		file << obs[i].TopLeftX() << "\n";
		file << obs[i].TopLeftY() << "\n";
		file << obs[i].BotRightX() << "\n";
		file << obs[i].BotRightY() << "\n";
	}

	file << int(prize.size()) << "\n";
	for (int i = 0; i<int(prize.size()); i++)
	{
		file << prize[i].TopLeftX() << "\n";
		file << prize[i].TopLeftY() << "\n";
		file << prize[i].BotRightX() << "\n";
		file << prize[i].BotRightY() << "\n";
	}

	file << time1;
	file.close();
}

vector<int> CSAVE::Load_game()
{
	ifstream file;
	vector<int> info;
	string line;
	file.open("Save_game.txt");
	while (getline(file, line))
	{
		info.push_back(stoi(line));
	}
	file.close();
	return info;
}


void CSAVE::High_scores(int score, string name1)
{
	fstream file;
	vector <string> table;
	vector <string> name;
	string line;
	file.open("High_scores.txt", ios::in);
	if (file.good())
	{
		while (getline(file, line))
		{
			name.push_back(line);
			getline(file, line);
			table.push_back(line);
		}
		name.push_back(name1);
		table.push_back(to_string(score));
		file.close();
		file.open("High_scores.txt", ios::out);
		for (int i = 0; i<int(table.size()) - 1; i++)
		{
			for (int j = i + 1; j<int(table.size()); j++)
			{
				if (stoi(table[j]) > stoi(table[i]))
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

			// Save only top 15
			if (i >= 15) break;
		}
		file.close();
	}
}

vector<string> CSAVE::Load_highscores()
{
	fstream file;
	vector <string> table;
	string line;
	file.open("High_scores.txt", ios::in);
	while (getline(file, line))
	{
		table.push_back(line);
	}
	return table;
}
