#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Timer.h"
#include "PlayerShot.h"
#include "PlayerShip.h"

class Player : public Entity
{
private:
	bool m_Thrust;
	bool m_Fire;
	bool m_TurnRight;
	bool m_TurnLeft;
	bool m_Hit;
	bool m_ExplosionOn;
	bool m_InsideLineHit[4];
	bool m_OutsideLineHit[8];
	int m_NumberOfShots;
	float m_MaxThrust;
	float m_ThrustMagnitude;
	float m_TurnRate;
	double m_ThrustDrawTimer;
	double m_ThrustDrawTimerAmount;
	double m_ExplosionTimer;
	double m_ExplosiontTimerAmount;
	SDL_Rect m_InsideBorder;

	Mix_Chunk *p_Shotsound = nullptr;
	Mix_Chunk *p_Thrustsound = nullptr;
	Mix_Chunk *p_Explosionsound = nullptr;
	Mix_Chunk *p_HitLine = nullptr;

	int m_ThrustChannel = -1;

	Timer *pTimer;
	PlayerShot *pShots[4];
	PlayerShip *pShip;
	Color ShipColor;

	void UpdateShip(void);
	void UpdateShots(double *Frame);
	void UpdateRotationThrust(void);
	void UpdateEdge(void);
	void InitializeShot(void);
	void DrawShots(void);
	void DrawThrust(void);
	void FireShot(void);
	void SetExplosion(void);

public:
	Player(void);
	~Player(void);

	void Draw(void);
	void Update(double *frame);
	void NewGame(void);
	void Restart(void);
	void Hit(void);
	void Spawn(bool *rightSide);
	void FireButtonPressed(void);
	void SetThrust(bool *Thrust);
	void SetTurnRight(bool *TurnRight);
	void SetTurnLeft(bool *TurnLeft);
	void SetShotActive(int *Shot, bool *Active);
	void SetInsideBorder(SDL_Rect *border);
	void TimerPause(void);
	void TimerUnpause(void);
	int GetNumberOfShots(void);
	float GetShotRadius(void);
	Vector2i GetShotLocation(int *Shot);
	bool GetShotActive(int *Shot);
	bool GetShotCircle(Vector2f *location, float *radius, int *shot);
	bool GetHit(void);
	bool GetExplosionOn(void);
	bool GetInsideLineHit(int *line);
	bool GetOutsideLineHit(int *line);
};
#endif