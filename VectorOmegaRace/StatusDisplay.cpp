#include "StatusDisplay.h"

void StatusDisplay::Draw(void)
{
	int size = 8;

	pLetter->ProcessString(&m_ScoreText[0], &m_HiScoreTextLocation, &size);
	pNumber->ProcessNumber(&m_HighScore, &m_HiScoreLocation, &size);
	pLetter->ProcessString(&m_ScoreText[1], &m_ScoreTextLocation, &size);
	pNumber->ProcessNumber(&m_Score, &m_ScoreLocation, &size);

	DrawShips();
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
	pLetter->InitializeLetterLine();
}

StatusDisplay::StatusDisplay()
{
	m_Score = 0;
	m_Ships = 0;
	m_HighScore = 0;
	m_GameOver = true;
	m_ShipRotation = Pi * 1.5f;
	m_ShipLocation = Vector2f(Window::GetWindowSize().x * 0.20, Window::GetWindowSize().y * 0.40);

	m_ScoreText[0] = "HIGH SCORE";
	m_ScoreText[1] = "PLAYER SCORE";
	m_HiScoreLocation = Vector2i(Window::GetWindowSize().x * 0.8f, Window::GetWindowSize().y * 0.5f + 40);
	m_ScoreLocation = m_HiScoreLocation - Vector2i(0, 60);
	m_ScoreTextLocation = m_ScoreLocation - Vector2i(145, 30);
	m_HiScoreTextLocation = m_HiScoreLocation - Vector2i(120, 30);

	pNumber = new Number();
	pLetter = new Letter();
	pShip = new PlayerShip();

	//Player Ship Color
	m_ShipColor.Red = 120;
	m_ShipColor.Green = 40;
	m_ShipColor.Blue = 255;
	m_ShipColor.Alpha = 255;

	pLetter->SetColor(&m_ShipColor);
}

StatusDisplay::~StatusDisplay()
{
	delete pNumber;
	delete pLetter;
	delete pShip;
}
// ----------- Private methods -------
void StatusDisplay::DrawShips(void)
{
	for (int ship = 0; ship < m_Ships; ship++)
	{
		float scale = 1.8;
		Vector2f location = m_ShipLocation + Vector2f(ship * 20, 0);
		pShip->Update(&m_ShipRotation, &location, &scale);
		pShip->Draw(&m_ShipColor);
	}
}