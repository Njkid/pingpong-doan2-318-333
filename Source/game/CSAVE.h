#pragma once
#include <iostream>
#include"CGAME.h"
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
	void Save(CBALL ball, CBAR bar_left, CBAR bar_right, vector<CFOOD> food);
	void High_scores(int score);
};

