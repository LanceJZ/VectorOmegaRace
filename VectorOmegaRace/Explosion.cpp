#include "Explosion.h"

void Explosion::Draw(void)
{
	if (m_Active)
	{
		for (int line = 0; line < 12; line++)
		{
			pLines[line]->Draw();
		}
	}
}

void Explosion::Update(double *Frame)
{
	if (m_Active)
	{
		for (int line = 0; line < 12; line++)
		{
			pLines[line]->Update(Frame);
		}
	}
}

void Explosion::Activate(Vector2i location, int Size)
{
	m_Active = true;

	float angle = 0;

	for (int line = 0; line < 12; line++)
	{
		angle += (Window::Random(0, 630)) * 0.01;
		pLines[line]->Activate(location, angle, Size);
	}
}

void Explosion::PauseTimer(void)
{
	for (int line = 0; line < 12; line++)
	{
		pLines[line]->PauseTimer();
	}
}

void Explosion::UnpauseTimer(void)
{
	for (int line = 0; line < 12; line++)
	{
		pLines[line]->UnpauseTimer();
	}
}


bool Explosion::GetActive(void)
{
	bool active = false;

	for (int line = 0; line < 12; line++)
	{
		if (pLines[line]->GetActive())
			active = true;
	}

	return active;
}

Explosion::Explosion(void)
{
	m_Active = false;

	for (int line = 0; line < 12; line++)
	{
		pLines[line] = new ExplosionLine();
	}
}

Explosion::~Explosion(void)
{
	delete pLines;
}