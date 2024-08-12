// Oleg Kotov

#pragma once

#include "collisionshape.h"
#include "vec2.h"

class CircleShape : public CollisionShape
{
public:

	CircleShape( float radius )
	{
		m_radius = radius;
	}

	void setRadius( float radius )
	{
		m_radius = radius;
	}
	
	float getRadius() const
	{
		return m_radius;
	}

	CollisionShape::Type getType() const override
	{
		return CollisionShape::Type::circle;
	}

private:

	float m_radius;
};

