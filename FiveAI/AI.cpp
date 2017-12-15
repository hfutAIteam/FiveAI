 #include "AI.h"
#include <time.h>  
int leavesNumber = 0;
extern int game[15][15];
extern bool aifirst;
AI::AI()
{
	numberreset();
}

AI::~AI()
{

}

Vecposition AI::maxVecPosition()
{
	vec = Vecposition(0, 0);
	max = -999999;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (score[i][j] == 0)
				continue;
			else if (score[i][j]>max)
			{
				max = score[i][j];
				vec = Vecposition(i * 50, 50 * j);
			}
		}
	return vec;
}

double AI::minVecPosition_Score_Second()
{
	
	min = 9999;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (score_Second[i][j] == 0)
				continue;
			else if (score_Second[i][j]<min)
			{
				min = score_Second[i][j];
			}
		}
	return min;
}

double AI::max_Score_Secend_One()
{
	max = -9999;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (scoreSecond_One[i][j] == 0)
				continue;
			else if (scoreSecond_One[i][j]>max)
			{
				max = scoreSecond_One[i][j];
			}
		}
	return max;
}

Vecposition AI::aiselect()
{ 
	//easyconsider();				/*需要修改评价函数*/
	//mornalconsider();
	//hardconsider();
	//return maxVecPosition();
	double score = 0;
	int layer = 0;
	Vecposition best;
	findcompmove(game, best, score, layer, -9999, 9999);
	return best;
}
void AI::showscore()
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	settextstyle(&f);

	for (int j = 0; j < 15; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			sprintf_s(a, "%.4f ", score[i][j]);
			s += a;
			if (score[i][j] < 100 && score[i][j] > -100) s += "  ";
			if (score[i][j] < 10 && score[i][j] > -10) s += "  ";
		}
		outtextxy(750, 60 + j * 50, s.c_str());
		s = "";
	}
}

int  AI::checkbreak(int game[15][15], int x, int y)
{
	x++; y++;
	int winscore = 0;
	{
		i = x;
		j = y;
		j -= 4;
		if (j < 1)	j = 1;
		if (game[i - 1][j - 1] != 0 &&
			game[i - 1][j] == game[i - 1][j - 1] &&
			game[i - 1][j + 1] == game[i - 1][j - 1] &&
			game[i - 1][j + 2] == game[i - 1][j - 1] &&
			game[i - 1][j + 3] == game[i - 1][j - 1])
			winscore = 9999;
	}
	//横排检查



	{
		i = x;
		j = y;
		i -= 4;
		if (i < 1)	i = 1;
		for (int count = 0; count < 5; count++, i++)
			if (game[i - 1][j - 1] != 0 &&
				game[i][j - 1] == game[i - 1][j - 1] &&
				game[i + 1][j - 1] == game[i - 1][j - 1] &&
				game[i + 2][j - 1] == game[i - 1][j - 1] &&
				game[i + 3][j - 1] == game[i - 1][j - 1])
				winscore = 9999;

	}
	//右斜检查
	{
		i = x;
		j = y;
		i -= 4;
		j -= 4;
		while (i < 1 || j < 1)
		{
			i++; j++;
		}

		if (game[i - 1][j - 1] != 0 &&
			game[i][j] == game[i - 1][j - 1] &&
			game[i + 1][j + 1] == game[i - 1][j - 1] &&
			game[i + 2][j + 2] == game[i - 1][j - 1] &&
			game[i + 3][j + 3] == game[i - 1][j - 1])
			winscore = 9999;
	}
	//左斜检查
	{
		i = x;
		j = y;
		i += 4;
		j -= 4;
		while (i > 15 || j < 1)
		{
			i--; j++;
		}

		if (game[i - 1][j - 1] != 0 &&
			game[i - 2][j] == game[i - 1][j - 1] &&
			game[i - 3][j + 1] == game[i - 1][j - 1] &&
			game[i - 4][j + 2] == game[i - 1][j - 1] &&
			game[i - 5][j + 3] == game[i - 1][j - 1])
			winscore = 9999;
	}

	/*if (game[i][j] = -1)	winscore = -winscore;

	if (aifirst == false)	winscore = -winscore;*/
	return winscore;
}

void AI::initScore()
{
	for (int i = 0; i < 15; i++)				//初始化score
		for (int j = 0; j < 15; j++)
		{
			score[i][j] = 0;
		}
}
void AI::initScore_Second()
{
	for (int i = 0; i < 15; i++)				//初始化score
		for (int j = 0; j < 15; j++)
			score_Second[i][j] = 0;
}
int AI::easyconsider()
{
	initScore();
	for (i = 0; i < 15; i++)		//只计算当前最优解
		for (j = 0; j < 15; j++)
		{
			numberreset();
			if (g1[i][j] != 0) {
				score[i][j] = 0;
				continue;
			}
			else {
				if (aifirst == true)	g1[i][j] = 1;
				if (aifirst == false)	g1[i][j] = -1;
				score[i][j] += assessment2(g1) + 0.01*(49 - (i - 7)*(i - 7)) + 0.01*(49 - (j - 7)*(j - 7));
			}
		}
	setfillcolor(LIGHTGRAY);
	fillrectangle(750, 0, 2024, 750);
	return 0;
}

int AI::mornalconsider()
{
	initScore();
	int imax = 0, imin = 0, jmax = 0, jmin = 0;
	imax = 0, imin = 15, jmax = 0, jmin = 15;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (game[i][j] != 0)
			{
				if (i >= imax)	imax = i + 3;
				if (i <= imin)	imin = i - 3;
				if (j >= jmax)	jmax = j + 3;
				if (j <= jmin)	jmin = j - 3;

				if (imax > 14)	imax = 14;
				if (imin < 0)	imin = 0;
				if (jmax > 14)	jmax = 14;
				if (jmin < 0)	jmin = 0;
			}
		}
	if (imin == 15) { imax = 7; imin = 7; jmax = 7; jmin = 7; }

	//int imin = 0, jmin = 0, imax = 14, jmax = 14;
	for (int i = imin; i < imax + 1; i++)		//只计算当前最优解
		for (int j = jmin; j < jmax + 1; j++)
		{
			numberreset();
			initScore_Second();
			if (g1[i][j] != 0) {
				score[i][j] = 0;
				continue;
			}
			else {
				if (aifirst == true)	g1[i][j] = 1;
				if (aifirst == false)	g1[i][j] = -1;
				score[i][j] += assessment(g1) + 0.01*(49 - (i - 7)*(i - 7)) + 0.01*(49 - (j - 7)*(j - 7));
				//	score[i][j] += checkbreak(g1, i, j);
				if (score[i][j] > 1000)		return 0;
				//进行第二步评分
				for (int i_2 = imin; i_2 < imax + 1; i_2++)
				{
					for (int j_2 = jmin; j_2 < jmax + 1; j_2++)
					{
						g_Secondset();
						if (g_Second[i_2][j_2] != 0) {
							score_Second[i_2][j_2] = 0;
							continue;
						}
						else {
							if (aifirst == true)	g_Second[i_2][j_2] = -1;
							if (aifirst == false)	g_Second[i_2][j_2] = 1;
							score_Second[i_2][j_2] = assessment(g_Second);
							leavesNumber++;
							if (score_Second[i_2][j_2] < alpha)
							{
								isbreak = true;
								alpha_Beta_Cut = true;
								break;
							}
						}
					}
					if (isbreak) {
						isbreak = false;
						break;
					}
				}
				//	if (minVecPosition_Score_Second() != 9999)
				if (alpha_Beta_Cut)
				{
					score[i][j] += -600;
					alpha_Beta_Cut = false;
				}

				else
					score[i][j] += minVecPosition_Score_Second();
				if (minVecPosition_Score_Second()>alpha)	alpha = minVecPosition_Score_Second();
			}
		}
	alpha = -9999;
	setfillcolor(LIGHTGRAY);
	fillrectangle(750, 0, 2024, 750);
	return 0;

}

