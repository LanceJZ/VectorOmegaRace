#include "ExplosionLine.h"

void ExplosionLine::Draw(void)
{
	if (m_Active)
	{
		Window::DrawLine(&m_Line, &m_Color);
	}
}

void ExplosionLine::Update(double *Frame)
{
	if (m_Active)
	{
		if (m_Timer < pTimer->Seconds())
			m_Active = false;

		UpdateFrame(Frame);
		m_Line.LineEnd = m_Location;

		if (m_Color.Alpha > 1)
			m_Color.Alpha -= 1;
	}
}

void ExplosionLine::Activate(Vector2i location, float angle, int size)
{
	m_Active = true;
	m_Location = location + Vector2i(Window::Random(0, size), Window::Random(0, size));
	m_Line.LineStart = location;
	m_Line.LineEnd = location;
	double frame = 0;
	UpdateFrame(&frame);

	float sinRot = sin(angle);
	float cosRot = cos(angle);

	int maxV = 22;
	int minV = 15;
	m_Velocity = Vector2f(cosRot * (float)Window::Random(minV, maxV), sinRot * (float)Window::Random(minV, maxV));
	m_Timer = pTimer->Seconds() + (float)Window::Random(m_TimerAmount / 2, m_TimerAmount) * 0.01;
	m_Color.Alpha = 255;
}

void ExplosionLine::PauseTimer(void)
{
	pTimer->Pause();
}

void ExplosionLine::UnpauseTimer(void)
{
	pTimer->Unpause();
}

ExplosionLine::ExplosionLine()
{
	m_Active = false;
	m_TimerAmount = 90;
	pTimer = new Timer();
	pTimer->Start();

	m_Color.Red = 190;
	m_Color.Green = 0;
	m_Color.Blue = 200;
	m_Color.Alpha = 255;
}

ExplosionLine::~ExplosionLine()
{
	delete pTimer;
}
