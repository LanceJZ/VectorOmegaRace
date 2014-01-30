#include "LeadEnemy.h"

void LeadEnemy::Update(double *Frame)
{
	if (m_Active)
	{
		pTriShip->Update(&m_Location, &m_Scale);
		CheckToFire();
	}

	Enemy::Update(Frame);
	pShot->Update(Frame);
}

void LeadEnemy::Draw(void)
{
	if (m_Active)
	{
		pTriShip->Draw();
	}

	Enemy::Draw();
	pShot->Draw();
}

void LeadEnemy::SetPlayerLocation(Vector2f *location)
{
	m_PlayerLocation = *location;
}

void LeadEnemy::SetInsideBorderOnShot(SDL_Rect *border)
{
	pShot->SetInsideBorder(border);
}

Vector2f LeadEnemy::GetShotLocation(void)
{
	return pShot->GetLocation();
}

float LeadEnemy::GetShotRadius(void)
{
	return pShot->GetRadius();
}

bool LeadEnemy::GetShotActive(void)
{
	return pShot->GetActive();
}

void LeadEnemy::ShotHitTarget(void)
{
	pShot->SetActive(&False);
}

void LeadEnemy::TimerPause(void)
{
	pTimer->Pause();
}

void LeadEnemy::TimerUnpause(void)
{
	pTimer->Unpause();
}

LeadEnemy::LeadEnemy()
{
	m_FireTimerAmount = 2.8;
	pTriShip = new TriShip();
	pShot = new Shot();
	pTimer = new Timer();
	pTimer->Start();
	ResetShotTimer();
	Enemy::Initialize();
}

LeadEnemy::~LeadEnemy()
{
	pTimer = nullptr;
	pShot = nullptr;
	pTriShip = nullptr;

	delete pTimer;
	delete pShot;
	delete pTriShip;
}

void LeadEnemy::FireShot(void)
{
	float angle = atan2(m_PlayerLocation.y - m_Location.y, m_PlayerLocation.x - m_Location.x);
	pShot->Activate(&m_Location, &angle);
	ResetShotTimer();
}

void LeadEnemy::CheckToFire(void)
{
	if (m_FireTimer < pTimer->Seconds())
		FireShot();
}

void LeadEnemy::ResetShotTimer(void)
{
	m_FireTimer = m_FireTimerAmount + pTimer->Seconds() + Window::Random(0, (int)(m_FireTimerAmount * 10) * 0.1);
}
