#include "Letter.h"

void Letter::DrawLetter(Vector2i *location, int *letter, int *size)
{
	Line LetterLine;
	int sizeIn = *size;

	if (*letter > -1 && *letter < 26)
	{
		for (int line = 0; line < 16; line++)
		{
			if (Letters[*letter].Lines[line])
			{
				LetterLine.LineStart = m_LetterLineStart[line] * sizeIn + *location;
				LetterLine.LineEnd = m_LetterLineEnd[line] * sizeIn + *location;

				Window::DrawLine(&LetterLine, &m_Color);
			}
		}
	}
}

void Letter::ProcessString(std::string *string, Vector2i *locationStart, int *size)
{
	std::string stringIn = *string;
	Vector2i locationIn = *locationStart;
	int stringlength = stringIn.size(); //length of the string.
	int space;

	for (int letter = 0; letter < stringlength; letter++)
	{
		int letterIn = (int)stringIn[letter];

		if (letterIn > 64 && letterIn < 91)
		{
			letterIn -= 65;
			DrawLetter(&Vector2i(locationIn.x + space, locationIn.y), &letterIn, size);
		}

		space += float(*size * 2.666);
	}
}

void Letter::SetColor(Color *color)
{
	m_Color = *color;
}

Letter::Letter()
{
}


Letter::~Letter()
{
}

