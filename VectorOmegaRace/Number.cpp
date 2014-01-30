#include "Number.h"

void Number::ProcessNumber(int *number, Vector2i *locationStart, int *size)
{
	int space = 0;
	int sizeIn = *size;
	int numberIn = *number;
	Vector2i locationIn = *locationStart;

	do
	{
		//Make digit the modulus of 10 from number.
		int digit = numberIn % 10;
		//This sends a digit to the draw function with the location and size.
		DrawDigit(&Vector2i(locationIn.x - space, locationIn.y), &digit, size);
		// Dividing the int by 10, we discard the digit that was derived from the modulus operation.
		numberIn /= 10;
		// Move the location for the next digit location to the left. We start on the right hand side with the lowest digit.
		space += sizeIn * 2;
	} while (numberIn > 0);
}

void Number::DrawDigit(Vector2i *location, int *digit, int *size)
{
	Line NumberLine;
	int sizeIn = *size;

	if (*digit > -1 && *digit < 10)
	{
		for (int line = 0; line < 7; line++)
		{
			if (Numbers[*digit].Lines[line])
			{
				NumberLine.LineStart = m_NumberLineStart[line] * sizeIn + *location;
				NumberLine.LineEnd = m_NumberLineEnd[line] * sizeIn + *location;

				Window::DrawLine(&NumberLine, &m_Color);
			}
		}
	}
}

Number::Number()
{
}


Number::~Number()
{
}

void Number::InitializeNumberLine(void)
{
	//Color of letters and numbers.
	m_Color.Red = 165;
	m_Color.Green = 165;
	m_Color.Blue = 255;
	m_Color.Alpha = 255;
	// LED Grid location of line start and end points. 0, 0 is the top left corner.
	m_NumberLineStart[0] = Vector2i(0, 0);
	m_NumberLineStart[1] = Vector2i(1, 0);
	m_NumberLineStart[2] = Vector2i(1, 1);
	m_NumberLineStart[3] = Vector2i(0, 2);
	m_NumberLineStart[4] = Vector2i(0, 1);
	m_NumberLineStart[5] = Vector2i(0, 0);
	m_NumberLineStart[6] = Vector2i(0, 1);

	m_NumberLineEnd[0] = Vector2i(1, 0);
	m_NumberLineEnd[1] = Vector2i(1, 1);
	m_NumberLineEnd[2] = Vector2i(1, 2);
	m_NumberLineEnd[3] = Vector2i(1, 2);
	m_NumberLineEnd[4] = Vector2i(0, 2);
	m_NumberLineEnd[5] = Vector2i(0, 1);
	m_NumberLineEnd[6] = Vector2i(1, 1);

	// LED Grid, what lines are on for each number.
	// Line 0 is the top line.
	// Line 1 is upper right side line.
	// Line 2 is lower right side line.
	// Line 3 is bottom line.
	// Line 4 is lower left side line.
	// Line 5 is upper left side line.
	// Line 6 is the middle line.

	Numbers[0].Lines[0] = true;
	Numbers[0].Lines[1] = true;
	Numbers[0].Lines[2] = true;
	Numbers[0].Lines[3] = true;
	Numbers[0].Lines[4] = true;
	Numbers[0].Lines[5] = true;
	Numbers[0].Lines[6] = false;

	Numbers[1].Lines[0] = false;
	Numbers[1].Lines[1] = true;
	Numbers[1].Lines[2] = true;
	Numbers[1].Lines[3] = false;
	Numbers[1].Lines[4] = false;
	Numbers[1].Lines[5] = false;
	Numbers[1].Lines[6] = false;

	Numbers[2].Lines[0] = true;
	Numbers[2].Lines[1] = true;
	Numbers[2].Lines[2] = false;
	Numbers[2].Lines[3] = true;
	Numbers[2].Lines[4] = true;
	Numbers[2].Lines[5] = false;
	Numbers[2].Lines[6] = true;

	Numbers[3].Lines[0] = true;
	Numbers[3].Lines[1] = true;
	Numbers[3].Lines[2] = true;
	Numbers[3].Lines[3] = true;
	Numbers[3].Lines[4] = false;
	Numbers[3].Lines[5] = false;
	Numbers[3].Lines[6] = true;

	Numbers[4].Lines[0] = false;
	Numbers[4].Lines[1] = true;
	Numbers[4].Lines[2] = true;
	Numbers[4].Lines[3] = false;
	Numbers[4].Lines[4] = false;
	Numbers[4].Lines[5] = true;
	Numbers[4].Lines[6] = true;

	Numbers[5].Lines[0] = true;
	Numbers[5].Lines[1] = false;
	Numbers[5].Lines[2] = true;
	Numbers[5].Lines[3] = true;
	Numbers[5].Lines[4] = false;
	Numbers[5].Lines[5] = true;
	Numbers[5].Lines[6] = true;

	Numbers[6].Lines[0] = true;
	Numbers[6].Lines[1] = false;
	Numbers[6].Lines[2] = true;
	Numbers[6].Lines[3] = true;
	Numbers[6].Lines[4] = true;
	Numbers[6].Lines[5] = true;
	Numbers[6].Lines[6] = true;

	Numbers[7].Lines[0] = true;
	Numbers[7].Lines[1] = true;
	Numbers[7].Lines[2] = true;
	Numbers[7].Lines[3] = false;
	Numbers[7].Lines[4] = false;
	Numbers[7].Lines[5] = false;
	Numbers[7].Lines[6] = false;

	Numbers[8].Lines[0] = true;
	Numbers[8].Lines[1] = true;
	Numbers[8].Lines[2] = true;
	Numbers[8].Lines[3] = true;
	Numbers[8].Lines[4] = true;
	Numbers[8].Lines[5] = true;
	Numbers[8].Lines[6] = true;

	Numbers[9].Lines[0] = true;
	Numbers[9].Lines[1] = true;
	Numbers[9].Lines[2] = true;
	Numbers[9].Lines[3] = false;
	Numbers[9].Lines[4] = false;
	Numbers[9].Lines[5] = true;
	Numbers[9].Lines[6] = true;
}
