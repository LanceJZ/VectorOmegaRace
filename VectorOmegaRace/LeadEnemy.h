#ifndef LEADENEMY_H
#define LEADENEMY_H
#include "Enemy.h"
#include "TriShip.h"
#include "Timer.h"
#include "Shot.h"

class LeadEnemy :
	public Enemy
{
private:
	float m_FireTimer;
	float m_FireTimerAmount;
	Vector2f m_PlayerLocation;

	void FireShot(void);
	void CheckToFire(void);
	void ResetShotTimer(void);

	Timer *pTimer = nullptr;
	Shot *pShot = nullptr;
	TriShip *pTriShip = nullptr;

public:
	LeadEnemy();
	~LeadEnemy();

	void Update(double *Frame);
	void Draw(void);
	void SetPlayerLocation(Vector2f *location);
	void SetInsideBorderOnShot(SDL_Rect *border);
	void ShotHitTarget(void);
	Vector2f GetShotLocation(void);
	float GetShotRadius(void);
	bool GetShotActive(void);
	void TimerPause(void);
	void TimerUnpause(void);
};

#endif