void AI::hardconsider()
{
	initScore();
	int imax = 0, imin = 0, jmax = 0, jmin = 0;
	imax = 0, imin = 15, jmax = 0, jmin = 15;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (game[i][j] != 0)
			{
				if (i >= imax)	imax = i + 3;
				if (i <= imin)	imin = i - 3;
				if (j >= jmax)	jmax = j + 3;
				if (j <= jmin)	jmin = j - 3;

				if (imax > 14)	imax = 14;
				if (imin < 0)	imin = 0;
				if (jmax > 14)	jmax = 14;
				if (jmin < 0)	jmin = 0;
			}
		}
	if (imin == 15) { imax = 7; imin = 7; jmax = 7; jmin = 7; }

	//int imin = 0, jmin = 0, imax = 14, jmax = 14;
	for (int i = imin; i < imax + 1; i++)		//只计算当前最优解
		for (int j = jmin; j < jmax + 1; j++)			//第一层
		{
			numberreset();
			initScore_Second();
			if (g1[i][j] != 0) {
				score[i][j] = 0;
				continue;
			}
			else {
				if (aifirst == true)	g1[i][j] = 1;
				if (aifirst == false)	g1[i][j] = -1;

				score[i][j] = assessment(g1);
				if (score[i][j] > 3000)
				{
					mustset = Vecposition(i, j);

					return;
				}
				else
					score[i][j] = 0.01*(49 - (i - 7)*(i - 7)) + 0.01*(49 - (j - 7)*(j - 7));

				//进行第二步评分
				for (int i_2 = imin; i_2 < imax + 1; i_2++)				//第二层
				{
					for (int j_2 = jmin; j_2 < jmax + 1; j_2++)
					{
						g_Secondset();
						if (g_Second[i_2][j_2] != 0) {
							score_Second[i_2][j_2] = 0;
							continue;
						}
						else {
							if (aifirst == true)	g_Second[i_2][j_2] = -1;
							if (aifirst == false)	g_Second[i_2][j_2] = 1;

							score_Second[i_2][j_2] = assessment(g_Second);
							if (score_Second[i_2][j_2] < -300)
							{
								mustset = Vecposition(i_2, j_2);

								isbreak = true;
								break;
							}
							else
							{
								initscoreSecond_One();
								for (int i_3 = 0; i_3 < 15; i_3++)
								{
									for (int j_3 = 0; j_3 < 15; j_3++)		//第三层
									{
										leavesNumber++;
										gSecond_OneSet();
										if (gSecond_One[i_3][j_3] != 0) {
											gSecond_One[i_3][j_3] = 0;
											continue;
										}
										else
										{
											if (aifirst == true)	gSecond_One[i_3][j_3] = 1;
											if (aifirst == false)	gSecond_One[i_3][j_3] = -1;
											scoreSecond_One[i_3][j_3] = assessment(gSecond_One);
										}
										if (scoreSecond_One[i_3][j_3]>beta)
										{
											isbreak = true;
											break;
										}
									}
									if (isbreak) {
										isbreak = false;
										break;
									}

								}
								score_Second[i_2][j_2] = max_Score_Secend_One();
							}

							if (score_Second[i_2][j_2] <alpha)
							{
								isbreak = true;
								break;
							}
						}

						if (beta > score_Second[i_2][j_2])
							beta = score_Second[i_2][j_2];

					}

					if (isbreak) {
						isbreak = false;
						break;
					}
				}

				score[i][j] += minVecPosition_Score_Second();
				if (score[i][j]>alpha)	alpha = score[i][j];
			}
			beta = 9999;
		}
	alpha = -9999;

	setfillcolor(LIGHTGRAY);
	fillrectangle(750, 0, 2024, 750);

}

void AI::alphaBetaCut(int color, int alpha, int beta, int deep, int g[15][15])
{
	initScore();
	initScore_Second();


	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			for (int i = 0; i < 15; i++)
				for (int j = 0; j < 15; j++)
					g1[i][j] = g[i][j];

			if (g1[i][j] != 0)	continue;
			else
			{
				if (color == 1)
					g1[i][j] = 1;
				else if (color == -1)
					g1[i][j] = -1;

				score[i][j] += checkbreak(g1, i, j);
				if (score[i][j] > 1000)
					return;
				else //开始第二层
				{
					for (int i = 0; i < 15; i++)
					{
						for (int j = 0; j < 15; j++)
						{
							leavesNumber++;
							for (int i = 0; i < 15; i++)
								for (int j = 0; j < 15; j++)
									g_Second[i][j] = g1[i][j];

							if (g_Second[i][j] != 0)	continue;
							else
							{
								if (color == 1)
									g_Second[i][j] = -1;
								else if (color == -1)
									g_Second[i][j] = 1;

								score_Second[i][j] += checkbreak(g_Second, i, j);
								if (score_Second[i][j] > 1000)
								{
									score_Second[i][j] = -score_Second[i][j];
									isbreak = true;
									break;
								}
								else
								{
									score_Second[i][j] = assessment(g_Second) + 0.01*(49 - (i - 7)*(i - 7)) + 0.01*(49 - (j - 7)*(j - 7));
								}

							}
						}

						if (isbreak)
						{
							isbreak = false;
							break;
						}
					}
					score[i][j] = minVecPosition_Score_Second();

				}
			}

		}

}
void AI::numberreset()
{

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			g1[i][j] = game[i][j];
}

void AI::g_Secondset()
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			g_Second[i][j] = g1[i][j];
}

void AI::gSecond_OneSet()
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			gSecond_One[i][j] = g_Second[i][j];
}

void AI::initscoreSecond_One()
{
	for (int i = 0; i < 15; i++)				//初始化score
		for (int j = 0; j < 15; j++)
			scoreSecond_One[i][j] = 0;
}

//以前的评分代码（可参考）

