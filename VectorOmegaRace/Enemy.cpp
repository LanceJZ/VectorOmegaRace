#include "Enemy.h"

void Enemy::Update(double *Frame)
{
	UpdateFrame(Frame);

	if (m_Active)
	{
		CheckForTurn();
		pShip->Update(&m_Rotation.Amount, &m_Location, &m_Scale);
	}

	pExplosion->Update(Frame);
}

void Enemy::Draw(void)
{
	if (m_Active)
		pShip->Draw();

	pExplosion->Draw();
}

void Enemy::SetRightSide(bool *rightSide)
{
	m_RightSide = *rightSide;
}

WhenToTurn Enemy::GetTurns(void)
{
	return m_WhenToTurn;
}

void Enemy::SetTurns(WhenToTurn *turns)
{
	m_WhenToTurn = *turns;
}

void Enemy::SetTurns(void)
{
	m_WhenToTurn.Left = Window::Random(25, int(Window::GetWindowSize().x * 0.15625f) - 8);
	m_WhenToTurn.Right = Window::Random(int(Window::GetWindowSize().x * 0.84375f) + 8, Window::GetWindowSize().x - 25);
	m_WhenToTurn.Top = Window::Random(25, int(Window::GetWindowSize().y * 0.3335f));
	m_WhenToTurn.Bottom = m_Location.y;
}

void Enemy::StartMoving(void)
{
	m_Velocity.y = 0;

	if (m_RightSide)
	{
		m_Rotation.Velocity = -Pi * 0.5f;
		m_Velocity.x = m_MoveSpeed;
	}
	else
	{
		m_Rotation.Velocity = Pi * 0.5f;
		m_Velocity.x = -m_MoveSpeed;
	}
}

void Enemy::Explode(void)
{
	pExplosion->Activate(m_Location, 4);
}

bool Enemy::GetExplosionActive(void)
{
	return pExplosion->GetActive();
}

Enemy::Enemy()
{
	m_Radius = 16;
	m_Scale = 3;
	m_Rectangle.h = 16;
	m_Rectangle.w = 16;
}

Enemy::~Enemy()
{
	pShip = nullptr;
	pExplosion = nullptr;

	delete pShip;
	delete pExplosion;
}

void Enemy::CheckForTurn(void)
{
	if (m_RightSide)
	{
		if (m_Location.x <= m_WhenToTurn.Left)
		{
			if (m_Location.y >= m_WhenToTurn.Bottom)
			{
				m_Velocity.y = 0;
				m_Velocity.x = m_MoveSpeed;
			}

			if (m_Location.y <= m_WhenToTurn.Top)
			{
				m_Velocity.y = m_MoveSpeed;
				m_Velocity.x = 0;
			}
		}

		if (m_Location.x >= m_WhenToTurn.Right)
		{
			if (m_Location.y >= m_WhenToTurn.Bottom)
			{
				m_Velocity.y = -m_MoveSpeed;
				m_Velocity.x = 0;
			}

			if (m_Location.y <= m_WhenToTurn.Top)
			{
				m_Velocity.y = 0;
				m_Velocity.x = -m_MoveSpeed;
			}
		}
	}
	else
	{
		if (m_Location.x <= m_WhenToTurn.Left)
		{
			if (m_Location.y >= m_WhenToTurn.Bottom)
			{
				m_Velocity.y = -m_MoveSpeed;
				m_Velocity.x = 0;
			}

			if (m_Location.y <= m_WhenToTurn.Top)
			{
				m_Velocity.y = 0;
				m_Velocity.x = m_MoveSpeed;
			}
		}

		if (m_Location.x >= m_WhenToTurn.Right)
		{
			if (m_Location.y >= m_WhenToTurn.Bottom)
			{
				m_Velocity.y = 0;
				m_Velocity.x = -m_MoveSpeed;
			}

			if (m_Location.y <= m_WhenToTurn.Top)
			{
				m_Velocity.y = m_MoveSpeed;
				m_Velocity.x = 0;
			}
		}
	}
}

void Enemy::SetSpeed(float *speed)
{
	m_MoveSpeed = *speed;
}

void Enemy::Initialize(void)
{
	pShip = new Ship();
	pShip->Initialize();
	pExplosion = new Explosion();
}

