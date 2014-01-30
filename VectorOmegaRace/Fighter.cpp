#include "Fighter.h"

void Fighter::Update(double *Frame)
{
	if (m_Active)
	{
		m_Frame = *Frame;
		UpdateFrame(Frame);
		pShip->Update(&m_Location, &m_Scale);
		pBlade->Update(&m_Location, &m_Rotation.Amount);
		TimerCheck();
		CheckBorders();
	}

	pShot->Update(Frame);
	pExplosion->Update(Frame);
}

void Fighter::Draw(void)
{
	if (m_Active)
	{
		pShip->Draw();
		pBlade->Draw();
	}

	pShot->Draw();
	pExplosion->Draw();

	for (int mine = 0; mine < m_Mines.size(); mine++)
		m_Mines[mine]->Draw();
}

void Fighter::SetPlayerLocation(Vector2f *location)
{
	m_PlayerLocation = *location;
}

void Fighter::SetInsideBorder(SDL_Rect *border)
{
	m_InsideBorder = *border;
	pShot->SetInsideBorder(border);
}

bool Fighter::GetInsideLineHit(int *line)
{
	return m_InsideLineHit[*line];
}

bool Fighter::GetOutsideLineHit(int *line)
{
	return m_OutsideLineHit[*line];
}

Vector2f Fighter::GetMineLocaiton(int *mine)
{
	return m_Mines[*mine]->GetLocation();
}

float Fighter::GetMineRadius(void)
{
	return m_Mines[0]->GetRadius();
}

int Fighter::GetMineCount(void)
{
	return m_Mines.size();
}

bool Fighter::GetMineActive(int *mine)
{
	return m_Mines[*mine]->GetActive();
}

void Fighter::MineHit(int *mine)
{
	m_Mines[*mine]->SetActive(&False);
}

Vector2f Fighter::GetShotLocation(void)
{
	return pShot->GetLocation();
}

float Fighter::GetShotRadius(void)
{
	return pShot->GetRadius();
}

bool Fighter::GetShotActive(void)
{
	return pShot->GetActive();
}

void Fighter::ShotHitTarget(void)
{
	pShot->SetActive(&False);
}

void Fighter::Start(Vector2f *location, Vector2f *velocity)
{
	m_Location = *location;
	m_Velocity = *velocity;
	m_Active = true;
	m_Rotation.Velocity = 9.15;
	m_Speed = 105;

	for (int line = 0; line < 4; line++)
		m_InsideLineHit[line] = false;

	for (int line = 0; line < 8; line++)
		m_OutsideLineHit[line] = false;

	ResetMineTimer();
	ResetShotTimer();
	ResetChangeVectorTimer();
	Update(&m_Frame);
}

void Fighter::NewGame(void)
{
	m_Mines.clear();
	m_Active = false;
}

void Fighter::TimerPause(void)
{
	pTimer->Pause();
}

void Fighter::TimerUnpause(void)
{
	pTimer->Unpause();
}

void Fighter::Explode(void)
{
	m_Active = false;
	pExplosion->Activate(m_Location, 2);
}

bool Fighter::GetExplosionActive(void)
{
	return pExplosion->GetActive();
}

Fighter::Fighter()
{
	pShip = new TriShip();
	pShot = new Shot();
	pBlade = new FighterShip();
	pExplosion = new Explosion();
	pTimer = new Timer();
	pTimer->Start();
	m_ShotTimerAmount = 3.2;
	m_MineTimerAmount = 5.1;
	m_ChangeVectorTimerAmount = 2.4;
	m_Scale = 3.5;
	m_Radius = 5;
	m_Rectangle.h = 10;
	m_Rectangle.w = 10;
}

Fighter::~Fighter()
{
	pShip = nullptr;
	pBlade = nullptr;
	pShot = nullptr;
	pTimer = nullptr;
	pExplosion = nullptr;

	delete pShip;
	delete pBlade;
	delete pShot;
	delete pTimer;
	delete pExplosion;
}

void Fighter::ResetMineTimer(void)
{
	m_MineTimer = m_MineTimerAmount + Window::Random(0, m_MineTimerAmount) + pTimer->Seconds();
}

void Fighter::ResetShotTimer(void)
{
	m_ShotTimer = m_ShotTimerAmount + Window::Random(0, m_ShotTimerAmount) + pTimer->Seconds();
}

