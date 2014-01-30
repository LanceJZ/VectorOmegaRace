#ifndef SHOT_H
#define SHOT_H
#include "Entity.h"
#include "Timer.h"

class Shot :
	public Entity
{
private:
	bool m_InsideLines[4];
	bool m_OutsideLines[8];
	float m_ShotTimer;
	Timer *pTimer;
	Color m_InsideColor;
	Color m_OutsideColor;
	SDL_Rect m_InsideBorder;

	void CheckForEdge(void);

protected:
	float m_Angle;
	float m_ShotTimeLimit;
	float m_Speed;

public:
	Shot(void);
	~Shot(void);

	void Update(double *frame);
	void Draw(void);
	void Activate(Vector2f *location, float *Angle);
	void TimerPause(void);
	void TimerUnpause(void);
	void SetInsideBorder(SDL_Rect *border);
	void SetInsideLine(int *line);
	bool GetInsideLine(int *line);
	bool GetOutsideLine(int *line);
};

#endif