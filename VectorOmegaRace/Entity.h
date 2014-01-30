#ifndef ENTITY_H
#define ENTITY_H
#include "Common.h"

struct Rotation
{
	float Amount;
	float Velocity;
	float Acceleration;
};

class Entity : public Common
{
private:

protected:
	bool m_Active;

	Vector2f m_Location;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	SDL_Rect m_Rectangle;
	Rotation m_Rotation;

	bool CheckForXEdge(void);
	bool CheckForYEdge(void);

	float m_Radius;
	float m_Scale;

	void UpdateFrame(double *Frame);
	void BounceX(void);
	void BounceY(void);

public:
	Entity(void);
	~Entity(void);

	bool CirclesIntersect(Vector2f *Target, float *TargetRadius);
	bool RectangleIntersect(SDL_Rect *Target);
	bool ValueInRange(int *Value, int *min, int *max);
	bool ValueInRange(float *Value, float *min, float *max);
	bool ValueInRange(float *Value, int *min, int *max);
	bool GetActive(void);
	float GetRadius(void);
	Rotation GetRotation(void);
	Vector2f GetLocation(void);
	Vector2f GetVelocity(void);
	void SetActive(bool *Active);
	void SetLocation(Vector2i *location);
	void SetLocation(Vector2f *location);
	void SetVelocity(Vector2f *velocity);
	void SetAcceleration(Vector2f *acceleration);
	void SetRotation(Rotation *rotation);
	void SetScale(float *scale);
};

#endif