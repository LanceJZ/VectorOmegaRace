#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H
#include <vector>
#include "Enemy.h"
#include "LeadEnemy.h"
#include "FollowEnemy.h"
#include "Fighter.h"
#include "Common.h"
#include "Timer.h"

class EnemyController : public Common
{
private:
	int m_NumberOfShips;
	bool m_RightSide;
	bool m_FollowActive;
	float m_EnemySpeed;
	float m_FighterTimer;
	float m_FighterTimerAmount;
	double m_Frame;

	Timer *pTimer = nullptr;
	LeadEnemy *pLeadEnemyShip = nullptr;
	FollowEnemy *pFollowEnemyShip = nullptr;
	Fighter *pFighter = nullptr;
	std::vector<Enemy*> m_EnemyShips;

	void SpawnShip(int ship);
	void PlaceFollowEnemy(int ship);
	void CheckFighterTimer(void);
	void ResetFighterTimer(void);
	void LaunchFighter(void);
	bool EnemyLeft(void);
	int FindEnemy(void);

public:
	EnemyController(void);
	~EnemyController(void);

	Fighter *GetFighterPointer(void);
	FollowEnemy *GetFollowPointer(void);
	LeadEnemy *GetLeadPointer(void);

	void Update(double *Frame);
	void Draw(void);
	Vector2f GetEnemyLocaiton(int *ship);
	void SpawnNewWave(bool *rightSide, int *numberOfShips);
	void EnemyHit(int *ship);
	void LeadEnemyHit(void);
	void FollowEnemyHit(void);
	void ResumeWave(void);
	void SetInisdeBorder(SDL_Rect *border);
	void TimerPause(void);
	void TimerUnpause(void);
	bool CheckEndOfWave(void);
	bool GetEnemyCircle(Vector2f *location, float *radius, int *ship);
	bool GetEnemyActive(int *ship);
	bool CheckExploding(void);
	int NewGame(void);
	int NewWave(void);
	int RestartWave(void);
	int GetEnemyCount(void);
	float GetEnemyRadius(void);
};

#endif