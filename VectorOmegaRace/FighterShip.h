#ifndef FIGHTERSHIP_H
#define FIGHTERSHIP_H
#include "Window.h"

class FighterShip
{
private:
	Line ShipLines[2];
	Line NewShipLines[2];
	Color m_ShipColor;
	float m_Scale;

	void MoveRotateLines(float *rotation, Vector2f *location);
	void Initilize();

public:
	FighterShip(void);
	~FighterShip(void);

	void Update(Vector2f *location, float *rotation);
	void Draw(void);
};

#endif