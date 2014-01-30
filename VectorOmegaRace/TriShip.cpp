#include "TriShip.h"

void TriShip::Update(Vector2f *Location, float *Scale)
{
	MoveScale(Location, Scale);
}

void TriShip::Draw(void)
{
	for (int line = 0; line < 3; line++)
	{
		Window::DrawLine(&NewTriangle[line], &m_ShipColor);
	}
}

TriShip::TriShip()
{
	Initilize();
}

TriShip::~TriShip()
{
}

void TriShip::MoveScale(Vector2f *Location, float *Scale)
{
	float scale = *Scale;

	for (int line = 0; line < 3; line++)
	{
		NewTriangle[line].LineStart = Triangle[line].LineStart * scale;
		NewTriangle[line].LineEnd = Triangle[line].LineEnd * scale;

		NewTriangle[line].LineStart += *Location;
		NewTriangle[line].LineEnd += *Location;
	}
}

void TriShip::Initilize(void)
{
	m_ShipColor.Red = 150;
	m_ShipColor.Green = 80;
	m_ShipColor.Blue = 200;
	m_ShipColor.Alpha = 255;

	Triangle[0].LineStart = Vector2i(-2, 1);
	Triangle[1].LineStart = Vector2i(0, -2);
	Triangle[2].LineStart = Vector2i(2, 1);

	Triangle[0].LineEnd = Triangle[1].LineStart;
	Triangle[1].LineEnd = Triangle[2].LineStart;
	Triangle[2].LineEnd = Triangle[0].LineStart;
}