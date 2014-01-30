#include "EnemyController.h"

void EnemyController::Update(double *Frame)
{
	m_Frame = *Frame;

	for (int ship = 0; ship < m_EnemyShips.size(); ship++)
	{
		m_EnemyShips[ship]->Update(Frame);
	}

	pLeadEnemyShip->Update(Frame);
	pFollowEnemyShip->Update(Frame);
	pFighter->Update(Frame);

	CheckFighterTimer();
}

void EnemyController::Draw(void)
{
	for (int ship = 0; ship < m_EnemyShips.size(); ship++)
	{
		m_EnemyShips[ship]->Draw();
	}

	pLeadEnemyShip->Draw();
	pFollowEnemyShip->Draw();
	pFighter->Draw();
}

int EnemyController::NewGame(void)
{
	m_FollowActive = false;
	m_EnemyShips.clear();
	m_NumberOfShips = 5;
	m_EnemySpeed = 10;
	pFollowEnemyShip->NewGame();
	pFighter->NewGame();
	m_FighterTimerAmount = 20.5;
	ResetFighterTimer();

	return m_NumberOfShips;
}

int EnemyController::NewWave(void)
{
	m_FollowActive = true;
	m_NumberOfShips += 1;
	m_EnemySpeed += 8.5;
	pFollowEnemyShip->SetActive(&True);
	pLeadEnemyShip->SetActive(&True);
	pLeadEnemyShip->ShotHitTarget();
	pFighter->ShotHitTarget();

	if (m_FighterTimerAmount > 6)
	{
		m_FighterTimerAmount -= 3.5;
	}

	ResetFighterTimer();

	return m_NumberOfShips;
}

bool EnemyController::CheckEndOfWave(void)
{
	for (int ship = 0; ship < m_EnemyShips.size(); ship++)
	{
		if (m_EnemyShips[ship]->GetActive())
			return false;
	}

	if (pFollowEnemyShip->GetActive())
		return false;

	if (pFighter->GetActive())
		return false;

	if (pLeadEnemyShip->GetActive())
		return false;

	return true;
}

int EnemyController::RestartWave(void)
{
	int activeCount = 0;

	for (int ship = 0; ship < m_EnemyShips.size(); ship++)
	{
		if (m_EnemyShips[ship]->GetActive())
		{
			activeCount++;
			m_EnemyShips[ship]->SetActive(&False);
		}
	}

	if (pFighter->GetActive())
	{
		if (pLeadEnemyShip->GetActive())
			activeCount++;
	}

	if (pFollowEnemyShip->GetActive())
	{
		activeCount++;
	}

	if (m_FollowActive && activeCount > 0)
	{
		pFollowEnemyShip->SetActive(&True);
	}

	pFighter->SetActive(&False);
	pLeadEnemyShip->ShotHitTarget();
	pFighter->ShotHitTarget();

	return activeCount;
}

void EnemyController::ResumeWave(void)
{

}

void EnemyController::SpawnNewWave(bool *rightSide, int *numberOfShips)
{
	m_RightSide = *rightSide;

	for (int ship = 0; ship < *numberOfShips; ship++)
	{
		bool spawnNewShip = true;

		for (int shipCheck = 0; shipCheck < m_EnemyShips.size(); shipCheck++)
		{
			if (!m_EnemyShips[shipCheck]->GetActive())
			{
				spawnNewShip = false;
				SpawnShip(shipCheck);
				break;
			}
		}

		if (spawnNewShip)
		{
			m_EnemyShips.push_back(new Enemy());
			m_EnemyShips[m_EnemyShips.size() - 1]->Initialize();
			SpawnShip(m_EnemyShips.size() - 1);
		}
	}

	Vector2i spawnPoint;

	spawnPoint.y = Window::Random(Window::GetWindowSize().y * 0.5f + int(Window::GetWindowSize().y * 0.125f) + 25,
		Window::GetWindowSize().y - 25);

	if (m_RightSide)
		spawnPoint.x = Window::GetWindowSize().x - 55;
	else
		spawnPoint.x = 55;

	pLeadEnemyShip->SetLocation(&spawnPoint);
	pLeadEnemyShip->Update(&m_Frame);
	float speed = m_EnemySpeed * 1.5;
	pLeadEnemyShip->SetSpeed(&speed);
	pLeadEnemyShip->SetRightSide(&m_RightSide);
	pLeadEnemyShip->StartMoving();
	pLeadEnemyShip->SetTurns();
	pLeadEnemyShip->SetActive(&True);

	if (pFollowEnemyShip->GetActive() && numberOfShips > 0)
	{
		PlaceFollowEnemy(0);
	}

	Update(&m_Frame);
}

