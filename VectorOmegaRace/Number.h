#ifndef NUMBER_H
#define NUMBER_H
#include "Common.h"

struct NumberData
{
	bool Lines[7];
};


class Number
{
private:
	Color m_Color;
	// Number lines
	NumberData Numbers[10];
	Vector2i m_NumberLineStart[7];
	Vector2i m_NumberLineEnd[7];

public:
	Number();
	~Number();

	void InitializeNumberLine(void);
	void ProcessNumber(int *number, Vector2i *locationStart, int *size);
	void DrawDigit(Vector2i *location, int *digit, int *size);
};

#endif