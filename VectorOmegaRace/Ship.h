#ifndef SHIP_H
#define SHIP_H
#include "Window.h"

class Ship
{
private:

protected:
	Line ShipLines[8];
	Line NewShipLines[8];
	Color m_ShipColor;

	void MoveRotateLines(float *rotation, Vector2f *location, float *scale);

public:
	Ship();
	~Ship();

	void Update(float *Rotation, Vector2f *Location, float *Scale);
	void Draw(void);
	void Initialize(void);
};

#endif