#pragma once
#include <iostream>
#include "CGAME.h"
#include "CFOOD.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class CSAVE
{
public:
	CSAVE();
	~CSAVE();
public:
	static vector<int> Load_game();
	static void Save(CBALL *ball, CBAR *bar_left, int score, vector<CFOOD> food, vector<CFOOD> obs, vector<CFOOD> prize, int time1);
	static vector<string> Load_highscores();
public:
	void High_scores(int score, string name1);
};
