#include "Shot.h"

void Shot::Update(double *Frame)
{
	if (m_Active)
	{
		UpdateFrame(Frame);
		
		if (pTimer->Seconds() > m_ShotTimer)
			m_Active = false;

		CheckForEdge();
	}
	else
	{
		for (int line = 0; line < 4; line++)
			m_InsideLines[line] = false;

		for (int line = 0; line < 8; line++)
			m_OutsideLines[line] = false;
	}
}

void Shot::Draw(void)
{
	if (m_Active)
	{		
		Vector2i location;

		Window::DrawPoint(&(Vector2i)m_Location, &m_InsideColor);
		location = m_Location + Vector2i(1, 0);
		Window::DrawPoint(&location, &m_OutsideColor);
		location = m_Location + Vector2i(0, 1);
		Window::DrawPoint(&location, &m_OutsideColor);
		location = m_Location + Vector2i(-1, 0);
		Window::DrawPoint(&location, &m_OutsideColor);
		location = m_Location + Vector2i(0, -1);
		Window::DrawPoint(&location, &m_OutsideColor);
	}
}

void Shot::Activate(Vector2f *location, float *Angle)
{
	m_Active = true;
	m_Angle = *Angle;
	m_Location = *location;

	float sinRot = sin(m_Angle);
	float cosRot = cos(m_Angle);

	m_Location.x += cosRot * 15;
	m_Location.y += sinRot * 15;

	m_Velocity.x = cosRot * m_Speed;
	m_Velocity.y = sinRot * m_Speed;

	for (int line = 0; line < 4; line++)
		m_InsideLines[line] = false;

	for (int line = 0; line < 8; line++)
		m_OutsideLines[line] = false;

	m_ShotTimer = m_ShotTimeLimit + pTimer->Seconds();
}

void Shot::TimerPause(void)
{
	pTimer->Pause();
}

void Shot::TimerUnpause(void)
{
	pTimer->Unpause();
}

void Shot::SetInsideBorder(SDL_Rect *border)
{
	m_InsideBorder = *border;
}

bool Shot::GetInsideLine(int *line)
{
	return m_InsideLines[*line];
}

bool Shot::GetOutsideLine(int *line)
{
	return m_OutsideLines[*line];
}

void Shot::SetInsideLine(int *line)
{
	m_InsideLines[*line] = false;
}

Shot::Shot(void) : Entity()
{
	m_Active = false;
	m_Speed = 250;
	m_ShotTimer = 0;
	m_Angle = 0;
	m_ShotTimeLimit = 1.6;
	m_Radius = 2;
	m_Rectangle.w = 2;
	m_Rectangle.h = 2;

	pTimer = new Timer();
	pTimer->Start();

	//Inside color
	m_InsideColor.Red = 170;
	m_InsideColor.Green = 150;
	m_InsideColor.Blue = 200;
	m_InsideColor.Alpha = 255;

	//180, 000, 185, 180
	m_OutsideColor.Red = 200;
	m_OutsideColor.Green = 50;
	m_OutsideColor.Blue = 185;
	m_OutsideColor.Alpha = 180;
}

Shot::~Shot(void)
{
	delete pTimer;
}

void Shot::CheckForEdge(void)
{
	if (CheckForXEdge())
	{
		m_Active = false;

		if (m_Location.x > Window::GetWindowSize().x / 2)
		{
			m_Location.x -= 2;

			if (m_Location.y > Window::GetWindowSize().y / 2)
				m_OutsideLines[7] = true;
			else
				m_OutsideLines[6] = true;
		}
		else
		{
			m_Location.x += 2;

			if (m_Location.y > Window::GetWindowSize().y / 2)
				m_OutsideLines[5] = true;
			else
				m_OutsideLines[4] = true;
		}
	}

	if (CheckForYEdge())
	{
		m_Active = false;

		if (m_Location.y > Window::GetWindowSize().y / 2)
		{
			m_Location.y -= 2;

			if (m_Location.x > Window::GetWindowSize().x / 2)
				m_OutsideLines[3] = true;
			else
				m_OutsideLines[2] = true;
		}
		else
		{
			m_Location.y += 2;

			if (m_Location.x > Window::GetWindowSize().x / 2)
				m_OutsideLines[1] = true;
			else
				m_OutsideLines[0] = true;
		}
	}

	if (RectangleIntersect(&m_InsideBorder))
	{
		m_Active = false;

		if (ValueInRange(&m_Location.x, &m_InsideBorder.x + 5, &m_InsideBorder.x + m_InsideBorder.w - 5))
		{
			if (m_Location.y > Window::GetWindowSize().y / 2)
			{
				m_InsideLines[2] = true;
			}
			else
			{
				m_InsideLines[0] = true;
			}
		}

		if (ValueInRange(&m_Location.y, &m_InsideBorder.y + 5, &m_InsideBorder.y + m_InsideBorder.h - 5))
		{
			if (m_Location.x > Window::GetWindowSize().x / 2)
			{
				m_InsideLines[1] = true;
			}
			else
			{
				m_InsideLines[3] = true;
			}
		}
	}
}