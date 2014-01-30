#include "StatusDisplay.h"

void StatusDisplay::Draw(void)
{
	Vector2i scoreLocation = Vector2i(Window::GetWindowSize().x * 0.8f, Window::GetWindowSize().y * 0.5f + 40);
	Vector2i hiScoreLocation = scoreLocation - Vector2i(0, 30);
	int size = 8;

	pNumber->ProcessNumber(&m_Score, &scoreLocation, &size);
	pNumber->ProcessNumber(&m_HighScore, &hiScoreLocation, &size);
}

void StatusDisplay::Update(void)
{

}

void StatusDisplay::SetScore(int *score)
{
	m_Score = *score;
}

void StatusDisplay::SetShip(int *ship)
{
	m_Ships = *ship;
}

void StatusDisplay::SetGameOver(bool *gameOver)
{
	m_GameOver = *gameOver;
}

StatusDisplay::StatusDisplay()
{
	m_Score = 0;
	m_Ships = 0;
	m_HighScore = 0;
	m_GameOver = true;

	pNumber = new Number();
}

StatusDisplay::~StatusDisplay()
{
}

void StatusDisplay::NewGame(void)
{
	if (m_Score > m_HighScore)
		m_HighScore = m_Score;

	m_Score = 0;
	m_Ships = 0;
	m_GameOver = false;
}

void StatusDisplay::Initilize(void)
{
	pNumber->InitializeNumberLine();
}
