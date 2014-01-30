#ifndef DOUBLEMINE_H
#define DOUBLEMINE_H
#include "Entity.h"

class DoubleMine : public Entity
{
private:
	Line Triangle[5];
	Line NewTriangle[5];
	Color m_ShipColor;

public:
	DoubleMine();
	~DoubleMine();

	void Initialize(void);
	void Draw(void);
	void MineDropped(Vector2f *location);
};

#endif