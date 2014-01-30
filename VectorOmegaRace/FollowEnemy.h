#ifndef FOLLOWENEMY_H
#define FOLLOWENEMY_H
#include "Enemy.h"
#include "TriShip.h"
#include "Mine.h"
#include "Timer.h"

class FollowEnemy :
	public Enemy
{
private:
	TriShip *pTriShip = nullptr;
	std::vector<Mine*> m_Mines;
	Timer *pTimer = nullptr;

	float m_MineTimer;
	float m_MineTimerAmount;

	void SpawnMine(void);
	void TimeToLayMine(void);
	void ResetTimer(void);

public:
	FollowEnemy();
	~FollowEnemy();

	void Update(double *Frame);
	void Draw(void);
	void NewGame(void);
	Vector2f GetMineLocaiton(int *mine);
	float GetMineRadius(void);
	int GetMineCount(void);
	bool GetMineActive(int *mine);
	void MineHit(int *mine);
	void TimerPause(void);
	void TimerUnpause(void);
};

#endif