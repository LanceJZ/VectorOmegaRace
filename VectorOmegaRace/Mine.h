#ifndef MINE_H
#define MINE_H
#include "Entity.h"
#include "TriShip.h"

class Mine :
	public Entity
{
private:
	TriShip *pMine;

public:
	Mine(void);
	~Mine(void);

	void Draw(void);
	void MineDropped(void);
};

#endif