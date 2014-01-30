#ifndef BORDERS_H
#define BORDERS_H
#include "Window.h"
#include "Timer.h"

class Borders
{
private:
	Timer *pTimer;

	Line InsideFieldLines[4];
	Line OutsideFieldLines[8];
	Vector2i InsideDots[8];
	Vector2i OutsideDots[8];
	SDL_Rect InsideBorder;
	Color LineColor;
	Color BorderColor;
	double InsideLineTimers[4];
	double OutsideLineTimers[8];
	bool InsideLineOn[4];
	bool OutsideLineOn[8];

public:
	Borders();
	~Borders();

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void SetInsideLineHit(int *line);
	void SetOutsideLineHit(int *line);
	SDL_Rect GetInsideBorder(void);
};

#endif