#ifndef TRISHIP_H
#define TRISHIP_H
#include "Window.h"

class TriShip
{
private:
	Line Triangle[3];
	Line NewTriangle[3];
	Color m_ShipColor;

	void Initilize(void);
	void MoveScale(Vector2f *Location, float *Scale);

public:
	TriShip();
	~TriShip();

	void Update(Vector2f *Location, float *Scale);
	void Draw(void);
};

#endif