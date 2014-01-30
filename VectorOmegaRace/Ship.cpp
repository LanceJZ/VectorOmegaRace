#include "Ship.h"

void Ship::Update(float *Rotation, Vector2f *Location, float *Scale)
{
	MoveRotateLines(Rotation, Location, Scale);
}

void Ship::Draw(void)
{
	for (int line = 0; line < 8; line++)
	{
		Window::DrawLine(&NewShipLines[line], &m_ShipColor);
	}
}

Ship::Ship()
{

}

Ship::~Ship()
{
}

void Ship::MoveRotateLines(float *Rotation, Vector2f *Location, float *Scale)
{
	float sinRot = sin(*Rotation);
	float cosRot = cos(*Rotation);
	float scale = *Scale;

	for (int line = 0; line < 8; line++)
	{
		NewShipLines[line].LineStart.x = ShipLines[line].LineStart.x * scale * cosRot - ShipLines[line].LineStart.y * scale * sinRot;
		NewShipLines[line].LineStart.y = ShipLines[line].LineStart.x * scale * sinRot + ShipLines[line].LineStart.y * scale * cosRot;

		NewShipLines[line].LineEnd.x = ShipLines[line].LineEnd.x * scale * cosRot - ShipLines[line].LineEnd.y  * scale * sinRot;
		NewShipLines[line].LineEnd.y = ShipLines[line].LineEnd.x * scale * sinRot + ShipLines[line].LineEnd.y * scale * cosRot;

		NewShipLines[line].LineStart += *Location;
		NewShipLines[line].LineEnd += *Location;
	}
}

void Ship::Initialize(void)
{
	m_ShipColor.Red = 150;
	m_ShipColor.Green = 80;
	m_ShipColor.Blue = 200;
	m_ShipColor.Alpha = 255;

	ShipLines[0].LineStart = Vector2i(-3, -3);
	ShipLines[1].LineStart = Vector2i(3, -3);
	ShipLines[2].LineStart = Vector2i(3, 3);
	ShipLines[3].LineStart = Vector2i(-3, 3);
	ShipLines[4].LineStart = Vector2i(-4, 0);
	ShipLines[5].LineStart = Vector2i(0, -4);
	ShipLines[6].LineStart = Vector2i(4, 0);
	ShipLines[7].LineStart = Vector2i(0, 4);

	ShipLines[0].LineEnd = ShipLines[1].LineStart;
	ShipLines[1].LineEnd = ShipLines[2].LineStart;
	ShipLines[2].LineEnd = ShipLines[3].LineStart;
	ShipLines[3].LineEnd = ShipLines[0].LineStart;
	ShipLines[4].LineEnd = ShipLines[5].LineStart;
	ShipLines[5].LineEnd = ShipLines[6].LineStart;
	ShipLines[6].LineEnd = ShipLines[7].LineStart;
	ShipLines[7].LineEnd = ShipLines[4].LineStart;
}