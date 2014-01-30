#include "PlayerShip.h"

void PlayerShip::Update(float *rotation, Vector2f *location, float *scale)
{
	MoveRotateLines(rotation, location, scale);
}

void PlayerShip::Draw(Color *color)
{
	//Set each point as an array then you can use a for/next to draw the three lines.
	for (int line = 0; line < 12; line++)
	{
		Window::DrawLine(&NewPlayerLines[line], color);
	}
}

void PlayerShip::DrawThrust(void)
{
	for (int line = 0; line < 2; line++)
	{
		Window::DrawLine(&NewThrustLines[line], &m_ThrustColor);
	}
}

void PlayerShip::UpdateExplosion(double *frame)
{
	for (int line = 0; line < 12; line++)
	{
		pExplosionLines[line]->Update(frame);
	}
}

void PlayerShip::DrawExplosion(void)
{
	for (int line = 0; line < 12; line++)
	{
		pExplosionLines[line]->Draw();
	}
}

void PlayerShip::SetExplosion(Vector2i *Location)
{
	for (int line = 0; line < 12; line++)
	{
		pExplosionLines[line]->Initialize(&NewPlayerLines[line], Location);
	}
}

void PlayerShip::InitializeLines()
{
	for (int line = 0; line < 12; line++)
	{
		pExplosionLines[line] = new PlayerExplosionLine();
	}
}

PlayerShip::PlayerShip()
{
	m_ThrustColor.Red = 150;
	m_ThrustColor.Green = 0;
	m_ThrustColor.Blue = 230;
	m_ThrustColor.Alpha = 255;
	Initialize();
}


PlayerShip::~PlayerShip()
{
}

void PlayerShip::Initialize(void)
{
	PlayerLines[0].LineStart = Vector2i(-4, 3);
	PlayerLines[1].LineStart = Vector2i(-4, -3);
	PlayerLines[2].LineStart = Vector2i(-4, -3);
	PlayerLines[3].LineStart = Vector2i(-4, 3);
	PlayerLines[4].LineStart = Vector2i(-1, 4);
	PlayerLines[5].LineStart = Vector2i(-1, -4);
	PlayerLines[6].LineStart = Vector2i(2, 0);
	PlayerLines[7].LineStart = Vector2i(3, 1);
	PlayerLines[8].LineStart = Vector2i(2, 0);
	PlayerLines[9].LineStart = Vector2i(3, -1);
	PlayerLines[10].LineStart = Vector2i(-1, 4);
	PlayerLines[11].LineStart = Vector2i(-1, -4);

	PlayerLines[0].LineEnd = Vector2i(2, 0);
	PlayerLines[1].LineEnd = Vector2i(2, 0);
	PlayerLines[2].LineEnd = Vector2i(-1, 4);
	PlayerLines[3].LineEnd = Vector2i(-1, -4);
	PlayerLines[4].LineEnd = Vector2i(2, 0);
	PlayerLines[5].LineEnd = Vector2i(2, 0);
	PlayerLines[6].LineEnd = Vector2i(3, 1);
	PlayerLines[7].LineEnd = Vector2i(4, 0);
	PlayerLines[8].LineEnd = Vector2i(3, -1);
	PlayerLines[9].LineEnd = Vector2i(4, 0);
	PlayerLines[10].LineEnd = Vector2i(1, 4);
	PlayerLines[11].LineEnd = Vector2i(1, -4);

	//Thrust Lines -------------

	ThrustLines[0].LineStart = Vector2i(-6, 0);
	ThrustLines[1].LineStart = Vector2i(-6, 0);

	ThrustLines[0].LineEnd = Vector2i(-3, 2);
	ThrustLines[1].LineEnd = Vector2i(-3, -2);
}

void PlayerShip::MoveRotateLines(float *Rotation, Vector2f *Location, float *Scale)
{
	float sinRot = sin(*Rotation);
	float cosRot = cos(*Rotation);
	float scale = *Scale;

	for (int line = 0; line < 12; line++)
	{
		NewPlayerLines[line].LineStart.x = PlayerLines[line].LineStart.x * scale * cosRot - PlayerLines[line].LineStart.y * scale * sinRot;
		NewPlayerLines[line].LineStart.y = PlayerLines[line].LineStart.x * scale * sinRot + PlayerLines[line].LineStart.y * scale * cosRot;

		NewPlayerLines[line].LineEnd.x = PlayerLines[line].LineEnd.x * scale * cosRot - PlayerLines[line].LineEnd.y  * scale * sinRot;
		NewPlayerLines[line].LineEnd.y = PlayerLines[line].LineEnd.x * scale * sinRot + PlayerLines[line].LineEnd.y * scale * cosRot;

		NewPlayerLines[line].LineStart += *Location;
		NewPlayerLines[line].LineEnd += *Location;
	}

	for (int line = 0; line < 2; line++)
	{
		NewThrustLines[line].LineStart.x = ThrustLines[line].LineStart.x * scale * cosRot - ThrustLines[line].LineStart.y * scale * sinRot;
		NewThrustLines[line].LineStart.y = ThrustLines[line].LineStart.x * scale * sinRot + ThrustLines[line].LineStart.y * scale * cosRot;

		NewThrustLines[line].LineEnd.x = ThrustLines[line].LineEnd.x * scale * cosRot - ThrustLines[line].LineEnd.y * scale * sinRot;
		NewThrustLines[line].LineEnd.y = ThrustLines[line].LineEnd.x * scale * sinRot + ThrustLines[line].LineEnd.y * scale * cosRot;

		NewThrustLines[line].LineStart += *Location;
		NewThrustLines[line].LineEnd += *Location;
	}
}