void Letter::InitializeLetterLine(void)
{
	m_LetterLineStart[0] = Vector2i(0, 0); //1
	m_LetterLineStart[1] = Vector2i(1, 0); //2
	m_LetterLineStart[2] = Vector2i(2, 0); //3
	m_LetterLineStart[3] = Vector2i(2, 2); //4
	m_LetterLineStart[4] = Vector2i(1, 4); //5
	m_LetterLineStart[5] = Vector2i(0, 4); //6
	m_LetterLineStart[6] = Vector2i(0, 2); //7
	m_LetterLineStart[7] = Vector2i(0, 0); //8
	m_LetterLineStart[8] = Vector2i(0, 0); //9
	m_LetterLineStart[9] = Vector2i(2, 0); //10
	m_LetterLineStart[10] = Vector2i(1, 2); //11
	m_LetterLineStart[11] = Vector2i(1, 2); //12
	m_LetterLineStart[12] = Vector2i(1, 2); //13
	m_LetterLineStart[13] = Vector2i(0, 2); //14
	m_LetterLineStart[14] = Vector2i(1, 0); //15
	m_LetterLineStart[15] = Vector2i(1, 2); //16

	m_LetterLineEnd[0] = Vector2i(1, 0); //1
	m_LetterLineEnd[1] = Vector2i(2, 0); //2
	m_LetterLineEnd[2] = Vector2i(2, 2); //3
	m_LetterLineEnd[3] = Vector2i(2, 4); //4
	m_LetterLineEnd[4] = Vector2i(2, 4); //5
	m_LetterLineEnd[5] = Vector2i(1, 4); //6
	m_LetterLineEnd[6] = Vector2i(0, 4); //7
	m_LetterLineEnd[7] = Vector2i(0, 2); //8
	m_LetterLineEnd[8] = Vector2i(1, 2); //9
	m_LetterLineEnd[9] = Vector2i(1, 2); //10
	m_LetterLineEnd[10] = Vector2i(2, 2); //11
	m_LetterLineEnd[11] = Vector2i(2, 4); //12
	m_LetterLineEnd[12] = Vector2i(0, 4); //13
	m_LetterLineEnd[13] = Vector2i(1, 2); //14
	m_LetterLineEnd[14] = Vector2i(1, 2); //15
	m_LetterLineEnd[15] = Vector2i(1, 4); //16

	// A
	Letters[0].Lines[0] = true;
	Letters[0].Lines[1] = true;
	Letters[0].Lines[2] = true;
	Letters[0].Lines[3] = true;
	Letters[0].Lines[4] = false;
	Letters[0].Lines[5] = false;
	Letters[0].Lines[6] = true;
	Letters[0].Lines[7] = true;
	Letters[0].Lines[8] = false;
	Letters[0].Lines[9] = false;
	Letters[0].Lines[10] = true;
	Letters[0].Lines[11] = false;
	Letters[0].Lines[12] = false;
	Letters[0].Lines[13] = true;
	Letters[0].Lines[14] = false;
	Letters[0].Lines[15] = false;
	// B
	Letters[1].Lines[0] = true;
	Letters[1].Lines[1] = true;
	Letters[1].Lines[2] = true;
	Letters[1].Lines[3] = true;
	Letters[1].Lines[4] = true;
	Letters[1].Lines[5] = true;
	Letters[1].Lines[6] = false;
	Letters[1].Lines[7] = false;
	Letters[1].Lines[8] = false;
	Letters[1].Lines[9] = false;
	Letters[1].Lines[10] = true;
	Letters[1].Lines[11] = false;
	Letters[1].Lines[12] = false;
	Letters[1].Lines[13] = false;
	Letters[1].Lines[14] = true;
	Letters[1].Lines[15] = true;
	// C
	Letters[2].Lines[0] = true;
	Letters[2].Lines[1] = true;
	Letters[2].Lines[2] = false;
	Letters[2].Lines[3] = false;
	Letters[2].Lines[4] = true;
	Letters[2].Lines[5] = true;
	Letters[2].Lines[6] = true;
	Letters[2].Lines[7] = true;
	Letters[2].Lines[8] = false;
	Letters[2].Lines[9] = false;
	Letters[2].Lines[10] = false;
	Letters[2].Lines[11] = false;
	Letters[2].Lines[12] = false;
	Letters[2].Lines[13] = false;
	Letters[2].Lines[14] = false;
	Letters[2].Lines[15] = false;
	// D
	Letters[3].Lines[0] = true;
	Letters[3].Lines[1] = true;
	Letters[3].Lines[2] = true;
	Letters[3].Lines[3] = true;
	Letters[3].Lines[4] = true;
	Letters[3].Lines[5] = true;
	Letters[3].Lines[6] = false;
	Letters[3].Lines[7] = false;
	Letters[3].Lines[8] = false;
	Letters[3].Lines[9] = false;
	Letters[3].Lines[10] = false;
	Letters[3].Lines[11] = false;
	Letters[3].Lines[12] = false;
	Letters[3].Lines[13] = false;
	Letters[3].Lines[14] = true;
	Letters[3].Lines[15] = true;
	// E
	Letters[4].Lines[0] = true;
	Letters[4].Lines[1] = true;
	Letters[4].Lines[2] = false;
	Letters[4].Lines[3] = false;
	Letters[4].Lines[4] = true;
	Letters[4].Lines[5] = true;
	Letters[4].Lines[6] = true;
	Letters[4].Lines[7] = true;
	Letters[4].Lines[8] = false;
	Letters[4].Lines[9] = false;
	Letters[4].Lines[10] = false;
	Letters[4].Lines[11] = false;
	Letters[4].Lines[12] = false;
	Letters[4].Lines[13] = true;
	Letters[4].Lines[14] = false;
	Letters[4].Lines[15] = false;
	// F
	Letters[5].Lines[0] = true;
	Letters[5].Lines[1] = true;
	Letters[5].Lines[2] = false;
	Letters[5].Lines[3] = false;
	Letters[5].Lines[4] = false;
	Letters[5].Lines[5] = false;
	Letters[5].Lines[6] = true;
	Letters[5].Lines[7] = true;
	Letters[5].Lines[8] = false;
	Letters[5].Lines[9] = false;
	Letters[5].Lines[10] = false;
	Letters[5].Lines[11] = false;
	Letters[5].Lines[12] = false;
	Letters[5].Lines[13] = true;
	Letters[5].Lines[14] = false;
	Letters[5].Lines[15] = false;
	// G
	Letters[6].Lines[0] = true;
	Letters[6].Lines[1] = true;
	Letters[6].Lines[2] = false;
	Letters[6].Lines[3] = true;
	Letters[6].Lines[4] = true;
	Letters[6].Lines[5] = true;
	Letters[6].Lines[6] = true;
	Letters[6].Lines[7] = true;
	Letters[6].Lines[8] = false;
	Letters[6].Lines[9] = false;
	Letters[6].Lines[10] = true;
	Letters[6].Lines[11] = false;
	Letters[6].Lines[12] = false;
	Letters[6].Lines[13] = false;
	Letters[6].Lines[14] = false;
	Letters[6].Lines[15] = false;
	// H
	Letters[7].Lines[0] = false;
	Letters[7].Lines[1] = false;
	Letters[7].Lines[2] = true;
	Letters[7].Lines[3] = true;
	Letters[7].Lines[4] = false;
	Letters[7].Lines[5] = false;
	Letters[7].Lines[6] = true;
	Letters[7].Lines[7] = true;
	Letters[7].Lines[8] = false;
	Letters[7].Lines[9] = false;
	Letters[7].Lines[10] = true;
	Letters[7].Lines[11] = false;
	Letters[7].Lines[12] = false;
	Letters[7].Lines[13] = true;
	Letters[7].Lines[14] = false;
	Letters[7].Lines[15] = false;
	// I
	Letters[8].Lines[0] = true;
	Letters[8].Lines[1] = true;
	Letters[8].Lines[2] = false;
	Letters[8].Lines[3] = false;
	Letters[8].Lines[4] = true;
	Letters[8].Lines[5] = true;
	Letters[8].Lines[6] = false;
	Letters[8].Lines[7] = false;
	Letters[8].Lines[8] = false;
	Letters[8].Lines[9] = false;
	Letters[8].Lines[10] = false;
	Letters[8].Lines[11] = false;
	Letters[8].Lines[12] = false;
	Letters[8].Lines[13] = false;
	Letters[8].Lines[14] = true;
	Letters[8].Lines[15] = true;
	// J
	Letters[9].Lines[0] = false;
	Letters[9].Lines[1] = true;
	Letters[9].Lines[2] = true;
	Letters[9].Lines[3] = true;
	Letters[9].Lines[4] = true;
	Letters[9].Lines[5] = true;
	Letters[9].Lines[6] = true;
	Letters[9].Lines[7] = false;
	Letters[9].Lines[8] = false;
	Letters[9].Lines[9] = false;
	Letters[9].Lines[10] = false;
	Letters[9].Lines[11] = false;
	Letters[9].Lines[12] = false;
	Letters[9].Lines[13] = false;
	Letters[9].Lines[14] = false;
	Letters[9].Lines[15] = false;
	// K
	Letters[10].Lines[0] = false;
	Letters[10].Lines[1] = false;
	Letters[10].Lines[2] = false;
	Letters[10].Lines[3] = false;
	Letters[10].Lines[4] = false;
	Letters[10].Lines[5] = false;
	Letters[10].Lines[6] = true;
	Letters[10].Lines[7] = true;
	Letters[10].Lines[8] = false;
	Letters[10].Lines[9] = true;
	Letters[10].Lines[10] = false;
	Letters[10].Lines[11] = true;
	Letters[10].Lines[12] = false;
	Letters[10].Lines[13] = true;
	Letters[10].Lines[14] = false;
	Letters[10].Lines[15] = false;
	// L
	Letters[11].Lines[0] = false;
	Letters[11].Lines[1] = false;
	Letters[11].Lines[2] = false;
	Letters[11].Lines[3] = false;
	Letters[11].Lines[4] = true;
	Letters[11].Lines[5] = true;
	Letters[11].Lines[6] = true;
	Letters[11].Lines[7] = true;
	Letters[11].Lines[8] = false;
	Letters[11].Lines[9] = false;
	Letters[11].Lines[10] = false;
	Letters[11].Lines[11] = false;
	Letters[11].Lines[12] = false;
	Letters[11].Lines[13] = false;
	Letters[11].Lines[14] = false;
	Letters[11].Lines[15] = false;
	// M
	Letters[12].Lines[0] = false;
	Letters[12].Lines[1] = false;
	Letters[12].Lines[2] = true;
	Letters[12].Lines[3] = true;
	Letters[12].Lines[4] = false;
	Letters[12].Lines[5] = false;
	Letters[12].Lines[6] = true;
	Letters[12].Lines[7] = true;
	Letters[12].Lines[8] = true;
	Letters[12].Lines[9] = true;
	Letters[12].Lines[10] = false;
	Letters[12].Lines[11] = false;
	Letters[12].Lines[12] = false;
	Letters[12].Lines[13] = false;
	Letters[12].Lines[14] = false;
	Letters[12].Lines[15] = false;
	// N
	Letters[13].Lines[0] = false;
	Letters[13].Lines[1] = false;
	Letters[13].Lines[2] = true;
	Letters[13].Lines[3] = true;
	Letters[13].Lines[4] = false;
	Letters[13].Lines[5] = false;
	Letters[13].Lines[6] = true;
	Letters[13].Lines[7] = true;
	Letters[13].Lines[8] = true;
	Letters[13].Lines[9] = false;
	Letters[13].Lines[10] = false;
	Letters[13].Lines[11] = true;
	Letters[13].Lines[12] = false;
	Letters[13].Lines[13] = false;
	Letters[13].Lines[14] = false;
	Letters[13].Lines[15] = false;
	// O
	Letters[14].Lines[0] = true;
	Letters[14].Lines[1] = true;
	Letters[14].Lines[2] = true;
	Letters[14].Lines[3] = true;
	Letters[14].Lines[4] = true;
	Letters[14].Lines[5] = true;
	Letters[14].Lines[6] = true;
	Letters[14].Lines[7] = true;
	Letters[14].Lines[8] = false;
	Letters[14].Lines[9] = false;
	Letters[14].Lines[10] = false;
	Letters[14].Lines[11] = false;
	Letters[14].Lines[12] = false;
	Letters[14].Lines[13] = false;
	Letters[14].Lines[14] = false;
	Letters[14].Lines[15] = false;
	// P
	Letters[15].Lines[0] = true;
	Letters[15].Lines[1] = true;
	Letters[15].Lines[2] = true;
	Letters[15].Lines[3] = false;
	Letters[15].Lines[4] = false;
	Letters[15].Lines[5] = false;
	Letters[15].Lines[6] = true;
	Letters[15].Lines[7] = true;
	Letters[15].Lines[8] = false;
	Letters[15].Lines[9] = false;
	Letters[15].Lines[10] = true;
	Letters[15].Lines[11] = false;
	Letters[15].Lines[12] = false;
	Letters[15].Lines[13] = true;
	Letters[15].Lines[14] = false;
	Letters[15].Lines[15] = false;
	// Q
	Letters[16].Lines[0] = true;
	Letters[16].Lines[1] = true;
	Letters[16].Lines[2] = true;
	Letters[16].Lines[3] = true;
	Letters[16].Lines[4] = true;
	Letters[16].Lines[5] = true;
	Letters[16].Lines[6] = true;
	Letters[16].Lines[7] = true;
	Letters[16].Lines[8] = false;
	Letters[16].Lines[9] = false;
	Letters[16].Lines[10] = false;
	Letters[16].Lines[11] = true;
	Letters[16].Lines[12] = false;
	Letters[16].Lines[13] = false;
	Letters[16].Lines[14] = false;
	Letters[16].Lines[15] = false;
	// R
	Letters[17].Lines[0] = true;
	Letters[17].Lines[1] = true;
	Letters[17].Lines[2] = true;
	Letters[17].Lines[3] = false;
	Letters[17].Lines[4] = false;
	Letters[17].Lines[5] = false;
	Letters[17].Lines[6] = true;
	Letters[17].Lines[7] = true;
	Letters[17].Lines[8] = false;
	Letters[17].Lines[9] = false;
	Letters[17].Lines[10] = true;
	Letters[17].Lines[11] = true;
	Letters[17].Lines[12] = false;
	Letters[17].Lines[13] = true;
	Letters[17].Lines[14] = false;
	Letters[17].Lines[15] = false;
	// S
	Letters[18].Lines[0] = true;
	Letters[18].Lines[1] = true;
	Letters[18].Lines[2] = false;
	Letters[18].Lines[3] = true;
	Letters[18].Lines[4] = true;
	Letters[18].Lines[5] = true;
	Letters[18].Lines[6] = false;
	Letters[18].Lines[7] = true;
	Letters[18].Lines[8] = false;
	Letters[18].Lines[9] = false;
	Letters[18].Lines[10] = true;
	Letters[18].Lines[11] = false;
	Letters[18].Lines[12] = false;
	Letters[18].Lines[13] = true;
	Letters[18].Lines[14] = false;
	Letters[18].Lines[15] = false;
	// T
	Letters[19].Lines[0] = true;
	Letters[19].Lines[1] = true;
	Letters[19].Lines[2] = false;
	Letters[19].Lines[3] = false;
	Letters[19].Lines[4] = false;
	Letters[19].Lines[5] = false;
	Letters[19].Lines[6] = false;
	Letters[19].Lines[7] = false;
	Letters[19].Lines[8] = false;
	Letters[19].Lines[9] = false;
	Letters[19].Lines[10] = false;
	Letters[19].Lines[11] = false;
	Letters[19].Lines[12] = false;
	Letters[19].Lines[13] = false;
	Letters[19].Lines[14] = true;
	Letters[19].Lines[15] = true;
	// U
	Letters[20].Lines[0] = false;
	Letters[20].Lines[1] = false;
	Letters[20].Lines[2] = true;
	Letters[20].Lines[3] = true;
	Letters[20].Lines[4] = true;
	Letters[20].Lines[5] = true;
	Letters[20].Lines[6] = true;
	Letters[20].Lines[7] = true;
	Letters[20].Lines[8] = false;
	Letters[20].Lines[9] = false;
	Letters[20].Lines[10] = false;
	Letters[20].Lines[11] = false;
	Letters[20].Lines[12] = false;
	Letters[20].Lines[13] = false;
	Letters[20].Lines[14] = false;
	Letters[20].Lines[15] = false;
	// V
	Letters[21].Lines[0] = false;
	Letters[21].Lines[1] = false;
	Letters[21].Lines[2] = false;
	Letters[21].Lines[3] = false;
	Letters[21].Lines[4] = false;
	Letters[21].Lines[5] = false;
	Letters[21].Lines[6] = true;
	Letters[21].Lines[7] = true;
	Letters[21].Lines[8] = false;
	Letters[21].Lines[9] = true;
	Letters[21].Lines[10] = false;
	Letters[21].Lines[11] = false;
	Letters[21].Lines[12] = true;
	Letters[21].Lines[13] = false;
	Letters[21].Lines[14] = false;
	Letters[21].Lines[15] = false;
	// W
	Letters[22].Lines[0] = false;
	Letters[22].Lines[1] = false;
	Letters[22].Lines[2] = true;
	Letters[22].Lines[3] = true;
	Letters[22].Lines[4] = false;
	Letters[22].Lines[5] = false;
	Letters[22].Lines[6] = true;
	Letters[22].Lines[7] = true;
	Letters[22].Lines[8] = false;
	Letters[22].Lines[9] = false;
	Letters[22].Lines[10] = false;
	Letters[22].Lines[11] = true;
	Letters[22].Lines[12] = true;
	Letters[22].Lines[13] = false;
	Letters[22].Lines[14] = false;
	Letters[22].Lines[15] = false;
	// X
	Letters[23].Lines[0] = false;
	Letters[23].Lines[1] = false;
	Letters[23].Lines[2] = false;
	Letters[23].Lines[3] = false;
	Letters[23].Lines[4] = false;
	Letters[23].Lines[5] = false;
	Letters[23].Lines[6] = false;
	Letters[23].Lines[7] = false;
	Letters[23].Lines[8] = true;
	Letters[23].Lines[9] = true;
	Letters[23].Lines[10] = false;
	Letters[23].Lines[11] = true;
	Letters[23].Lines[12] = true;
	Letters[23].Lines[13] = false;
	Letters[23].Lines[14] = false;
	Letters[23].Lines[15] = false;
	// Y
	Letters[24].Lines[0] = false;
	Letters[24].Lines[1] = false;
	Letters[24].Lines[2] = false;
	Letters[24].Lines[3] = false;
	Letters[24].Lines[4] = false;
	Letters[24].Lines[5] = false;
	Letters[24].Lines[6] = false;
	Letters[24].Lines[7] = false;
	Letters[24].Lines[8] = true;
	Letters[24].Lines[9] = true;
	Letters[24].Lines[10] = false;
	Letters[24].Lines[11] = false;
	Letters[24].Lines[12] = false;
	Letters[24].Lines[13] = false;
	Letters[24].Lines[14] = false;
	Letters[24].Lines[15] = true;
	// Z
	Letters[25].Lines[0] = true;
	Letters[25].Lines[1] = true;
	Letters[25].Lines[2] = false;
	Letters[25].Lines[3] = false;
	Letters[25].Lines[4] = true;
	Letters[25].Lines[5] = true;
	Letters[25].Lines[6] = false;
	Letters[25].Lines[7] = false;
	Letters[25].Lines[8] = false;
	Letters[25].Lines[9] = true;
	Letters[25].Lines[10] = false;
	Letters[25].Lines[11] = false;
	Letters[25].Lines[12] = true;
	Letters[25].Lines[13] = false;
	Letters[25].Lines[14] = false;
	Letters[25].Lines[15] = false;
}
