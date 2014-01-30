#ifndef FIGHTER_H
#define FIGHTER_H
#include "Entity.h"
#include "Timer.h"
#include "TriShip.h"
#include "FighterShip.h"
#include "DoubleMine.h"
#include "Shot.h"
#include "Explosion.h"

class Fighter :
	public Entity
{
private:
	Timer *pTimer;
	TriShip *pShip;
	Shot *pShot;
	FighterShip *pBlade;
	Explosion *pExplosion;
	std::vector<DoubleMine*> m_Mines;

	Vector2f m_PlayerLocation;
	SDL_Rect m_InsideBorder;
	bool m_InsideLineHit[4];
	bool m_OutsideLineHit[8];
	float m_MineTimer;
	float m_MineTimerAmount;
	float m_ShotTimer;
	float m_ShotTimerAmount;
	float m_ChangeVectorTimer;
	float m_ChangeVectorTimerAmount;
	float m_Speed;
	double m_Frame;

	void ResetMineTimer(void);
	void ResetShotTimer(void);
	void ResetChangeVectorTimer(void);
	void TimerCheck(void);
	void LayMine(void);
	void ShotPlayer(void);
	void ChangeVector(void);
	void CheckBorders(void);

public:
	Fighter(void);
	~Fighter(void);

	void Update(double *Frame);
	void Draw(void);
	void SetPlayerLocation(Vector2f *location);
	void SetInsideBorder(SDL_Rect *border);
	bool GetInsideLineHit(int *line);
	bool GetOutsideLineHit(int *line);
	Vector2f GetMineLocaiton(int *mine);
	float GetMineRadius(void);
	int GetMineCount(void);
	bool GetMineActive(int *mine);
	void MineHit(int *mine);
	Vector2f GetShotLocation(void);
	void ShotHitTarget(void);
	float GetShotRadius(void);
	bool GetShotActive(void);
	void NewGame(void);
	void Start(Vector2f *location, Vector2f *velocity);
	void TimerPause(void);
	void TimerUnpause(void);
	void Explode(void);
	bool GetExplosionActive(void);
};

#endif