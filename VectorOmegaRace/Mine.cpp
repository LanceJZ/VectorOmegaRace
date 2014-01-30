#include "Mine.h"

void Mine::Draw(void)
{
	if (m_Active)
		pMine->Draw();
}

void Mine::MineDropped(void)
{
	pMine->Update(&m_Location, &m_Scale);
	m_Active = true;
}

Mine::Mine()
{
	pMine = new TriShip();
	m_Radius = 4;
	m_Scale = 4;
}

Mine::~Mine()
{
	delete pMine;
}
