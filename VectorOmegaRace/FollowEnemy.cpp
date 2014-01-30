#include "FollowEnemy.h"

void FollowEnemy::Update(double *Frame)
{
	if (m_Active)
	{
		Enemy::Update(Frame);
		pTriShip->Update(&m_Location, &m_Scale);
		
		TimeToLayMine();
	}
}

void FollowEnemy::Draw(void)
{
	if (m_Active)
	{
		Enemy::Draw();
		pTriShip->Draw();
	}

	for (int mine = 0; mine < m_Mines.size(); mine++)
	{
		m_Mines[mine]->Draw();
	}
}

void FollowEnemy::NewGame(void)
{
	m_Mines.clear();
	m_Active = false;
}

Vector2f FollowEnemy::GetMineLocaiton(int *mine)
{
	return m_Mines[*mine]->GetLocation();
}

float FollowEnemy::GetMineRadius(void)
{
	return m_Mines[0]->GetRadius();
}

int FollowEnemy::GetMineCount(void)
{
	return m_Mines.size();
}

bool FollowEnemy::GetMineActive(int *mine)
{
	return m_Mines[*mine]->GetActive();
}

void FollowEnemy::MineHit(int *mine)
{
	m_Mines[*mine]->SetActive(&False);
}

void FollowEnemy::TimerPause(void)
{
	pTimer->Pause();
}

void FollowEnemy::TimerUnpause(void)
{
	pTimer->Unpause();
}

FollowEnemy::FollowEnemy()
{
	Enemy::Initialize();
	m_MineTimerAmount = 5.5;
	pTriShip = new TriShip();
	pTimer = new Timer();
	pTimer->Start();
	ResetTimer();
}

FollowEnemy::~FollowEnemy()
{
	pTimer = nullptr;
	pTriShip = nullptr;

	delete pTimer;
	delete pTriShip;
}

void FollowEnemy::SpawnMine(void)
{
	float scale = 3.5;
	m_Mines.push_back(new Mine());
	int mine = m_Mines.size() - 1;
	m_Mines[mine]->SetLocation(&m_Location);
	m_Mines[mine]->SetScale(&scale);
	m_Mines[mine]->MineDropped();
}

void FollowEnemy::TimeToLayMine(void)
{
	if (m_MineTimer < pTimer->Seconds())
	{
		ResetTimer();
		SpawnMine();
	}
}

void FollowEnemy::ResetTimer(void)
{
	m_MineTimer = m_MineTimerAmount + Window::Random(0, m_MineTimerAmount) + pTimer->Seconds();
}
