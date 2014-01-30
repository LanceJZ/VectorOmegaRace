#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "Ship.h"
#include "Explosion.h"

struct WhenToTurn
{
	int Left;
	int Right;
	int Top;
	int Bottom;
};

class Enemy :
	public Entity
{
private:
	Ship *pShip;
	Explosion *pExplosion;
	WhenToTurn m_WhenToTurn;
	bool m_RightSide;

protected:
	float m_MoveSpeed;

	void CheckForTurn(void);

public:
	Enemy();
	~Enemy();

	void Update(double *Frame);
	void Draw(void);
	void Initialize(void);
	void SetRightSide(bool *rightSide);
	void SetTurns(void);
	void StartMoving(void);
	void SetSpeed(float *speed);
	void SetTurns(WhenToTurn *turns);
	void Explode(void);
	bool GetExplosionActive(void);
	WhenToTurn GetTurns(void);
};

#endif