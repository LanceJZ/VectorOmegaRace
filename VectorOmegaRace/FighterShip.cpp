#include "FighterShip.h"

void FighterShip::Update(Vector2f *location, float *rotation)
{
	MoveRotateLines(rotation, location);
}

void FighterShip::Draw(void)
{
	for (int line = 0; line < 2; line++)
	{
		Window::DrawLine(&NewShipLines[line], &m_ShipColor);
	}
}

FighterShip::FighterShip(void)
{
	m_Scale = 4.5;
	Initilize();
}

FighterShip::~FighterShip(void)
{

}

void FighterShip::Initilize()
{
	m_ShipColor.Red = 150;
	m_ShipColor.Green = 80;
	m_ShipColor.Blue = 200;
	m_ShipColor.Alpha = 255;

	ShipLines[0].LineStart = Vector2i(0, -2);
	ShipLines[1].LineStart = Vector2i(-2, 0);

	ShipLines[0].LineEnd = Vector2i(0, 2);
	ShipLines[1].LineEnd = Vector2i(2, 0);
}

void FighterShip::MoveRotateLines(float *rotation, Vector2f *location)
{
	float sinRot = sin(*rotation);
	float cosRot = cos(*rotation);

	for (int line = 0; line < 2; line++)
	{
		NewShipLines[line].LineStart.x = ShipLines[line].LineStart.x * m_Scale * cosRot - ShipLines[line].LineStart.y * m_Scale * sinRot;
		NewShipLines[line].LineStart.y = ShipLines[line].LineStart.x * m_Scale * sinRot + ShipLines[line].LineStart.y * m_Scale * cosRot;

		NewShipLines[line].LineEnd.x = ShipLines[line].LineEnd.x * m_Scale * cosRot - ShipLines[line].LineEnd.y  * m_Scale * sinRot;
		NewShipLines[line].LineEnd.y = ShipLines[line].LineEnd.x * m_Scale * sinRot + ShipLines[line].LineEnd.y * m_Scale * cosRot;

		NewShipLines[line].LineStart += *location;
		NewShipLines[line].LineEnd += *location;
	}
}