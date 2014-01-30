#ifndef COMMON_H
#define COMMON_H
#include "Window.h"

class Common
{
protected:
	Vector2i RandomLocation(void);
	int GetRandomX(void);
	int GetRandomY(void);
	bool True = true;
	bool False = false;
	const float PiTimesTwo = 6.2831853f;
	const float Pi = 3.1415927f;

public:
	Common();
	~Common();
};

#endif