EnemyController::EnemyController(void)
{
	pTimer = new Timer();
	pTimer->Start();
	pLeadEnemyShip = new LeadEnemy();
	pFollowEnemyShip = new FollowEnemy();
	pFighter = new Fighter();
	pFollowEnemyShip->SetActive(&False);
}

EnemyController::~EnemyController(void)
{
	m_EnemyShips.clear();

	pLeadEnemyShip = nullptr;
	pFollowEnemyShip = nullptr;
	pFighter = nullptr;
	pTimer = nullptr;

	delete pLeadEnemyShip;
	delete pFollowEnemyShip;
	delete pFighter;
	delete pTimer;
}

void EnemyController::SpawnShip(int ship)
{
	Vector2i spawnPoint;

	spawnPoint.y = Window::Random(Window::GetWindowSize().y * 0.5f + int(Window::GetWindowSize().y * 0.125f) + 25,
		Window::GetWindowSize().y - 25);

	if (m_RightSide)
	{
		spawnPoint.x = Window::Random(Window::GetWindowSize().x * 0.5f, Window::GetWindowSize().x - 105);
	}
	else
	{
		spawnPoint.x = Window::Random(105, Window::GetWindowSize().x / 2);
	}
	
	m_EnemyShips[ship]->SetLocation(&spawnPoint);
	m_EnemyShips[ship]->Update(&m_Frame);
	m_EnemyShips[ship]->SetSpeed(&m_EnemySpeed);
	m_EnemyShips[ship]->SetRightSide(&m_RightSide);
	m_EnemyShips[ship]->StartMoving();
	m_EnemyShips[ship]->SetTurns();
	m_EnemyShips[ship]->SetActive(&True);
}

float EnemyController::GetEnemyRadius(void)
{
	return m_EnemyShips[0]->GetRadius();
}

int EnemyController::GetEnemyCount(void)
{
	return m_EnemyShips.size();
}

Vector2f EnemyController::GetEnemyLocaiton(int *ship)
{
	return m_EnemyShips[*ship]->GetLocation();
}

bool EnemyController::GetEnemyCircle(Vector2f *location, float *radius, int *ship)
{
	return m_EnemyShips[*ship]->CirclesIntersect(location, radius);
}

void EnemyController::EnemyHit(int *ship)
{
	m_EnemyShips[*ship]->Explode();
	m_EnemyShips[*ship]->SetActive(&False);
}

bool EnemyController::GetEnemyActive(int *ship)
{
	return m_EnemyShips[*ship]->GetActive();
}

void EnemyController::SetInisdeBorder(SDL_Rect *border)
{
	pLeadEnemyShip->SetInsideBorderOnShot(border);
	pFighter->SetInsideBorder(border);
}

void EnemyController::LeadEnemyHit(void)
{
	pLeadEnemyShip->Explode();

	if (EnemyLeft())
	{
		int ship = FindEnemy();
		pLeadEnemyShip->SetLocation(&m_EnemyShips[ship]->GetLocation());
		Vector2f newVelocity = m_EnemyShips[ship]->GetVelocity() * 1.5;
		pLeadEnemyShip->SetVelocity(&newVelocity);
		pLeadEnemyShip->SetTurns(&m_EnemyShips[ship]->GetTurns());
		m_EnemyShips[ship]->SetActive(&False);
	}
	else if (pFollowEnemyShip->GetActive())
	{
		pLeadEnemyShip->SetLocation(&pFollowEnemyShip->GetLocation());
		Vector2f newVelocity = pFollowEnemyShip->GetVelocity() * 1.5;
		pLeadEnemyShip->SetVelocity(&newVelocity);
		pLeadEnemyShip->SetTurns(&pFollowEnemyShip->GetTurns());
		pFollowEnemyShip->SetActive(&False);
	}
	else
	{
		pLeadEnemyShip->SetActive(&False);
	}
}

