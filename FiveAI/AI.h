#pragma once
#include <iostream>
#include "Vecposition.h"
#include <string>
#include <graphics.h>
using namespace std;
class AI
{
public:
	AI();
	~AI();
	Vecposition aiselect();
	int easyconsider();
	int mornalconsider();
	void hardconsider();
	void alphaBetaCut(int color, int alpha, int beta, int deep, int g[15][15]);
	void numberreset();
	void g_Secondset();
	void gSecond_OneSet();
	double assessment(int x[15][15]);
	double assessment2(int x[15][15]);
	Vecposition maxVecPosition();
	double minVecPosition_Score_Second();
	double max_Score_Secend_One();
	void initScore();
	void initScore_Second();
	void initscoreSecond_One();
	void showscore();
	int checkbreak(int game[15][15],int x,int y);
	void findcompmove(int board[15][15], Vecposition &best, double &score, int layer, int alpha, int beta);
	void findhumanmove(int board[15][15], Vecposition &best, double &score, int layer_, int alpha, int beta);
private:
	int g1[15][15];
	int g_Second[15][15];
	int gSecond_One[15][15];
	int gSecond_Second[15][15];
	int gThird_One[15][15];
	int gThird_Second[15][15];
	double score[15][15];
	double score_Second[15][15];
	double scoreSecond_One[15][15];
	double scoreSecond_Second[15][15];
	int i, j;
	int x, y;
	Vecposition vec;
	double max = score[0][0];
	double min = score_Second[0][0];
	int count = 0;
	char a[50];
	double alpha=-9999, beta=9999;
	bool isbreak=false;
	bool alpha_Beta_Cut = false;
	Vecposition vec_Second;
	Vecposition mustset;
	string s;
	FILE *fp;
	errno_t err  = fopen_s(&fp, "score", "a+");
};