void Fighter::ResetChangeVectorTimer(void)
{
	m_ChangeVectorTimer = m_ChangeVectorTimerAmount + Window::Random(0, m_ChangeVectorTimerAmount) + pTimer->Seconds();
}

void Fighter::TimerCheck(void)
{
	if (m_MineTimer < pTimer->Seconds())
	{
		LayMine();
		ResetMineTimer();
	}

	if (m_ShotTimer < pTimer->Seconds())
	{
		ShotPlayer();
		ResetShotTimer();
	}

	if (m_ChangeVectorTimer < pTimer->Seconds())
	{
		ChangeVector();
		ResetChangeVectorTimer();
	}
}

void Fighter::LayMine(void)
{
	float scale = 3.5;
	m_Mines.push_back(new DoubleMine());
	int mine = m_Mines.size() - 1;
	m_Mines[mine]->Initialize();
	m_Mines[mine]->SetScale(&scale);
	m_Mines[mine]->MineDropped(&m_Location);
}

void Fighter::ShotPlayer(void)
{
	float angle = atan2(m_PlayerLocation.y - m_Location.y, m_PlayerLocation.x - m_Location.x);
	pShot->Activate(&m_Location, &angle);
	ResetShotTimer();
}

void Fighter::ChangeVector(void)
{
	float angle;

	if (Window::Random(0, 2))
	{
		angle = Window::Random(0, (Pi * 2) * 10) * 0.1;
	}
	else
	{
		angle = atan2(m_PlayerLocation.y - m_Location.y, m_PlayerLocation.x - m_Location.x);
	}

	m_Velocity.x = cos(angle) * m_Speed;
	m_Velocity.y = sin(angle) * m_Speed;

	m_Speed += 10;
}

void Fighter::CheckBorders(void)
{
	if (CheckForXEdge())
	{
		BounceX();

		if (m_Location.x > Window::GetWindowSize().x / 2)
		{
			m_Location.x -= 2;

			if (m_Location.y > Window::GetWindowSize().y / 2)
				m_OutsideLineHit[7] = true;
			else
				m_OutsideLineHit[6] = true;
		}
		else
		{
			m_Location.x += 2;

			if (m_Location.y > Window::GetWindowSize().y / 2)
				m_OutsideLineHit[5] = true;
			else
				m_OutsideLineHit[4] = true;
		}
	}
	else
	{
		for (int line = 4; line < 8; line++)
			m_OutsideLineHit[line] = false;
	}

	if (CheckForYEdge())
	{
		BounceY();

		if (m_Location.y > Window::GetWindowSize().y / 2)
		{
			m_Location.y -= 2;

			if (m_Location.x > Window::GetWindowSize().x / 2)
				m_OutsideLineHit[3] = true;
			else
				m_OutsideLineHit[2] = true;
		}
		else
		{
			m_Location.y += 2;

			if (m_Location.x > Window::GetWindowSize().x / 2)
				m_OutsideLineHit[1] = true;
			else
				m_OutsideLineHit[0] = true;
		}
	}
	else
	{
		for (int line = 0; line < 4; line++)
			m_OutsideLineHit[line] = false;
	}

	if (RectangleIntersect(&m_InsideBorder))
	{
		int maxborder = m_InsideBorder.x + m_InsideBorder.w - 1;
		if (ValueInRange(&m_Location.x, &m_InsideBorder.x, &maxborder))
		{
			BounceY();

			if (m_Location.y > Window::GetWindowSize().y / 2)
			{
				m_Location.y += 1;
				m_InsideLineHit[2] = true;
			}
			else
			{
				m_Location.y -= 1;
				m_InsideLineHit[0] = true;
			}
		}

		maxborder = m_InsideBorder.y + m_InsideBorder.h - 1;
		if (ValueInRange(&m_Location.y, &m_InsideBorder.y, &maxborder))
		{
			BounceX();

			if (m_Location.x > Window::GetWindowSize().x / 2)
			{
				m_Location.x += 1;
				m_InsideLineHit[1] = true;
			}
			else
			{
				m_Location.x -= 1;
				m_InsideLineHit[3] = true;
			}
		}
	}
	else
	{
		for (int line = 0; line < 4; line++)
		{
			m_InsideLineHit[line] = false;
		}
	}
}
