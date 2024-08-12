// Oleg Kotov

#pragma once

#include "vec2.h"

struct Manifold
{
	class CollisionShape* body0 = nullptr;
	class CollisionShape* body1 = nullptr;
	float penetration;
	Vec2 normal;
};

