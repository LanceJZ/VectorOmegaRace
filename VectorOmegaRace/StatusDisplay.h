#ifndef STATUSDISPLAY_H
#define STATUSDISPLAY_H
#include "Common.h"
#include "Number.h"
#include "Letter.h"

class StatusDisplay : Common
{
private:
	bool m_GameOver;
	int m_Score;
	int m_HighScore;
	int m_Ships;

	Number *pNumber = nullptr;

public:
	StatusDisplay();
	~StatusDisplay();

	void Initilize(void);
	void Draw(void);
	void Update(void);
	void SetScore(int *score);
	void SetShip(int *ship);
	void SetGameOver(bool *gameOver);
	void NewGame(void);
};

#endif