//评价函数
double AI::assessment2(int x[15][15])
	{
		int i, j;
		double score_=0.0;
		int g[15][15];
		for (i = 0; i < 15; i++)
			for (j = 0; j < 15; j++)
				g[i][j] = x[i][j];

		//横排连二检查
		for (i = 1; i < 16; i++)
			for (j = 2; j < 13; j++) {
				if (g[i - 1][j - 1] != 0 &&
					g[i - 1][j] == g[i - 1][j - 1] &&
	
					g[i - 1][j - 2] == 0 &&
					g[i - 1][j + 1] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 1;
					else score_ -= 0.5;
			}
		//横排连三检查
		for (i = 1; i < 16; i++)
			for (j = 2; j < 13; j++) {
				if (g[i - 1][j - 1] != 0 &&
					g[i - 1][j] == g[i - 1][j - 1] &&
					g[i - 1][j + 1] == g[i - 1][j - 1] &&
	
					g[i - 1][j - 2] == 0 &&
					g[i - 1][j + 2] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 10;
					else score_ -= 20;
			}
		//横排连三   堵一检查
		for (i = 1; i < 16; i++)
			for (j = 2; j < 13; j++) {
				if (g[i - 1][j - 1] != 0 &&
					g[i - 1][j] == g[i - 1][j - 1] &&
					g[i - 1][j + 1] == g[i - 1][j - 1] &&
	
					(g[i - 1][j - 2] == 0 ||
					g[i - 1][j + 2] == 0))
					if (g[i - 1][j - 1] == 1)
						score_ += 2;
					else score_ -= 1;
			}
		//横排连四检查
		for (i = 1; i < 16; i++)
			for (j = 2; j < 13; j++) {
				if (g[i - 1][j - 1] != 0 &&
					g[i - 1][j] == g[i - 1][j - 1] &&
					g[i - 1][j + 1] == g[i - 1][j - 1] &&
					g[i - 1][j + 2] == g[i - 1][j - 1] &&
	
					g[i - 1][j - 2] == 0 &&
					g[i - 1][j + 3] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 200;
					else score_ -= 400;
			}
		//横排  一隔二检查
		for (i = 1; i < 16; i++)
			for (j = 2; j < 13; j++) {
				if (g[i - 1][j - 1] != 0 &&
					(g[i - 1][j] == g[i - 1][j - 1] ||
					g[i - 1][j + 1] == g[i - 1][j - 1]) &&
					(g[i - 1][j] == 0 ||
						g[i - 1][j + 1] == 0)&&
					g[i - 1][j + 2] == g[i - 1][j - 1] &&
	
					g[i - 1][j - 2] == 0 &&
					g[i - 1][j + 3] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 10;
					else score_ -= 20;
			}
		//横排连四  堵一检查
		for (i = 1; i < 16; i++)
			for (j = 2; j < 13; j++) {
				if (g[i - 1][j - 1] != 0 &&
					g[i - 1][j] == g[i - 1][j - 1] &&
					g[i - 1][j + 1] == g[i - 1][j - 1] &&
					g[i - 1][j + 2] == g[i - 1][j - 1] &&
	
					(g[i - 1][j - 2] == 0 ||
						g[i - 1][j + 3] == 0))
					if (g[i - 1][j - 1] == 1)
						score_ += 20;
					else score_ -= 300;
			}
		//横排连五检查
		for (i = 1; i < 16; i++)
			for (j = 1; j < 13; j++) {
				if (g[i - 1][j - 1] != 0 && g[i - 1][j + 3] == g[i - 1][j - 1])
				{
					count = 2;
					if (g[i - 1][j] == g[i - 1][j - 1])count++;
					else if (g[i - 1][j] != 0)count = 0;
					if (g[i - 1][j + 1] == g[i - 1][j - 1])count++;
					else if (g[i - 1][j + 1] != 0)count = 0;
					if (g[i - 1][j + 2] == g[i - 1][j - 1])count++;
					else if (g[i - 1][j + 2] != 0)count = 0;
				}
				if (count == 4){
					if (g[i - 1][j - 1] == 1)	score_ += 20;
					else score_ -= 300;
				}
				else if (count == 5){
					if (g[i - 1][j - 1] == 1)	score_ += 700;
					else score_ -= 900;
				}
				count = 0;
			}
		//横排连五检查
		for (i = 1; i < 15; i++)
			for (j = 1; j < 11; j++) {
				if (g[i - 1][j - 1] != 0 &&
					g[i - 1][j] == g[i - 1][j - 1] &&
					g[i - 1][j + 1] == g[i - 1][j - 1] &&
					g[i - 1][j + 2] == g[i - 1][j - 1] &&
					g[i - 1][j + 3] == g[i - 1][j - 1])
					if (g[i - 1][j - 1] == 1)
						score_ += 700;
					else score_ -= 900;
			}
		//竖排连二检查
		for (j = 1; j < 16; j++)
			for (i = 2; i < 13; i++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 1] == g[i - 1][j - 1] &&
	
					g[i - 2][j - 1] == 0 &&
					g[i + 1][j - 1] == 0)
					if (g[i - 1][j - 1] == 1)	score_ += 1;
					else score_ -= 0.5;
				
			}
		//竖排连三检查
		for (j = 1; j < 16; j++)
			for (i = 2; i < 13; i++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 1] == g[i - 1][j - 1] &&
					g[i + 1][j - 1] == g[i - 1][j - 1] &&
	
					g[i - 2][j - 1] == 0 &&
					g[i + 2][j - 1] == 0)
					if (g[i - 1][j - 1] == 1)	score_ += 10;
					else score_ -= 20;
			}
	
		//竖排连三   堵一检查
		for (j = 1; j < 16; j++)
			for (i = 2; i < 13; i++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 1] == g[i - 1][j - 1] &&
					g[i + 1][j - 1] == g[i - 1][j - 1] &&
	
					(g[i - 2][j - 1] == 0 ||
					g[i + 2][j - 1] == 0))
					if (g[i - 1][j - 1] == 1)
						score_ += 2;
					else score_ -= 1;
			}
		//竖排连四检查
		for (j = 1; j < 16; j++)
			for (i = 2; i < 12; i++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 1] == g[i - 1][j - 1] &&
					g[i + 1][j - 1] == g[i - 1][j - 1] &&
					g[i + 2][j - 1] == g[i - 1][j - 1] &&
	
					g[i - 2][j - 1] == 0 &&
					g[i + 3][j - 1] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 200;
					else score_ -= 400;
			}
	
	
		//竖排   一隔二检查
		for (j = 1; j < 16; j++)
			for (i = 2; i < 12; i++)
			{
				if (g[i - 1][j - 1] != 0 &&
					(g[i][j - 1] == g[i - 1][j - 1]||
					g[i + 1][j - 1] == g[i - 1][j - 1]) &&
					(g[i][j - 1] == 0 ||
						g[i + 1][j - 1] ==0) &&
					g[i + 2][j - 1] == g[i - 1][j - 1] &&
	
					g[i - 2][j - 1] == 0 &&
					g[i + 3][j - 1] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 10;
					else score_ -= 20;
			}
		//竖排连四   堵一检查
		for (j = 1; j < 16; j++)
			for (i = 2; i < 12; i++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 1] == g[i - 1][j - 1] &&
					g[i + 1][j - 1] == g[i - 1][j - 1] &&
					g[i + 2][j - 1] == g[i - 1][j - 1] &&
	
					(g[i - 2][j - 1] == 0 ||
						g[i + 3][j - 1] == 0))
					if (g[i - 1][j - 1] == 1)
						score_ += 20;
					else score_ -= 300;
			}
		//竖排连五检查
		for (j = 1; j < 16; j++)
			for (i = 1; i < 12; i++)
			{
				if (g[i - 1][j - 1] != 0 && g[i + 3][j - 1] == g[i - 1][j - 1])
				{
					count = 2;
					if (g[i][j - 1] == g[i - 1][j - 1])	
						count++; 
					else if (g[i][j - 1] != 0)	count = 0;
					if (g[i + 1][j - 1] == g[i - 1][j - 1])
						count++;
					else if (g[i + 1][j - 1] != 0)	count = 0;
					if (g[i + 2][j - 1] == g[i - 1][j - 1])
						count++;
					else if (g[i + 2][j - 1] != 0)	count = 0;
					
				}
				if(count==4)
				{
					if (g[i - 1][j - 1] == 1)
						score_ += 20;
					else score_ -= 300;
				}
				if (count == 5)
				{
					if (g[i - 1][j - 1] == 1)
						score_ += 700;
					else score_ -= 900;
				}
				count = 0;
			}
		//竖排连五检查
		for (j = 1; j < 15; j++)
			for (i = 1; i < 11; i++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 1] == g[i - 1][j - 1] &&
					g[i + 1][j - 1] == g[i - 1][j - 1] &&
					g[i + 2][j - 1] == g[i - 1][j - 1] &&
					g[i + 3][j - 1] == g[i - 1][j - 1])
					if (g[i - 1][j - 1] == 1)
						score_ += 700;
					else score_ -= 900;
			}
	
		//右斜连二检查
		for (i = 2; i < 13; i++)
			for (j = 2; j < 13; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j] == g[i - 1][j - 1] &&
		
					g[i - 2][j - 2] == 0 &&
					g[i + 1][j + 1] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 1;
					else score_ -= 0.5;
	
			}
		//右斜连三检查
		for (i = 2; i < 13; i++)
			for (j = 2; j < 13; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j] == g[i - 1][j - 1] &&
					g[i + 1][j + 1] == g[i - 1][j - 1] &&
	
					g[i - 2][j - 2] == 0 &&
					g[i + 2][j + 2] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 10;
					else score_ -= 20;
			}
		//右斜连三  堵一检查
		for (i = 2; i < 13; i++)
			for (j = 2; j < 13; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j] == g[i - 1][j - 1] &&
					g[i + 1][j + 1] == g[i - 1][j - 1] &&
	
					(g[i - 2][j - 2] == 0 ||
					g[i + 2][j + 2] == 0))
					if (g[i - 1][j - 1] == 1)
						score_ += 2;
					else score_ -= 1;
			}
		//右斜		一隔二检查
		for (i = 2; i < 12; i++)
			for (j = 2; j < 12; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					(g[i][j] == g[i - 1][j - 1] ||
					g[i + 1][j + 1] == g[i - 1][j - 1] )&&
					(g[i][j] == 0 ||
						g[i + 1][j + 1] == 0) &&
					g[i + 2][j + 2] == g[i - 1][j - 1] &&
	
					g[i - 2][j - 2] == 0&&
					g[i + 3][j + 3] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 10;
					else score_ -= 20;
			}
	
	
	
		//右斜连四检查
		for (i = 2; i < 12; i++)
			for (j = 2; j < 12; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j] == g[i - 1][j - 1] &&
					g[i + 1][j + 1] == g[i - 1][j - 1] &&
					g[i + 2][j + 2] == g[i - 1][j - 1] &&
	
					g[i - 2][j - 2] == 0 &&
					g[i + 3][j + 3] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 200;
					else score_ -= 400;
			}
		//右斜连四  堵一检查
		for (i = 2; i < 12; i++)
			for (j = 2; j < 12; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j] == g[i - 1][j - 1] &&
					g[i + 1][j + 1] == g[i - 1][j - 1] &&
					g[i + 2][j + 2] == g[i - 1][j - 1] &&
	
					(g[i - 2][j - 2] == 0 ||
					g[i + 3][j + 3] == 0))
					if (g[i - 1][j - 1] == 1)
						score_ += 20;
					else score_ -= 300;
			}
		
	
		//右斜连五检查
		for (i = 1; i < 12; i++)
			for (j = 1; j < 12; j++)
			{
				if (g[i - 1][j - 1] != 0 && g[i + 3][j + 3] == g[i - 1][j - 1])
				{
					count = 2;
					if (g[i][j] == g[i - 1][j - 1])count++;
					else if (g[i][j] != 0)count = 0;
					if (g[i + 1][j + 1] == g[i - 1][j - 1])count++;
					else if (g[i + 1][j + 1] != 0)count = 0;
					if (g[i + 2][j + 2] == g[i - 1][j - 1])count++;
					else if (g[i + 2][j + 2] != 0)count = 0;
				}
				if (count == 4)
				{
					if (g[i - 1][j - 1] == 1)
						score_ += 20;
					else score_ -= 300;
				}
				if (count == 5)
				{
					if (g[i - 1][j - 1] == 1)
						score_ += 700;
					else score_ -= 900;
				}
				count = 0;
			}
				
				
					
					
	
				//右斜连五检查
		for (i = 1; i < 11; i++)
			for (j = 1; j < 11; j++)
				if (g[i - 1][j - 1] != 0 &&
					g[i][j] == g[i - 1][j - 1] &&
					g[i + 1][j + 1] == g[i - 1][j - 1] &&
					g[i + 2][j + 2] == g[i - 1][j - 1] &&
					g[i + 3][j + 3] == g[i - 1][j - 1])
					if (g[i - 1][j - 1] == 1)
						score_ += 700;
					else score_ -= 900;
	
		//左斜连二检查
		for (i = 2; i < 14; i++)
			for (j = 3; j < 15; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 2] == g[i - 1][j - 1] &&
					
					g[i - 2][j] == 0 &&
					g[i + 1][j - 3] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 1;
					else score_ -= 0.5;
			}
	
		//左斜连三检查
		for (i = 2; i < 13; i++)
			for (j = 4; j < 16; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 2] == g[i - 1][j - 1] &&
					g[i + 1][j - 3] == g[i - 1][j - 1] &&
	
					g[i - 2][j] == 0 &&
					g[i + 2][j - 4] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 10;
					else score_ -= 20;
			}
		  
		//左斜连三   堵一检查
		for (i = 2; i < 13; i++)
			for (j = 4; j < 15; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 2] == g[i - 1][j - 1] &&
					g[i + 1][j - 3] == g[i - 1][j - 1] &&
	
					(g[i - 2][j] == 0 ||
					g[i + 2][j - 4] == 0))
					if (g[i - 1][j - 1] == 1)
						score_ += 2;
					else score_ -= 1;
			}
	
		//左斜一隔二检查
		for (i = 2; i < 12; i++)
			for (j = 5; j < 15; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					(g[i][j - 2] == g[i - 1][j - 1] ||
					g[i + 1][j - 3] == g[i - 1][j - 1]) &&
					(g[i][j - 2] == 0 ||
						g[i + 1][j - 3] == 0) &&
					g[i + 2][j - 4] == g[i - 1][j - 1] &&
	
					g[i - 2][j] == 0 &&
					g[i + 3][j - 5] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 10;
					else score_ -= 20;
			}
	
		//左斜连四检查
		for (i = 2; i < 12; i++)
			for (j = 5; j < 15; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 2] == g[i - 1][j - 1] &&
					g[i + 1][j - 3] == g[i - 1][j - 1] &&
					g[i + 2][j - 4] == g[i - 1][j - 1] &&
	
					g[i - 2][j ] == 0 &&
					g[i + 3][j - 5] == 0)
					if (g[i - 1][j - 1] == 1)
						score_ += 200;
					else score_ -= 400;
			}
	
		//左斜连四    堵一检查
		for (i = 2; i < 12; i++)
			for (j = 5; j < 15; j++)
			{
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 2] == g[i - 1][j - 1] &&
					g[i + 1][j - 3] == g[i - 1][j - 1] &&
					g[i + 2][j - 4] == g[i - 1][j - 1] &&
					(g[i - 2][j] == 0 ||
						g[i + 3][j - 5] == 0))
					if (g[i - 1][j - 1] == 1)
						score_ += 20;
					else score_ -= 300;
				
			}
		//左斜连 五检查   与五空一
	
		for (i = 1; i < 12; i++)
			for (j = 5; j < 16; j++)
			{
				if (g[i - 1][j - 1] != 0 && g[i + 3][j - 5] == g[i - 1][j - 1])
				{
					count = 2;
					if (g[i][j - 2] == g[i - 1][j - 1]) count++;
					else if (g[i][j - 2] != 0)count = 0;
					if (g[i + 1][j - 3] == g[i - 1][j - 1]) count++;
					else if (g[i + 1][j - 3] != 0)count = 0;
					if (g[i + 2][j - 4] == g[i - 1][j - 1])count++;
					else if (g[i + 2][j - 4] != 0)count = 0;
				}
				if (count == 5)
				{
					if (g[i - 1][j - 1] == 1)
						score_ += 700;
					else score_ -= 900;
				}
				else if (count == 4)
				{
					if (g[i - 1][j - 1] == 1)
						score_ += 20;
					else score_ -= 300;
				}
				count = 0;
			}
				
		
		if (g[i - 1][j - 1] != 0 &&
					g[i][j - 2] == g[i - 1][j - 1] &&
					g[i + 1][j - 3] == g[i - 1][j - 1] &&
					g[i + 2][j - 4] == g[i - 1][j - 1] &&
					g[i + 3][j - 5] == g[i - 1][j - 1])
					
					if (g[i - 1][j - 1] == 1)
						score_ += 700;
					else score_ -= 900;
	
	
		//左斜连 五检查
		for (i = 1; i < 11; i++)
			for (j = 5; j < 15; j++)
				if (g[i - 1][j - 1] != 0 &&
					g[i][j - 2] == g[i - 1][j - 1] &&
					g[i + 1][j - 3] == g[i - 1][j - 1] &&
					g[i + 2][j - 4] == g[i - 1][j - 1] &&
					g[i + 3][j - 5] == g[i - 1][j - 1])
					if (g[i - 1][j - 1] == 1)
						score_ += 700;
					else score_ -= 900;
		
		return score_;
	}
