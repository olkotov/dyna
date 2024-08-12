// Oleg Kotov

#pragma once

#include "collisionshape.h"
#include "vec2.h"

class BoxShape : public CollisionShape
{
public:

	BoxShape( const Vec2& halfExtents )
		: m_halfExtents( halfExtents )
	{}

	void setHalfExtents( const Vec2& halfExtents )
	{
		m_halfExtents = halfExtents;
	}

	const Vec2& getHalfExtents() const
	{
		return m_halfExtents;
	}

	CollisionShape::Type getType() const override
	{
		return CollisionShape::Type::box;
	}

private:

	Vec2 m_halfExtents;
};

