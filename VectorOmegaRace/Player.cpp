#include "Player.h"

//Public Methods
void Player::Draw(void)
{
	if (m_Active && !m_Hit)
	{
		pShip->Draw(&ShipColor);

		if (m_Thrust)
			DrawThrust();
	}
	else if (m_ExplosionOn)
		pShip->DrawExplosion();

	DrawShots();
}

void Player::Update(double *Frame)
{
	UpdateFrame(Frame);
	UpdateShots(Frame);

	if (m_Active && !m_Hit)
	{
		UpdateEdge();
		UpdateRotationThrust();
		UpdateShip();
		pShip->Update(&m_Rotation.Amount, &m_Location, &m_Scale);
	}
	else if (m_ExplosionOn)
	{
		pShip->UpdateExplosion(Frame);

		if (m_ExplosionTimer < pTimer->Seconds())
			m_ExplosionOn = false;
	}
}

void Player::FireButtonPressed(void)
{
	if (m_Active && !m_Hit)
	{
		FireShot();
	}
}

int Player::GetNumberOfShots(void)
{
	return m_NumberOfShots;
}

float Player::GetShotRadius(void)
{
	return pShots[0]->GetRadius();
}

Vector2i Player::GetShotLocation(int *Shot)
{
	return pShots[*Shot]->GetLocation();
}

bool Player::GetShotActive(int *Shot)
{
	return pShots[*Shot]->GetActive();
}

bool Player::GetShotCircle(Vector2f *location, float *radius, int *shot)
{
	return pShots[*shot]->CirclesIntersect(location, radius);
}

bool Player::GetHit()
{
	return m_Hit;
}

bool Player::GetExplosionOn()
{
	return m_ExplosionOn;
}

void Player::SetShotActive(int *Shot, bool *Active)
{
	pShots[*Shot]->SetActive(Active);
}

void Player::SetThrust(bool *Thrust)
{
	m_Thrust = *Thrust;
}

void Player::SetTurnRight(bool *TurnRight)
{
	m_TurnRight = *TurnRight;
}

void Player::SetTurnLeft(bool *TurnLeft)
{
	m_TurnLeft = *TurnLeft;
}

void Player::NewGame(void)
{
	pTimer->Start();
	m_Active = true;
}

void Player::Restart(void)
{
	m_Active = true;
}

void Player::Hit(void)
{
	if (!m_Hit)
	{
		//Play Player explosion sound.
		Mix_PlayChannel(-1, p_Explosionsound, 0);

		m_ExplosionOn = true;
		m_Hit = true;
		SetExplosion();

		//Turn off thrust sound.
		if (m_ThrustChannel > -1)
		{
			Mix_HaltChannel(m_ThrustChannel);
			m_ThrustChannel = -1;
		}
	}
}

void Player::Spawn(bool *rightSide)
{
	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		bool False = false;
		pShots[shot]->SetActive(&False);
	}

	if (*rightSide)
	{
		m_Rotation.Amount = 0;
		m_Location.x = Window::GetWindowSize().x / 11.1;
	}
	else
	{
		m_Rotation.Amount = Pi;
		m_Location.x = Window::GetWindowSize().x / 1.1;
	}
	
	m_Location.y = Window::GetWindowSize().y / 3;
	m_Hit = false;
	m_Acceleration = Vector2i();
	m_Velocity = Vector2i();	
}

void Player::SetInsideBorder(SDL_Rect *border)
{
	m_InsideBorder = *border;

	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		pShots[shot]->SetInsideBorder(&m_InsideBorder);
	}
}

bool Player::GetInsideLineHit(int *line)
{
	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		if (pShots[shot]->GetInsideLine(line))
			m_InsideLineHit[*line] = true;

		pShots[shot]->SetInsideLine(line);
	}

	return m_InsideLineHit[*line];
}

bool Player::GetOutsideLineHit(int *line)
{
	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		if (pShots[shot]->GetOutsideLine(line))
			m_OutsideLineHit[*line] = true;
	}

	return m_OutsideLineHit[*line];
}

Player::Player(void) : Entity()
{
	m_Thrust = false;
	m_Fire = false;
	m_TurnRight = false;
	m_TurnLeft = false;
	m_Active = false;
	m_Hit = false;
	m_ExplosionOn = false;
	m_Radius = 16;
	m_Scale = 2.5;
	m_Rectangle.h = 16;
	m_Rectangle.w = 16;

	m_MaxThrust = 325;
	m_ThrustMagnitude = 3.666;
	m_TurnRate = 4.5;

	m_NumberOfShots = 4;
	m_ThrustDrawTimerAmount = 0.100;
	m_ExplosiontTimerAmount = 2.500;

	pTimer = new Timer();
	pShip = new PlayerShip();
	
	//Player Ship Color
	ShipColor.Red = 120;
	ShipColor.Green = 40;
	ShipColor.Blue = 255;
	ShipColor.Alpha = 255;

	p_Shotsound = Mix_LoadWAV("PlayerShot.wav");
	Mix_VolumeChunk(p_Shotsound, MIX_MAX_VOLUME / 3);
	p_Thrustsound = Mix_LoadWAV("Thrust.wav");
	Mix_VolumeChunk(p_Thrustsound, MIX_MAX_VOLUME / 3);
	p_Explosionsound = Mix_LoadWAV("PlayerHit.wav");
	Mix_VolumeChunk(p_Explosionsound, MIX_MAX_VOLUME / 4);
	p_HitLine = Mix_LoadWAV("BorderHit.wav");
	Mix_VolumeChunk(p_HitLine, MIX_MAX_VOLUME / 3);

	InitializeShot();
	pShip->InitializeLines();
}

