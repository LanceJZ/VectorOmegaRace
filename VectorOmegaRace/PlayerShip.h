#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#include "Window.h"
#include "PlayerExplosionLine.h"

class PlayerShip
{
private:
	PlayerExplosionLine *pExplosionLines[12];

	Line PlayerLines[12];
	Line NewPlayerLines[12];

	Line ThrustLines[2];
	Line NewThrustLines[2];

	Color m_ThrustColor;

	void Initialize(void);
	void MoveRotateLines(float *rotation, Vector2f *location, float *scale);

public:
	PlayerShip();
	~PlayerShip();

	void Update(float *Rotation, Vector2f *Location, float *Scale);
	void Draw(Color *color);
	void DrawThrust(void);
	void UpdateExplosion(double *frame);
	void DrawExplosion(void);
	void SetExplosion(Vector2i *Location);
	void InitializeLines(void);
};

#endif