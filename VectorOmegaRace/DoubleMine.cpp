#include "DoubleMine.h"

void DoubleMine::Draw(void)
{
	if (m_Active)
	{
		for (int line = 0; line < 5; line++)
		{
			Window::DrawLine(&NewTriangle[line], &m_ShipColor);
		}
	}
}

void DoubleMine::MineDropped(Vector2f *location)
{
	m_Location = *location;

	for (int line = 0; line < 5; line++)
	{
		NewTriangle[line].LineStart = Triangle[line].LineStart * m_Scale;
		NewTriangle[line].LineEnd = Triangle[line].LineEnd * m_Scale;

		NewTriangle[line].LineStart += m_Location;
		NewTriangle[line].LineEnd += m_Location;
	}

	m_Active = true;
	m_Radius = m_Scale;
}

DoubleMine::DoubleMine()
{ //Worth 500 pts
}


DoubleMine::~DoubleMine()
{
}

void DoubleMine::Initialize(void)
{
	m_ShipColor.Red = 150;
	m_ShipColor.Green = 80;
	m_ShipColor.Blue = 200;
	m_ShipColor.Alpha = 255;

	Triangle[0].LineStart = Vector2i(-2, 0);
	Triangle[1].LineStart = Vector2i(0, -2);
	Triangle[2].LineStart = Vector2i(2, 0);
	Triangle[3].LineStart = Vector2i(0, 2);
	Triangle[4].LineStart = Vector2i(-2, 0);

	Triangle[0].LineEnd = Triangle[1].LineStart;
	Triangle[1].LineEnd = Triangle[2].LineStart;
	Triangle[2].LineEnd = Triangle[3].LineStart;
	Triangle[3].LineEnd = Triangle[4].LineStart;
	Triangle[4].LineEnd = Triangle[2].LineStart;

}