//
//double AI::assessment(int x[15][15])
//	{
//		int i, j;
//		double score_ = 0.0;
//		int g[15][15];
//		for (i = 0; i < 15; i++)
//			for (j = 0; j < 15; j++)
//				g[i][j] = x[i][j];
//		//横排连二检查
//		for (i = 1; i < 16; i++)
//			for (j = 2; j < 13; j++) {
//				if (g[i - 1][j - 1] != 0 &&
//					g[i - 1][j] == g[i - 1][j - 1] &&
//	
//					g[i - 1][j - 2] == 0 &&
//					g[i - 1][j + 1] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 12;
//					else score_ -= 12;
//			}
//	
//	
//	
//		//横排连三检查
//		for (i = 1; i < 16; i++)
//			for (j = 2; j < 13; j++) {
//				if (g[i - 1][j - 1] != 0 &&
//					g[i - 1][j] == g[i - 1][j - 1] &&
//					g[i - 1][j + 1] == g[i - 1][j - 1] &&
//	
//					g[i - 1][j - 2] == 0 &&
//					g[i - 1][j + 2] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//			}
//	/*	//横排连三   堵一检查
//		for (i = 1; i < 16; i++)
//			for (j = 2; j < 13; j++) {
//				if (g[i - 1][j - 1] != 0 &&
//					g[i - 1][j] == g[i - 1][j - 1] &&
//					g[i - 1][j + 1] == g[i - 1][j - 1] &&
//	
//					(g[i - 1][j - 2] == 0 ||
//						g[i - 1][j + 2] == 0))
//					if (g[i - 1][j - 1] == 1)
//						score_ += 2;
//					else score_ -= 1;
//			}*/
//	
//		//横排连四检查
//		for (i = 1; i < 16; i++)
//			for (j = 2; j < 13; j++) {
//				if (g[i - 1][j - 1] != 0 &&
//					g[i - 1][j] == g[i - 1][j - 1] &&
//					g[i - 1][j + 1] == g[i - 1][j - 1] &&
//					g[i - 1][j + 2] == g[i - 1][j - 1] &&
//	
//					g[i - 1][j - 2] == 0 &&
//					g[i - 1][j + 3] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 432;
//					else score_ -= 432;
//			}
//		//横排  一隔二检查
//		for (i = 1; i < 16; i++)
//			for (j = 2; j < 13; j++) {
//				if (g[i - 1][j - 1] != 0 &&
//					(g[i - 1][j] == g[i - 1][j - 1] ||
//						g[i - 1][j + 1] == g[i - 1][j - 1]) &&
//					(g[i - 1][j] == 0 ||
//						g[i - 1][j + 1] == 0) &&
//					g[i - 1][j + 2] == g[i - 1][j - 1] &&
//	
//					g[i - 1][j - 2] == 0 &&
//					g[i - 1][j + 3] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 12;
//					else score_ -= 12;
//			}
//		//横排连四  堵一检查
//		for (i = 1; i < 16; i++)
//			for (j = 2; j < 13; j++) {
//				if (g[i - 1][j - 1] != 0 &&
//					g[i - 1][j] == g[i - 1][j - 1] &&
//					g[i - 1][j + 1] == g[i - 1][j - 1] &&
//					g[i - 1][j + 2] == g[i - 1][j - 1] &&
//	
//					(g[i - 1][j - 2] == 0 ||
//						g[i - 1][j + 3] == 0))
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//			}
//		//横排连五检查
//		for (i = 1; i < 16; i++)
//			for (j = 1; j < 13; j++) {
//				if (g[i - 1][j - 1] != 0 && g[i - 1][j + 3] == g[i - 1][j - 1])
//				{
//					count = 2;
//					if (g[i - 1][j] == g[i - 1][j - 1])count++;
//					else if (g[i - 1][j] != 0)count = 0;
//					if (g[i - 1][j + 1] == g[i - 1][j - 1])count++;
//					else if (g[i - 1][j + 1] != 0)count = 0;
//					if (g[i - 1][j + 2] == g[i - 1][j - 1])count++;
//					else if (g[i - 1][j + 2] != 0)count = 0;
//				}
//				if (count == 4) {
//					if (g[i - 1][j - 1] == 1)	score_ += 72;
//					else score_ -= 72;
//				}
//				else if (count == 5) {
//					if (g[i - 1][j - 1] == 1)	score_ += 5000;
//					else score_ -= 5000;
//				}
//				count = 0;
//			}
//	
//		//竖排连二检查
//		for (j = 1; j < 16; j++)
//			for (i = 2; i < 13; i++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 1] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j - 1] == 0 &&
//					g[i + 1][j - 1] == 0)
//					if (g[i - 1][j - 1] == 1)	score_ += 12;
//					else score_ -= 12;
//	
//			}
//		//竖排连三检查
//		for (j = 1; j < 16; j++)
//			for (i = 2; i < 13; i++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 1] == g[i - 1][j - 1] &&
//					g[i + 1][j - 1] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j - 1] == 0 &&
//					g[i + 2][j - 1] == 0)
//					if (g[i - 1][j - 1] == 1)	score_ += 72;
//					else score_ -= 72;
//			}
//	
//	/*	//竖排连三   堵一检查
//		for (j = 1; j < 16; j++)
//			for (i = 2; i < 13; i++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 1] == g[i - 1][j - 1] &&
//					g[i + 1][j - 1] == g[i - 1][j - 1] &&
//	
//					(g[i - 2][j - 1] == 0 ||
//						g[i + 2][j - 1] == 0))
//					if (g[i - 1][j - 1] == 1)
//						score_ += 2;
//					else score_ -= 1;
//			}*/
//	
//	
//		//竖排连四检查
//		for (j = 1; j < 16; j++)
//			for (i = 2; i < 12; i++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 1] == g[i - 1][j - 1] &&
//					g[i + 1][j - 1] == g[i - 1][j - 1] &&
//					g[i + 2][j - 1] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j - 1] == 0 &&
//					g[i + 3][j - 1] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 432;
//					else score_ -= 432;
//			}
//	
//	
//		//竖排   一隔二检查
//		for (j = 1; j < 16; j++)
//			for (i = 2; i < 12; i++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					(g[i][j - 1] == g[i - 1][j - 1] ||
//						g[i + 1][j - 1] == g[i - 1][j - 1]) &&
//					(g[i][j - 1] == 0 ||
//						g[i + 1][j - 1] == 0) &&
//					g[i + 2][j - 1] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j - 1] == 0 &&
//					g[i + 3][j - 1] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//			}
//		//竖排连四   堵一检查
//		for (j = 1; j < 16; j++)
//			for (i = 2; i < 12; i++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 1] == g[i - 1][j - 1] &&
//					g[i + 1][j - 1] == g[i - 1][j - 1] &&
//					g[i + 2][j - 1] == g[i - 1][j - 1] &&
//	
//					(g[i - 2][j - 1] == 0 ||
//						g[i + 3][j - 1] == 0))
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//			}
//		//竖排连五检查
//		for (j = 1; j < 16; j++)
//			for (i = 1; i < 12; i++)
//			{
//				if (g[i - 1][j - 1] != 0 && g[i + 3][j - 1] == g[i - 1][j - 1])
//				{
//					count = 2;
//					if (g[i][j - 1] == g[i - 1][j - 1])
//						count++;
//					else if (g[i][j - 1] != 0)	count = 0;
//					if (g[i + 1][j - 1] == g[i - 1][j - 1])
//						count++;
//					else if (g[i + 1][j - 1] != 0)	count = 0;
//					if (g[i + 2][j - 1] == g[i - 1][j - 1])
//						count++;
//					else if (g[i + 2][j - 1] != 0)	count = 0;
//	
//				}
//				if (count == 4)
//				{
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//				}
//				if (count == 5)
//				{
//					if (g[i - 1][j - 1] == 1)
//						score_ += 5000;
//					else score_ -= 5000;
//				}
//				count = 0;
//			}
//		//竖排连五检查
//	
//		//右斜连二检查
//		for (i = 2; i < 13; i++)
//			for (j = 2; j < 13; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j - 2] == 0 &&
//					g[i + 1][j + 1] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 12;
//					else score_ -= 12;
//	
//			}
//		//右斜连三检查
//		for (i = 2; i < 13; i++)
//			for (j = 2; j < 13; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j] == g[i - 1][j - 1] &&
//					g[i + 1][j + 1] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j - 2] == 0 &&
//					g[i + 2][j + 2] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//			}
//	/*	//右斜连三  堵一检查
//		for (i = 2; i < 13; i++)
//			for (j = 2; j < 13; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j] == g[i - 1][j - 1] &&
//					g[i + 1][j + 1] == g[i - 1][j - 1] &&
//	
//					(g[i - 2][j - 2] == 0 ||
//						g[i + 2][j + 2] == 0))
//					if (g[i - 1][j - 1] == 1)
//						score_ += 2;
//					else score_ -= 1;
//			}*/
//		//右斜		一隔二检查
//		for (i = 2; i < 12; i++)
//			for (j = 2; j < 12; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					(g[i][j] == g[i - 1][j - 1] ||
//						g[i + 1][j + 1] == g[i - 1][j - 1]) &&
//					(g[i][j] == 0 ||
//						g[i + 1][j + 1] == 0) &&
//					g[i + 2][j + 2] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j - 2] == 0 &&
//					g[i + 3][j + 3] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//			}
//	
//	
//	
//		//右斜连四检查
//		for (i = 2; i < 12; i++)
//			for (j = 2; j < 12; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j] == g[i - 1][j - 1] &&
//					g[i + 1][j + 1] == g[i - 1][j - 1] &&
//					g[i + 2][j + 2] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j - 2] == 0 &&
//					g[i + 3][j + 3] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 432;
//					else score_ -= 432;
//			}
//		//右斜连四  堵一检查
//		for (i = 2; i < 12; i++)
//			for (j = 2; j < 12; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j] == g[i - 1][j - 1] &&
//					g[i + 1][j + 1] == g[i - 1][j - 1] &&
//					g[i + 2][j + 2] == g[i - 1][j - 1] &&
//	
//					(g[i - 2][j - 2] == 0 ||
//						g[i + 3][j + 3] == 0))
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//			}
//	
//	
//		//右斜连五检查
//		for (i = 1; i < 12; i++)
//			for (j = 1; j < 12; j++)
//			{
//				if (g[i - 1][j - 1] != 0 && g[i + 3][j + 3] == g[i - 1][j - 1])
//				{
//					count = 2;
//					if (g[i][j] == g[i - 1][j - 1])count++;
//					else if (g[i][j] != 0)count = 0;
//					if (g[i + 1][j + 1] == g[i - 1][j - 1])count++;
//					else if (g[i + 1][j + 1] != 0)count = 0;
//					if (g[i + 2][j + 2] == g[i - 1][j - 1])count++;
//					else if (g[i + 2][j + 2] != 0)count = 0;
//				}
//				if (count == 4)
//				{
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//				}
//				if (count == 5)
//				{
//					if (g[i - 1][j - 1] == 1)
//						score_ += 5000;
//					else score_ -= 5000;
//				}
//				count = 0;
//			}
//	
//		//左斜连二检查
//		for (i = 2; i < 14; i++)
//			for (j = 3; j < 15; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 2] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j] == 0 &&
//					g[i + 1][j - 3] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 12;
//					else score_ -= 12;
//			}
//	
//		//左斜连三检查
//		for (i = 2; i < 13; i++)
//			for (j = 4; j < 16; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 2] == g[i - 1][j - 1] &&
//					g[i + 1][j - 3] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j] == 0 &&
//					g[i + 2][j - 4] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//			}
//	
//	/*	//左斜连三   堵一检查
//		for (i = 2; i < 13; i++)
//			for (j = 4; j < 15; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 2] == g[i - 1][j - 1] &&
//					g[i + 1][j - 3] == g[i - 1][j - 1] &&
//	
//					(g[i - 2][j] == 0 ||
//						g[i + 2][j - 4] == 0))
//					if (g[i - 1][j - 1] == 1)
//						score_ += 2;
//					else score_ -= 1;
//			}
//			*/
//		//左斜一隔二检查
//		for (i = 2; i < 12; i++)
//			for (j = 5; j < 15; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					(g[i][j - 2] == g[i - 1][j - 1] ||
//						g[i + 1][j - 3] == g[i - 1][j - 1]) &&
//					(g[i][j - 2] == 0 ||
//						g[i + 1][j - 3] == 0) &&
//					g[i + 2][j - 4] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j] == 0 &&
//					g[i + 3][j - 5] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//			}
//	
//		//左斜连四检查
//		for (i = 2; i < 12; i++)
//			for (j = 5; j < 15; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 2] == g[i - 1][j - 1] &&
//					g[i + 1][j - 3] == g[i - 1][j - 1] &&
//					g[i + 2][j - 4] == g[i - 1][j - 1] &&
//	
//					g[i - 2][j] == 0 &&
//					g[i + 3][j - 5] == 0)
//					if (g[i - 1][j - 1] == 1)
//						score_ += 432;
//					else score_ -= 432;
//			}
//	
//		//左斜连四    堵一检查
//		for (i = 2; i < 12; i++)
//			for (j = 5; j < 15; j++)
//			{
//				if (g[i - 1][j - 1] != 0 &&
//					g[i][j - 2] == g[i - 1][j - 1] &&
//					g[i + 1][j - 3] == g[i - 1][j - 1] &&
//					g[i + 2][j - 4] == g[i - 1][j - 1] &&
//					(g[i - 2][j] == 0 ||
//						g[i + 3][j - 5] == 0))
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//	
//			}
//		//左斜连 五检查   与五空一
//	
//		for (i = 1; i < 12; i++)
//			for (j = 5; j < 16; j++)
//			{
//				if (g[i - 1][j - 1] != 0 && g[i + 3][j - 5] == g[i - 1][j - 1])
//				{
//					count = 2;
//					if (g[i][j - 2] == g[i - 1][j - 1]) count++;
//					else if (g[i][j - 2] != 0)count = 0;
//					if (g[i + 1][j - 3] == g[i - 1][j - 1]) count++;
//					else if (g[i + 1][j - 3] != 0)count = 0;
//					if (g[i + 2][j - 4] == g[i - 1][j - 1])count++;
//					else if (g[i + 2][j - 4] != 0)count = 0;
//				}
//				if (count == 5)
//				{
//					if (g[i - 1][j - 1] == 1)
//						score_ += 5000;
//					else score_ -= 5000;
//				}
//				else if (count == 4)
//				{
//					if (g[i - 1][j - 1] == 1)
//						score_ += 72;
//					else score_ -= 72;
//				}
//				count = 0;
//			}
//	
//	
//	
//		return score_;
//	}
//