Player::~Player(void)
{
	pTimer = nullptr;
	pShots[0] = nullptr;
	pShots[1] = nullptr;
	pShots[2] = nullptr;
	pShots[3] = nullptr;
	pShip = nullptr;

	delete pTimer;
	delete pShots;
	delete pShip;

	p_Explosionsound = nullptr;
	p_HitLine = nullptr;
	p_Shotsound = nullptr;
	p_Thrustsound = nullptr;

	delete p_Explosionsound;
	delete p_HitLine;
	delete p_Shotsound;
	delete p_Thrustsound;
}

void Player::FireShot(void)
{
	for (int shot = 0; shot < 4; shot++)
	{
		if (!pShots[shot]->GetActive())
		{
			//If shot found that is not active, then activate that shot.
			Mix_PlayChannel(-1, p_Shotsound, 0);
			pShots[shot]->Activate(&m_Location, &m_Rotation.Amount);
			break;
		}
	}
}

void Player::UpdateShots(double *Frame)
{
	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		pShots[shot]->Update(Frame);
	}
}

void Player::DrawShots(void)
{
	for (int shot = 0; shot < m_NumberOfShots; shot++)
		pShots[shot]->Draw();
}

void Player::DrawThrust(void)
{
	if (pTimer->Seconds() > m_ThrustDrawTimer)
	{
		m_ThrustDrawTimer = pTimer->Seconds() + m_ThrustDrawTimerAmount;
	}
	else
	{
		pShip->DrawThrust();
	}
}

void Player::InitializeShot()
{
	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		pShots[shot] = new PlayerShot();
		pShots[shot]->SetInsideBorder(&m_InsideBorder);
	}
}

void Player::UpdateEdge(void)
{
	if (CheckForXEdge())
	{
		Mix_PlayChannel(-1, p_HitLine, 0);
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
		Mix_PlayChannel(-1, p_HitLine, 0);
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
		Mix_PlayChannel(-1, p_HitLine, 0);

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

void Player::UpdateShip(void)
{
	//Get rotation keys
	if (m_TurnLeft || m_TurnRight)
	{
		if (m_TurnRight)
		{
			if (m_Rotation.Amount < PiTimesTwo)
				m_Rotation.Velocity = m_TurnRate;
			else
				m_Rotation.Amount -= PiTimesTwo;
		}

		if (m_TurnLeft)
		{
			if (m_Rotation.Amount > 0.0f)
				m_Rotation.Velocity = -m_TurnRate;
			else
				m_Rotation.Amount += PiTimesTwo;
		}
	}
	else
	{
		m_Rotation.Velocity = 0;
	}
}

void Player::UpdateRotationThrust(void)
{
	//Do thrust key
	if (m_Thrust)
	{
		//Play thrust sound.
		if (m_ThrustChannel < 0)
			m_ThrustChannel = Mix_PlayChannel(-1, p_Thrustsound, -1);

		if (m_Velocity.x > m_MaxThrust)
			m_Velocity.x = m_MaxThrust;

		if (m_Velocity.x < -m_MaxThrust)
			m_Velocity.x = -m_MaxThrust;

		if (m_Velocity.y > m_MaxThrust)
			m_Velocity.y = m_MaxThrust;

		if (m_Velocity.y < -m_MaxThrust)
			m_Velocity.y = -m_MaxThrust;

		m_Acceleration.x = cos(m_Rotation.Amount) * m_ThrustMagnitude;
		m_Acceleration.y = sin(m_Rotation.Amount) * m_ThrustMagnitude;
	}
	else
	{
		//Turn off thrust sound.
		if (m_ThrustChannel > -1)
		{
			Mix_HaltChannel(m_ThrustChannel);
			m_ThrustChannel = -1;
		}

		m_Acceleration = Vector2f(0, 0);
	}
}

void Player::SetExplosion(void)
{
	pShip->SetExplosion(&(Vector2i)m_Location);
	m_ExplosionTimer = pTimer->Seconds() + m_ExplosiontTimerAmount + Window::Random(0, (int)m_ExplosiontTimerAmount);
}

void Player::TimerPause(void)
{
	for (int shot = 0; shot < 4; shot++)
	{
		pShots[shot]->TimerPause();
	}
}

void Player::TimerUnpause(void)
{
	for (int shot = 0; shot < 4; shot++)
	{
		pShots[shot]->TimerUnpause();
	}
}