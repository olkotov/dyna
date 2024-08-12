// Oleg Kotov

#pragma once

#include <math.h>

class Vec2
{
public:

	Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vec2( float x, float y )
	{
		this->x = x;
		this->y = y;
	}

	Vec2 operator-()
	{
		return Vec2( -x, -y );
	}

	Vec2 operator+( const Vec2& vec ) const
	{
		Vec2 result;

		result.x = x + vec.x;
		result.y = y + vec.y;

		return result;
	}

	Vec2 operator+=( const Vec2& other )
	{
		*this = *this + other;
		return *this;
	}

	Vec2 operator-( const Vec2& vec ) const
	{
		Vec2 result;

		result.x = x - vec.x;
		result.y = y - vec.y;

		return result;
	}

	Vec2 operator-=( const Vec2& other )
	{
		*this = *this - other;
		return *this;
	}

	Vec2 operator*( const float scale ) const
	{
		return Vec2( x * scale, y * scale );
	}

	Vec2 operator*=( const float scale )
	{
		*this = *this * scale;
		return *this;
	}

	// use ( vec2 * inverse ) instead
	Vec2 operator/( const float scale ) const
	{
		return Vec2( x / scale, y / scale );
	}

	Vec2 operator/=( const float scale )
	{
		*this = *this / scale;
		return *this;
	}

public:

	Vec2 normalize()
	{
		float lengthSq = lengthSquared();

		if ( lengthSq > 0.0f )
		{
			float invLength = 1.0f / sqrtf( lengthSq );
        
			x *= invLength;
			y *= invLength;
		}

		return *this;
	}

	float lengthSquared() const
	{
		return x * x + y * y;
	}

	float dot( const Vec2& vec ) const
	{
		return ( x * vec.x ) + ( y * vec.y );
	}

	static Vec2 rotate( const Vec2& vector, float angle )
	{
		float cosAngle = cosf( angle );
		float sinAngle = sinf( angle );

		Vec2 rotatedVector;
		rotatedVector.x = vector.x * cosAngle - vector.y * sinAngle;
		rotatedVector.y = vector.x * sinAngle + vector.y * cosAngle;

		return rotatedVector;
	}

public:

	float x;
	float y;

public:

	// static Vec2 Right;
};