double AI::assessment(int x[15][15])
{
	int count = 0;
	int i, j;
	double score_ = 0.0;
	int g[15][15];
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			g[i][j] = x[i][j];


	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			if (i > 14 || i < 0 || j < 0 || j>14)
				continue;
		
				if ((g[i][j] != 0 || g[i + 1][j] != 0) && i < 11 && i>0 &&				//连三与连四检查
					g[i - 1][j] == 0 && g[i + 4][j] == 0)
				{
					if (g[i][j] != 0)
					{
						count++;
						if (g[i + 1][j] == g[i][j])	count++;
						if (g[i + 2][j] == g[i][j])	count++;
						if (g[i + 3][j] == g[i][j])	count++;

						if ((g[i + 1][j] != g[i][j] && g[i + 1][j] != 0) ||
							(g[i + 2][j] != g[i][j] && g[i + 2][j] != 0) ||
							(g[i + 3][j] != g[i][j] && g[i + 3][j] != 0))
							count = 0;
						if (count == 4) {
							if (g[i][j] == 1)	score_ += 432;
							else			score_ -= 432;
						}
						if (count == 3)
						{
							if (g[i][j] == 1)	score_ += 72;
							else			score_ -= 72;
						}
						if (count == 2)
						{
							if (g[i + 2][j] == g[i][j])
							{
								if (g[i][j] == 1)	score_ += 12;
								else			score_ -= 12;
							}
						}
						count = 0;
					}
					if (g[i][j] == 0)
					{
						if (g[i + 1][j] != 0)
						{
							if (g[i + 2][j] == g[i + 1][j] && g[i + 3][j] == g[i + 1][j])
							{
								if (g[i + 1][j] == 1)	score_ += 72;
								else				score_ -= 72;
							}
							if ((g[i + 2][j] == g[i + 1][j] && g[i + 3][j] == 0) || (g[i + 3][j] == g[i + 1][j] && g[i + 2][j] == 0))
							{
								if (g[i + 1][j] == 1)	score_ += 12;
								else				score_ -= 12;
							}
						}
					
						if (g[i + 3][j] == 0)
						{
							if ((g[i + 1][j] != 0 && g[i + 2][j] == 0) || (g[i + 2][j] != 0 && g[i + 1][j] == 0))
								if (g[i + 1][j] == 1 || g[i + 2][j] == 1)	score_ += 2;
								else				score_ -= 2;
						}
					}

				}

			if ( (g[i][j] != 0 || g[i][j + 1] != 0) && j < 11 && j>0
				&& g[i][j + 4] == 0 && g[i][j - 1] == 0)
			{
				if (g[i][j] != 0)
				{
					count++;
					if (g[i][j + 1] == g[i][j])				count++;
					if (g[i][j + 2] == g[i][j]) 				count++;
					if (g[i][j + 3] == g[i][j])				count++;
					if ((g[i][j + 1] != g[i][j] && g[i][j + 1] != 0) ||
						(g[i][j + 2] != g[i][j] && g[i][j + 2] != 0) ||
						(g[i][j + 3] != g[i][j] && g[i][j + 3] != 0))
						count = 0;

					if (count == 4) {
						if (g[i][j] == 1)	score_ += 432;
						else		score_ -= 432;
					}
					if (count == 3)
					{
						if (g[i][j] == 1)	score_ += 72;
						else			score_ -= 72;
					}
					if (count == 2)
					{
						if (g[i][j + 2] == g[i][j])
							if (g[i][j] == 1)	score_ += 12;
							else			score_ -= 12;
					}
					count = 0;
				}
				else if (g[i][j] == 0)
				{
					if (g[i][j + 1] != 0)
					{
						if (g[i][j + 2] == g[i][j + 1] && g[i][j + 3] == g[i][j + 1])
						{
							if (g[i][j + 1] == 1)	score_ += 72;
							else				score_ -= 72;
						}
						if ((g[i][j + 2] == g[i][j + 1] && g[i][j + 3] == 0) || (g[i][j + 3] == g[i][j + 1] && g[i][j + 2] == 0))
						{
							if (g[i][j + 1] == 1)	score_ += 12;
							else				score_ -= 12;
						}
					}
				
					if (g[i][j + 3] == 0)
					{
						if ((g[i][j + 2] == 0 && g[i][j + 1] != 0) || (g[i][j + 1] == 0 && g[i][j + 2] != 0))
						{
							if (g[i][j + 1] == 1 || g[i][j + 2] == 1)	score_ += 2;
							else				score_ -= 2;
						}
					}

				}
			}


			if ((g[i][j] != 0 || g[i + 1][j + 1] != 0 != 0) && i < 11 && j < 11 && i>0 && j>0 && g[i + 4][j + 4] == 0 && g[i - 1][j - 1] == 0)
			{
				if (g[i][j] != 0)
				{
					count++;
					if (g[i + 1][j + 1] == g[i][j])		count++;
					if (g[i + 2][j + 2] == g[i][j])		count++;
					if (g[i + 3][j + 3] == g[i][j])		count++;
					if ((g[i + 1][j + 1] != g[i][j] && g[i + 1][j + 1] != 0) ||
						(g[i + 2][j + 2] != g[i][j] && g[i + 2][j + 2] != 0) ||
						(g[i + 3][j + 3] != g[i][j] && g[i + 3][j + 3] != 0))
						count = 0;
					if (count == 4) {
						if (g[i][j] == 1)	score_ += 432;
						else		score_ -= 432;
					}
					if (count == 3)
					{
						if (g[i][j] == 1)	score_ += 72;
						else			score_ -= 72;
					}
					if (count == 2)
					{
						if (g[i + 2][j + 2] == g[i][j])
							if (g[i][j] == 1)	score_ += 12;
							else			score_ -= 12;
					}
					count = 0;
				}
				else  if (g[i][j] == 0)
				{
					if (g[i + 1][j + 1] != 0)
					{
						if (g[i + 3][j + 3] == g[i + 1][j + 1] && g[i + 2][j + 2] == g[i + 1][j + 1])
						{
							if (g[i + 1][j + 1] == 1)	score_ += 72;
							else				score_ -= 72;
						}
						if ((g[i + 3][j + 3] == g[i + 1][j + 1] && g[i + 2][j + 2] == 0) ||
							(g[i + 2][j + 2] == g[i + 1][j + 1] && g[i + 3][j + 3] == 0))
						{
							if (g[i + 1][j + 1] == 1)	score_ += 12;
							else			score_ -= 12;
						}
					}

					
					if (g[i + 3][j + 3] == 0)
					{
						if ((g[i + 2][j + 2] == 0 && g[i + 1][j + 1] != 0) || (g[i + 1][j + 1] == 0 && g[i + 2][j + 2] != 0))
							if (g[i + 1][j + 1] == 1 || g[i + 2][j + 2] == 1)	score_ += 2;
							else			score_ -= 2;
					}
				}

			}




			if ((g[i][j] != 0 || g[i - 1][j + 1] != 0) && i > 4 && j < 11 && j>0 && i < 14 && g[i - 4][j + 4] == 0 && g[i + 1][j - 1] == 0)
			{
				if (g[i][j] != 0)
				{
					count++;
					if (g[i - 1][j + 1] == g[i][j])		count++;
					if (g[i - 2][j + 2] == g[i][j])		count++;
					if (g[i - 3][j + 3] == g[i][j])		count++;
					if ((g[i - 1][j + 1] != g[i][j] && g[i - 1][j + 1] != 0) ||
						(g[i - 2][j + 2] != g[i][j] && g[i - 2][j + 2] != 0) ||
						(g[i - 3][j + 3] != g[i][j] && g[i - 3][j + 3] != 0))
						count = 0;
					if (count == 4) {
						if (g[i][j] == 1)	score_ += 432;
						else		score_ -= 432;
					}
					if (count == 3)
					{
						if (g[i][j] == 1)	score_ += 72;
						else			score_ -= 72;
					}
					if (count == 2)
					{
						if (g[i - 2][j + 2] == g[i][j])
							if (g[i][j] == 1)	score_ += 12;
							else			score_ -= 12;
					}
					count = 0;
				}
				else if (g[i][j] == 0)
				{
					if (g[i - 1][j + 1] != 0)
					{
						if (g[i - 2][j + 2] == g[i - 1][j + 1] && g[i - 3][j + 3] == g[i - 1][j + 1])
						{
							if (g[i - 1][j + 1] == 1)	score_ += 72;
							else			score_ -= 72;
						}
						if ((g[i - 2][j + 2] == g[i - 1][j + 1] && g[i - 3][j + 3] == 0) ||
							(g[i - 3][j + 3] == g[i - 1][j + 1] && g[i - 2][j + 2] == 0))
						{
							if (g[i - 1][j + 1] == 1)	score_ += 12;
							else			score_ -= 12;
						}
					}
					
					if (g[i - 3][j + 3] == 0)
					{
						if ((g[i - 2][j + 2] == 0 && g[i - 1][j + 1] != 0) || (g[i - 1][j + 1] == 0 && g[i - 2][j + 2] != 0))
							if (g[i - 1][j + 1] == 1 || g[i - 2][j + 2] == 1)	score_ += 2;
							else			score_ -= 2;
					}
				}

			}


			if (i < 11)			//横五连检查
			{
				if (g[i][j] != 0)
				{
					count++;
					if (g[i + 4][j] == g[i][j])			count++;
					if (g[i + 1][j] == g[i][j])			count++;
					if (g[i + 2][j] == g[i][j])			count++;
					if (g[i + 3][j] == g[i][j])			count++;
					if (count == 5) {
						if (g[i][j] == 1)
							score_ += 5000;
						else
							score_ -= 5000;
					}
					else if (count == 4 && (g[i + 1][j] == 0 || g[i + 2][j] == 0 || g[i + 3][j] == 0 || g[i + 4][j] == 0)) {
						if (g[i][j] == 1)	score_ += 72;
						else		score_ -= 72;
					}
					count = 0;
				}
				else if (g[i][j] == 0 && g[i + 1][j] != 0)
				{
					if (g[i + 4][j] == g[i + 1][j] && g[i + 3][j] == g[i + 1][j] && g[i + 2][j] == g[i + 1][j])
						if (g[i + 1][j] == 1)	score_ += 72;
						else		score_ -= 72;
				}
			}



			if (j < 11)
			{
				if (g[i][j] != 0)
				{
					count++;
					if (g[i][j + 1] == g[i][j])	count++;
					if (g[i][j + 2] == g[i][j])	count++;
					if (g[i][j + 3] == g[i][j])	count++;
					if (g[i][j + 4] == g[i][j])	count++;

					if (count == 5) {
						if (g[i][j] == 1)
							score_ += 5000;
						else
							score_ -= 5000;
					}
					else if (count == 4 && (g[i][j + 1] == 0 || g[i][j + 2] == 0 || g[i][j + 3] == 0 || g[i][j + 4] == 0)) {
						if (g[i][j] == 1)	score_ += 72;
						else		score_ -= 72;
					}
					count = 0;
				}
				else if (g[i][j] == 0 && g[i][j + 1] != 0)
				{
					if (g[i][j + 4] == g[i][j + 1] && g[i][j + 3] == g[i][j + 1] && g[i][j + 2] == g[i][j + 1])
						if (g[i][j + 1] == 1)	score_ += 72;
						else		score_ -= 72;
				}
			}


			if (i < 11 && j < 11)
			{
				if (g[i][j] != 0)
				{
					count++;
					if (g[i + 4][j + 4] == g[i][j])	count++;
					if (g[i + 1][j + 1] == g[i][j])	count++;
					if (g[i + 2][j + 2] == g[i][j])	count++;
					if (g[i + 3][j + 3] == g[i][j])	count++;

					if (count == 5)
					{
						if (g[i][j] == 1)
							score_ += 5000;
						else
							score_ -= 5000;
					}
					else if (count == 4 && (g[i + 3][j + 3] == 0 || g[i + 2][j + 2] == 0 || g[i + 1][j + 1] == 0 || g[i + 4][j + 4] == 0))
					{
						if (g[i][j] == 1)	score_ += 72;
						else		score_ -= 72;
					}
					count = 0;
				}
				else if (g[i][j] == 0 && g[i + 1][j + 1] != 0)
				{
					if (g[i + 2][j + 2] == g[i + 1][j + 1] && g[i + 3][j + 3] == g[i + 1][j + 1] && g[i + 4][j + 4] == g[i + 1][j + 1])
						if (g[i + 1][j + 1] == 1)	score_ += 72;
						else		score_ -= 72;
				}
			}


			if (i > 4 && j < 11)
			{
				if (g[i][j] != 0)
				{
					count++;
					if (g[i - 1][j + 1] == g[i][j])	count++;
					if (g[i - 2][j + 2] == g[i][j])	count++;
					if (g[i - 3][j + 3] == g[i][j])	count++;
					if (g[i - 4][j + 4] == g[i][j])	count++;

					if (count == 5)
					{
						if (g[i][j] == 1)
							score_ += 5000;
						else
							score_ -= 5000;
					}
					else if (count == 4 && (g[i - 1][j + 1] == 0 || g[i - 2][j + 2] == 0 || g[i - 3][j + 3] == 0 || g[i - 4][j + 4] == 0)) {
						if (g[i][j] == 1)	score_ += 72;
						else		score_ -= 72;
					}
					count = 0;
				}
				else if (g[i][j] == 0 && g[i - 1][j + 1] != 0)
				{
					if (g[i - 2][j + 2] == g[i - 1][j + 1] && g[i - 3][j + 3] == g[i - 1][j + 1] && g[i - 4][j + 4] == g[i - 1][j + 1])
					{
						if (g[i - 1][j + 1] == 1)	score_ += 72;
						else		score_ -= 72;
					}
				}
			}

		}



	
