#ifndef STATUSDISPLAY_H
#define STATUSDISPLAY_H
#include "Common.h"
#include "Number.h"
#include "Letter.h"
#include "PlayerShip.h"

class StatusDisplay : Common
{
private:
	bool m_GameOver;
	int m_Score;
	int m_HighScore;
	int m_Ships;
	float m_ShipRotation;
	std::string m_ScoreText[2];
	Color m_ShipColor;
	Vector2f m_ShipLocation;
	Vector2i m_ScoreLocation;
	Vector2i m_HiScoreLocation;
	Vector2i m_ScoreTextLocation;
	Vector2i m_HiScoreTextLocation;

	Number *pNumber = nullptr;
	Letter *pLetter = nullptr;
	PlayerShip *pShip = nullptr;

	void DrawShips(void);

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