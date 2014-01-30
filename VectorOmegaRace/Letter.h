#ifndef LETTER_H
#define LETTER_H
#include "Common.h"

struct LetterData
{
	bool Lines[16];
};

class Letter
{
private:
	Color m_Color;
	// Letter Lines
	LetterData Letters[26];
	Vector2i m_LetterLineStart[16];
	Vector2i m_LetterLineEnd[16];

public:
	Letter();
	~Letter();

	void InitializeLetterLine(void);
	void ProcessString(std::string *string, Vector2i *locationStart, int *size);
	void DrawLetter(Vector2i *location, int *letter, int *size);
	void SetColor(Color *color);
};

#endif