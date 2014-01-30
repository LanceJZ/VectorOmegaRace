#include "Borders.h"

void Borders::Update(void)
{
	for (int line = 0; line < 4; line++)
	{
		if (pTimer->Seconds() > InsideLineTimers[line])
			InsideLineOn[line] = false;
	}

	for (int line = 0; line < 8; line++)
	{
		if (pTimer->Seconds() > OutsideLineTimers[line])
			OutsideLineOn[line] = false;
	}
}

void Borders::Draw(void)
{
	Window::DrawRect(&InsideBorder, &BorderColor);

	for (int dot = 0; dot < 8; dot++)
	{
		Window::DrawPoint(&InsideDots[dot], &LineColor);
	}

	for (int line = 0; line < 4; line++)
	{
		if (InsideLineOn[line])
			Window::DrawLine(&InsideFieldLines[line], &LineColor);
	}

	for (int line = 0; line < 8; line++)
	{
		if (OutsideLineOn[line])
			Window::DrawLine(&OutsideFieldLines[line], &LineColor);

		Window::DrawPoint(&OutsideDots[line], &LineColor);
	}
}

void Borders::SetInsideLineHit(int *line)
{
	InsideLineOn[*line] = true;
	InsideLineTimers[*line] = pTimer->Seconds() + 0.1f;
}

void Borders::SetOutsideLineHit(int *line)
{
	OutsideLineOn[*line] = true;
	OutsideLineTimers[*line] = pTimer->Seconds() + 0.1f;
}

SDL_Rect Borders::GetInsideBorder(void)
{
	return InsideBorder;
}

Borders::Borders()
{
	pTimer = new Timer();
}


Borders::~Borders()
{
	delete pTimer;
}

void Borders::Initialize(void)
{
	pTimer->Start();

	LineColor.Red = 150;
	LineColor.Green = 150;
	LineColor.Blue = 255;
	LineColor.Alpha = 255;

	BorderColor.Red = 50;
	BorderColor.Green = 10;
	BorderColor.Blue = 150;
	BorderColor.Alpha = 50;

	int InsideWidth = Window::GetWindowSize().x * 0.666;
	int InsideHight = Window::GetWindowSize().y * 0.25;	
	int InsideLeft = Window::GetWindowSize().x / 2 - InsideWidth / 2;
	int InsideRight = Window::GetWindowSize().x / 2 + InsideWidth / 2;
	int InsideTop = Window::GetWindowSize().y / 2 - InsideHight / 2;
	int InsideBottom = Window::GetWindowSize().y / 2 + InsideHight / 2;

	InsideBorder.x = InsideLeft;
	InsideBorder.y = InsideTop;
	InsideBorder.h = InsideHight;
	InsideBorder.w = InsideWidth;

	InsideDots[0] = Vector2i(InsideLeft + (InsideLeft / 10), InsideTop);
	InsideDots[1] = Vector2i(InsideRight - (InsideLeft / 10), InsideTop);
	InsideDots[2] = Vector2i(InsideRight, InsideTop + (InsideLeft / 10));
	InsideDots[3] = Vector2i(InsideRight, InsideBottom - (InsideLeft / 10));
	InsideDots[4] = Vector2i(InsideRight - (InsideLeft / 10), InsideBottom);
	InsideDots[5] = Vector2i(InsideLeft + (InsideLeft / 10), InsideBottom);
	InsideDots[6] = Vector2i(InsideLeft, InsideBottom - (InsideLeft / 10));
	InsideDots[7] = Vector2i(InsideLeft, InsideTop + (InsideLeft / 10));

	InsideFieldLines[0].LineStart = Vector2i(InsideLeft, InsideTop);
	InsideFieldLines[1].LineStart = Vector2i(InsideRight, InsideTop);
	InsideFieldLines[2].LineStart = Vector2i(InsideRight, InsideBottom);
	InsideFieldLines[3].LineStart = Vector2i(InsideLeft, InsideBottom);

	InsideFieldLines[0].LineEnd = Vector2i(InsideRight, InsideTop);
	InsideFieldLines[1].LineEnd = Vector2i(InsideRight, InsideBottom);
	InsideFieldLines[2].LineEnd = Vector2i(InsideLeft, InsideBottom);
	InsideFieldLines[3].LineEnd = Vector2i(InsideLeft, InsideTop);

	OutsideFieldLines[0].LineStart = Vector2i(5, 5);
	OutsideFieldLines[1].LineStart = Vector2i(Window::GetWindowSize().x / 2, 5);
	OutsideFieldLines[2].LineStart = Vector2i(5, Window::GetWindowSize().y - 5);
	OutsideFieldLines[3].LineStart = Vector2i(Window::GetWindowSize().x / 2, Window::GetWindowSize().y - 5);
	OutsideFieldLines[4].LineStart = Vector2i(OutsideFieldLines[0].LineStart);
	OutsideFieldLines[5].LineStart = Vector2i(5, Window::GetWindowSize().y / 2);
	OutsideFieldLines[6].LineStart = Vector2i(Window::GetWindowSize().x - 5, 5);
	OutsideFieldLines[7].LineStart = Vector2i(Window::GetWindowSize().x - 5, Window::GetWindowSize().y / 2);

	OutsideFieldLines[0].LineEnd = Vector2i(OutsideFieldLines[1].LineStart);
	OutsideFieldLines[1].LineEnd = Vector2i(OutsideFieldLines[6].LineStart);
	OutsideFieldLines[2].LineEnd = Vector2i(OutsideFieldLines[3].LineStart);
	OutsideFieldLines[3].LineEnd = Vector2i(Window::GetWindowSize().x - 5, Window::GetWindowSize().y - 5);
	OutsideFieldLines[4].LineEnd = Vector2i(OutsideFieldLines[5].LineStart);
	OutsideFieldLines[5].LineEnd = Vector2i(OutsideFieldLines[2].LineStart);
	OutsideFieldLines[6].LineEnd = Vector2i(OutsideFieldLines[7].LineStart);
	OutsideFieldLines[7].LineEnd = Vector2i(Window::GetWindowSize().x - 5, Window::GetWindowSize().y - 5);

	OutsideDots[0] = OutsideFieldLines[0].LineStart;
	OutsideDots[1] = OutsideFieldLines[1].LineStart;
	OutsideDots[2] = OutsideFieldLines[2].LineStart;
	OutsideDots[3] = OutsideFieldLines[7].LineStart;
	OutsideDots[4] = OutsideFieldLines[7].LineEnd;
	OutsideDots[5] = OutsideFieldLines[3].LineStart;
	OutsideDots[6] = OutsideFieldLines[5].LineStart;
	OutsideDots[7] = OutsideFieldLines[6].LineStart;
}