/*
	
	//横排连二检查
	for (i = 1; i < 16; i++)
		for (j = 2; j < 13; j++) {
			if (g[i - 1][j - 1] != 0 &&
				g[i - 1][j] == g[i - 1][j - 1] &&

				g[i - 1][j - 2] == 0 &&
				g[i - 1][j + 1] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 12;
				else score_ -= 12;
		}

	//横排连三检查
	for (i = 1; i < 16; i++)
		for (j = 2; j < 13; j++) {
			if (g[i - 1][j - 1] != 0 &&
				g[i - 1][j] == g[i - 1][j - 1] &&
				g[i - 1][j + 1] == g[i - 1][j - 1] &&

				g[i - 1][j - 2] == 0 &&
				g[i - 1][j + 2] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
		}

	//横排连四检查
	for (i = 1; i < 16; i++)
		for (j = 2; j < 13; j++) {
			if (g[i - 1][j - 1] != 0 &&
				g[i - 1][j] == g[i - 1][j - 1] &&
				g[i - 1][j + 1] == g[i - 1][j - 1] &&
				g[i - 1][j + 2] == g[i - 1][j - 1] &&

				g[i - 1][j - 2] == 0 &&
				g[i - 1][j + 3] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 432;
				else score_ -= 432;
		}
	//横排  一隔二检查
	for (i = 1; i < 16; i++)
		for (j = 2; j < 13; j++) {
			if (g[i - 1][j - 1] != 0 &&
				(g[i - 1][j] == g[i - 1][j - 1] ||
					g[i - 1][j + 1] == g[i - 1][j - 1]) &&
				(g[i - 1][j] == 0 ||
					g[i - 1][j + 1] == 0) &&
				g[i - 1][j + 2] == g[i - 1][j - 1] &&

				g[i - 1][j - 2] == 0 &&
				g[i - 1][j + 3] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 12;
				else score_ -= 12;
		}
	//横排连四  堵一检查
	for (i = 1; i < 16; i++)
		for (j = 2; j < 13; j++) {
			if (g[i - 1][j - 1] != 0 &&
				g[i - 1][j] == g[i - 1][j - 1] &&
				g[i - 1][j + 1] == g[i - 1][j - 1] &&
				g[i - 1][j + 2] == g[i - 1][j - 1] &&

				(g[i - 1][j - 2] == 0 ||
					g[i - 1][j + 3] == 0))
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
		}
	//横排连五检查
	for (i = 1; i < 16; i++)
		for (j = 1; j < 13; j++) {
			if (g[i - 1][j - 1] != 0 && g[i - 1][j + 3] == g[i - 1][j - 1])
			{
				count = 2;
				if (g[i - 1][j] == g[i - 1][j - 1])count++;
				else if (g[i - 1][j] != 0)count = 0;
				if (g[i - 1][j + 1] == g[i - 1][j - 1])count++;
				else if (g[i - 1][j + 1] != 0)count = 0;
				if (g[i - 1][j + 2] == g[i - 1][j - 1])count++;
				else if (g[i - 1][j + 2] != 0)count = 0;
			}
			if (count == 4) {
				if (g[i - 1][j - 1] == 1)	score_ += 72;
				else score_ -= 72;
			}
			else if (count == 5) {
				if (g[i - 1][j - 1] == 1)	score_ += 5000;
				else score_ -= 5000;
			}
			count = 0;
		}

	//竖排连二检查
	for (j = 1; j < 16; j++)
		for (i = 2; i < 13; i++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j - 1] == g[i - 1][j - 1] &&

				g[i - 2][j - 1] == 0 &&
				g[i + 1][j - 1] == 0)
				if (g[i - 1][j - 1] == 1)	score_ += 12;
				else score_ -= 12;

		}
	//竖排连三检查
	for (j = 1; j < 16; j++)
		for (i = 2; i < 13; i++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j - 1] == g[i - 1][j - 1] &&
				g[i + 1][j - 1] == g[i - 1][j - 1] &&

				g[i - 2][j - 1] == 0 &&
				g[i + 2][j - 1] == 0)
				if (g[i - 1][j - 1] == 1)	score_ += 72;
				else score_ -= 72;
		}


	//竖排连四检查
	for (j = 1; j < 16; j++)
		for (i = 2; i < 12; i++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j - 1] == g[i - 1][j - 1] &&
				g[i + 1][j - 1] == g[i - 1][j - 1] &&
				g[i + 2][j - 1] == g[i - 1][j - 1] &&

				g[i - 2][j - 1] == 0 &&
				g[i + 3][j - 1] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 432;
				else score_ -= 432;
		}


	//竖排   一隔二检查
	for (j = 1; j < 16; j++)
		for (i = 2; i < 12; i++)
		{
			if (g[i - 1][j - 1] != 0 &&
				(g[i][j - 1] == g[i - 1][j - 1] ||
					g[i + 1][j - 1] == g[i - 1][j - 1]) &&
				(g[i][j - 1] == 0 ||
					g[i + 1][j - 1] == 0) &&
				g[i + 2][j - 1] == g[i - 1][j - 1] &&

				g[i - 2][j - 1] == 0 &&
				g[i + 3][j - 1] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
		}
	//竖排连四   堵一检查
	for (j = 1; j < 16; j++)
		for (i = 2; i < 12; i++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j - 1] == g[i - 1][j - 1] &&
				g[i + 1][j - 1] == g[i - 1][j - 1] &&
				g[i + 2][j - 1] == g[i - 1][j - 1] &&

				(g[i - 2][j - 1] == 0 ||
					g[i + 3][j - 1] == 0))
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
		}
	//竖排连五检查
	for (j = 1; j < 16; j++)
		for (i = 1; i < 12; i++)
		{
			if (g[i - 1][j - 1] != 0 && g[i + 3][j - 1] == g[i - 1][j - 1])
			{
				count = 2;
				if (g[i][j - 1] == g[i - 1][j - 1])
					count++;
				else if (g[i][j - 1] != 0)	count = 0;
				if (g[i + 1][j - 1] == g[i - 1][j - 1])
					count++;
				else if (g[i + 1][j - 1] != 0)	count = 0;
				if (g[i + 2][j - 1] == g[i - 1][j - 1])
					count++;
				else if (g[i + 2][j - 1] != 0)	count = 0;

			}
			if (count == 4)
			{
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
			}
			if (count == 5)
			{
				if (g[i - 1][j - 1] == 1)
					score_ += 5000;
				else score_ -= 5000;
			}
			count = 0;
		}
	//竖排连五检查

	//右斜连二检查
	for (i = 2; i < 13; i++)
		for (j = 2; j < 13; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j] == g[i - 1][j - 1] &&

				g[i - 2][j - 2] == 0 &&
				g[i + 1][j + 1] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 12;
				else score_ -= 12;

		}
	//右斜连三检查
	for (i = 2; i < 13; i++)
		for (j = 2; j < 13; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j] == g[i - 1][j - 1] &&
				g[i + 1][j + 1] == g[i - 1][j - 1] &&

				g[i - 2][j - 2] == 0 &&
				g[i + 2][j + 2] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
		}

	//右斜		一隔二检查
	for (i = 2; i < 12; i++)
		for (j = 2; j < 12; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				(g[i][j] == g[i - 1][j - 1] ||
					g[i + 1][j + 1] == g[i - 1][j - 1]) &&
				(g[i][j] == 0 ||
					g[i + 1][j + 1] == 0) &&
				g[i + 2][j + 2] == g[i - 1][j - 1] &&

				g[i - 2][j - 2] == 0 &&
				g[i + 3][j + 3] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
		}



	//右斜连四检查
	for (i = 2; i < 12; i++)
		for (j = 2; j < 12; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j] == g[i - 1][j - 1] &&
				g[i + 1][j + 1] == g[i - 1][j - 1] &&
				g[i + 2][j + 2] == g[i - 1][j - 1] &&

				g[i - 2][j - 2] == 0 &&
				g[i + 3][j + 3] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 432;
				else score_ -= 432;
		}
	//右斜连四  堵一检查
	for (i = 2; i < 12; i++)
		for (j = 2; j < 12; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j] == g[i - 1][j - 1] &&
				g[i + 1][j + 1] == g[i - 1][j - 1] &&
				g[i + 2][j + 2] == g[i - 1][j - 1] &&

				(g[i - 2][j - 2] == 0 ||
					g[i + 3][j + 3] == 0))
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
		}


	//右斜连五检查
	for (i = 1; i < 12; i++)
		for (j = 1; j < 12; j++)
		{
			if (g[i - 1][j - 1] != 0 && g[i + 3][j + 3] == g[i - 1][j - 1])
			{
				count = 2;
				if (g[i][j] == g[i - 1][j - 1])count++;
				else if (g[i][j] != 0)count = 0;
				if (g[i + 1][j + 1] == g[i - 1][j - 1])count++;
				else if (g[i + 1][j + 1] != 0)count = 0;
				if (g[i + 2][j + 2] == g[i - 1][j - 1])count++;
				else if (g[i + 2][j + 2] != 0)count = 0;
			}
			if (count == 4)
			{
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
			}
			if (count == 5)
			{
				if (g[i - 1][j - 1] == 1)
					score_ += 5000;
				else score_ -= 5000;
			}
			count = 0;
		}

	//左斜连二检查
	for (i = 2; i < 14; i++)
		for (j = 3; j < 15; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j - 2] == g[i - 1][j - 1] &&

				g[i - 2][j] == 0 &&
				g[i + 1][j - 3] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 12;
				else score_ -= 12;
		}

	//左斜连三检查
	for (i = 2; i < 13; i++)
		for (j = 4; j < 16; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j - 2] == g[i - 1][j - 1] &&
				g[i + 1][j - 3] == g[i - 1][j - 1] &&

				g[i - 2][j] == 0 &&
				g[i + 2][j - 4] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
		}

	//左斜一隔二检查
	for (i = 2; i < 12; i++)
		for (j = 5; j < 15; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				(g[i][j - 2] == g[i - 1][j - 1] ||
					g[i + 1][j - 3] == g[i - 1][j - 1]) &&
				(g[i][j - 2] == 0 ||
					g[i + 1][j - 3] == 0) &&
				g[i + 2][j - 4] == g[i - 1][j - 1] &&

				g[i - 2][j] == 0 &&
				g[i + 3][j - 5] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
		}

	//左斜连四检查
	for (i = 2; i < 12; i++)
		for (j = 5; j < 15; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j - 2] == g[i - 1][j - 1] &&
				g[i + 1][j - 3] == g[i - 1][j - 1] &&
				g[i + 2][j - 4] == g[i - 1][j - 1] &&

				g[i - 2][j] == 0 &&
				g[i + 3][j - 5] == 0)
				if (g[i - 1][j - 1] == 1)
					score_ += 432;
				else score_ -= 432;
		}

	//左斜连四    堵一检查
	for (i = 2; i < 12; i++)
		for (j = 5; j < 15; j++)
		{
			if (g[i - 1][j - 1] != 0 &&
				g[i][j - 2] == g[i - 1][j - 1] &&
				g[i + 1][j - 3] == g[i - 1][j - 1] &&
				g[i + 2][j - 4] == g[i - 1][j - 1] &&
				(g[i - 2][j] == 0 ||
					g[i + 3][j - 5] == 0))
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;

		}
	//左斜连 五检查   与五空一

	for (i = 1; i < 12; i++)
		for (j = 5; j < 16; j++)
		{
			if (g[i - 1][j - 1] != 0 && g[i + 3][j - 5] == g[i - 1][j - 1])
			{
				count = 2;
				if (g[i][j - 2] == g[i - 1][j - 1]) count++;
				else if (g[i][j - 2] != 0)count = 0;
				if (g[i + 1][j - 3] == g[i - 1][j - 1]) count++;
				else if (g[i + 1][j - 3] != 0)count = 0;
				if (g[i + 2][j - 4] == g[i - 1][j - 1])count++;
				else if (g[i + 2][j - 4] != 0)count = 0;
			}
			if (count == 5)
			{
				if (g[i - 1][j - 1] == 1)
					score_ += 5000;
				else score_ -= 5000;
			}
			else if (count == 4)
			{
				if (g[i - 1][j - 1] == 1)
					score_ += 72;
				else score_ -= 72;
			}
			count = 0;
		}

		*/
if (aifirst == false)	score_ = -score_;
	return score_;
}

void AI::findcompmove(int board[15][15], Vecposition &best, double &score,int layer, int alpha, int beta)
{
	if (layer == 3)
		score = assessment2(board);
	else
	{
		layer++;
		Vecposition dc;
		double response;
		score = alpha;
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				if (board[i][j] == 0 && score < beta)
				{
					board[i][j] = 1;
					findhumanmove(board, dc,response, layer, score, beta);
					board[i][j] = 0;
					if (response > score)
					{
						best = Vecposition(i * 50, 50 * j);
						score = response;
					}
				}
	}
}
void AI::findhumanmove(int board[15][15], Vecposition &best, double &score, int layer_, int alpha, int beta)
{
	if (layer_ == 3)
		score = assessment2(board);
	else
	{
		layer_++;
		double response;
		Vecposition dc;
		score = beta;
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				if (board[i][j] == 0 && score > alpha)
				{
					board[i][j] = -1;
					findcompmove(board, dc, response, layer_, alpha, score);
					board[i][j] = 0;
					if (response < score)
					{
						best = Vecposition(i * 50, 50 * j);
						score = response;
					}
				}
	}
}