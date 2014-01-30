#ifndef EXPLOSIONLINE_H
#define EXPLOSIONLINE_H
#include "Entity.h"
#include "Timer.h"

class ExplosionLine :
	public Entity
{
private:
	float m_Timer;
	int m_TimerAmount;
	Timer *pTimer;
	float m_Alpha;
	Color m_Color;
	Line m_Line;

public:
	ExplosionLine();
	~ExplosionLine();

	void Draw(void);
	void Update(double *Frame);
	void Activate(Vector2i location, float angle, int size);
	//Needs timer pause and unpause.
	void PauseTimer(void);
	void UnpauseTimer(void);
};

#endif