void EnemyController::FollowEnemyHit(void)
{
	pFollowEnemyShip->Explode();

	if (EnemyLeft())
	{
		PlaceFollowEnemy(FindEnemy());
	}
	else
	{
		pFollowEnemyShip->SetActive(&False);
	}
}

void EnemyController::PlaceFollowEnemy(int ship)
{
	pFollowEnemyShip->SetLocation(&m_EnemyShips[ship]->GetLocation());
	pFollowEnemyShip->SetVelocity(&m_EnemyShips[ship]->GetVelocity());
	pFollowEnemyShip->SetRotation(&m_EnemyShips[ship]->GetRotation());
	pFollowEnemyShip->SetSpeed(&m_EnemySpeed);
	pFollowEnemyShip->SetRightSide(&m_RightSide);
	pFollowEnemyShip->SetTurns(&m_EnemyShips[ship]->GetTurns());
	m_EnemyShips[ship]->SetActive(&False);
}

void EnemyController::CheckFighterTimer(void)
{
	if (m_FighterTimer < pTimer->Seconds())
	{
		if (!pFighter->GetActive())
		{
			LaunchFighter();
			ResetFighterTimer();
		}
	}
}

void EnemyController::ResetFighterTimer(void)
{
	m_FighterTimer = m_FighterTimerAmount + Window::Random(0, m_FighterTimerAmount) + pTimer->Seconds();
}

void EnemyController::LaunchFighter(void)
{
	if (EnemyLeft())
	{
		int ship = FindEnemy();
		pFighter->Start(&m_EnemyShips[ship]->GetLocation(), &m_EnemyShips[ship]->GetVelocity());
		m_EnemyShips[ship]->SetActive(&False);
	}
	else if (pFollowEnemyShip->GetActive())
	{
		pFighter->Start(&pFollowEnemyShip->GetLocation(), &pFollowEnemyShip->GetVelocity());
		pFollowEnemyShip->SetActive(&False);
	}
	else if (pLeadEnemyShip->GetActive())
	{
		pFighter->Start(&pLeadEnemyShip->GetLocation(), &pLeadEnemyShip->GetVelocity());
		pLeadEnemyShip->SetActive(&False);
	}
}

bool EnemyController::EnemyLeft(void)
{
	for (int ship = 0; ship < m_EnemyShips.size(); ship++)
	{
		if (m_EnemyShips[ship]->GetActive())
		{
			return true;
		}
	}

	return false;
}

int EnemyController::FindEnemy(void)
{
	bool shipActive = false;
	int ship;

	while (!shipActive)
	{
		ship = Window::Random(0, m_EnemyShips.size() - 1);
		shipActive = m_EnemyShips[ship]->GetActive();
	}

	return ship;
}

Fighter * EnemyController::GetFighterPointer(void)
{
	return pFighter;
}

FollowEnemy * EnemyController::GetFollowPointer(void)
{
	return pFollowEnemyShip;
}

LeadEnemy * EnemyController::GetLeadPointer(void)
{
	return pLeadEnemyShip;
}

void EnemyController::TimerPause(void)
{
	pTimer->Pause();
	pFighter->TimerPause();
	pFollowEnemyShip->TimerPause();
	pLeadEnemyShip->TimerPause();
}

void EnemyController::TimerUnpause(void)
{
	pTimer->Unpause();
	pFighter->TimerUnpause();
	pFollowEnemyShip->TimerUnpause();
	pLeadEnemyShip->TimerUnpause();
}

bool EnemyController::CheckExploding(void)
{
	bool explodeing = false;

	if (pLeadEnemyShip->GetExplosionActive())
		explodeing = true;

	if (pFighter->GetExplosionActive())
		explodeing = true;

	return explodeing;
}
