#include "Entity.h"

bool Entity::CirclesIntersect(Vector2f *Target, float *TargetRadius)
{
	float distance = sqrt((Target->x - m_Location.x) * (Target->x - m_Location.x) + 
		(Target->y - m_Location.y) * (Target->y - m_Location.y));

	if (distance < m_Radius + *TargetRadius)
	{
		return true;
	}

	return false;
}

bool Entity::RectangleIntersect(SDL_Rect *Target)
{
	int max = m_Rectangle.x + m_Rectangle.w;
	int targetmax = Target->x + Target->w;

	bool OverlapX = ValueInRange(&Target->x, &m_Rectangle.x, &max) ||
		ValueInRange(&m_Rectangle.x, &Target->x, &targetmax);

	max = m_Rectangle.y + m_Rectangle.h;
	targetmax = Target->y + Target->h;

	bool OverlapY = ValueInRange(&Target->y, &m_Rectangle.y, &max) ||
		ValueInRange(&m_Rectangle.y, &Target->y, &targetmax);

	return OverlapX && OverlapY;
}

bool Entity::GetActive(void)
{
	return m_Active;
}

Vector2f Entity::GetLocation(void)
{
	return m_Location;
}

Vector2f Entity::GetVelocity(void)
{
	return m_Velocity;
}

float Entity::GetRadius(void)
{
	return m_Radius;
}

Rotation Entity::GetRotation(void)
{
	return m_Rotation;
}

void Entity::SetActive(bool *Active)
{
	m_Active = *Active;
}

void Entity::SetLocation(Vector2i *location)
{
	m_Location = *location;
}

void Entity::SetLocation(Vector2f *location)
{
	m_Location = *location;
}

void Entity::SetVelocity(Vector2f *velocity)
{
	m_Velocity = *velocity;
}

void Entity::SetAcceleration(Vector2f *acceleration)
{
	m_Acceleration = *acceleration;
}

void Entity::SetRotation(Rotation *rotation)
{
	m_Rotation = *rotation;
}

void Entity::SetScale(float *scale)
{
	m_Scale = *scale;
}

bool Entity::ValueInRange(int *Value, int *min, int *max)
{
	return (*Value >= *min) && (*Value <= *max);
}

bool Entity::ValueInRange(float *Value, float *min, float *max)
{
	return (*Value >= *min) && (*Value <= *max);
}

bool Entity::ValueInRange(float *Value, int *min, int *max)
{
	return ((int)*Value >= *min) && ((int)*Value <= *max);
}

Entity::Entity(void) : Common()
{
	m_Active = false;

	m_Rotation.Amount = 0;
	m_Rotation.Acceleration = 0;
	m_Rotation.Velocity = 0;
	m_Radius = 0;

	m_Location = Vector2f();
	m_Velocity = Vector2f();
	m_Acceleration = Vector2f();
}

Entity::~Entity(void)
{
}

//Protected methods
void Entity::BounceX(void)
{
	m_Velocity.x *= 0.5f;
	m_Velocity.x *= -1.0f;
	m_Acceleration = Vector2f(0, 0);
}

void Entity::BounceY(void)
{
	m_Velocity.y *= 0.5f;
	m_Velocity.y *= -1.0f;
	m_Acceleration = Vector2f(0, 0);
}

bool Entity::CheckForXEdge(void)
{
	if (m_Location.x < m_Rectangle.w * 0.5f)
		return true;

	if (m_Location.x + m_Rectangle.w * 0.5f > Window::GetWindowSize().x)
		return true;

	return false;
}

bool Entity::CheckForYEdge(void)
{
	if (m_Location.y < m_Rectangle.h * 0.5f)
		return true;

	if (m_Location.y + m_Rectangle.h * 0.5f > Window::GetWindowSize().y)
		return true;

	return false;
}

void Entity::UpdateFrame(double *Frame)
{
	double frame = *Frame;
	//Calculate movement this frame according to velocity and acceleration.
	m_Velocity += m_Acceleration;	
	m_Location += (m_Velocity * frame);
	//Calculate rotation this frame according to velocity and acceleration.
	m_Rotation.Velocity += m_Rotation.Acceleration;
	m_Rotation.Amount += (m_Rotation.Velocity * frame);
	//Update rectangle. rectangle is always centered to the entity.
	m_Rectangle.x = m_Location.x - m_Rectangle.w * 0.5f;
	m_Rectangle.y = m_Location.y - m_Rectangle.h * 0.5f;
}
