// Oleg Kotov

#pragma once

#include "vec2.h"
#include "collisionshape.h"

#include <vector>
#include <assert.h>
#include <stdint.h>

class RigidBody
{
public:

	enum class MotionType : uint8_t
	{
		stationary,
		kinematic, // keyframed, animated
		dynamic
	};

	RigidBody( CollisionShape* shape )
		: m_shape( shape )
		, m_worldArrayIndex( -1 )
		, m_isActive( true )
		, m_position{ 0.0f, 0.0f }
		, m_orientation( 0.0f )
		, m_linearVelocity{ 0.0f, 0.0f }
		, m_angularVelocity( 0.0f )
		, m_mass( 1.0f )
		, m_invMass( 1.0f )
		, m_momentOfInertia( 0.0f )
		, m_invMomentOfInertia( 0.0f )
		, m_friction( 0.0f )
		, m_restitution( 0.0f )
		, m_torque( 0.0f )
		, m_gravityScale( 1.0f )
		, m_userdata( nullptr )
	{
		if ( shape )
		{
			shape->setRigidBody( this );
		}
	}

	void setPosition( const Vec2& position )
	{
		m_position = position;
	}

	const Vec2& getPosition() const
	{
		return m_position;
	}

	void setOrientation( float orientation )
	{
		m_orientation = orientation;
	}

	float getOrientationDeg() const
	{
		return m_orientation;
	}

	float getOrientationRad() const
	{
		return m_orientation * 3.14f / 180.0f;
	}

	void setLinearAcceleration( const Vec2& acceleration )
	{
		m_linearAcceleration = acceleration;
	}

	const Vec2& getLinearAcceleration() const
	{
		return m_linearAcceleration;
	}

	void setLinearVelocity( const Vec2& linearVelocity )
	{
		m_linearVelocity = linearVelocity;
	}

	const Vec2& getLinearVelocity() const
	{
		return m_linearVelocity;
	}

	void setAngularVelocity( float angularVelocity )
	{
		m_angularVelocity = angularVelocity;
	}

	float getAngularVelocity() const
	{
		return m_angularVelocity;
	}

	void setMass( float mass )
	{
		assert( mass >= 0.0f );

		m_mass = mass;

		if ( mass == 0.0f )
		{
			m_invMass = 0.0f;
			m_motionType = MotionType::stationary;
		}
		else
		{
			m_invMass = 1.0f / mass;
		}
	}

	float getMass() const
	{
		return m_mass;
	}

	float getInvMass() const
	{
		return m_invMass;
	}

	float getMassInverse() const
	{
		return m_invMass;
	}

	void setWorldArrayIndex( int index )
	{
		m_worldArrayIndex = index;
	}

	int getWorldArrayIndex() const
	{
		return m_worldArrayIndex;
	}

	bool isInWorld()
	{
		return ( m_worldArrayIndex >= 0 );
	}

	void setGravityScale( float scale )
	{
		m_gravityScale = scale;
	}

	float getGravityScale() const
	{
		return m_gravityScale;
	}

	float getTorque() const
	{
		return m_torque;
	}

	float getMomentOfInertia() const
	{
		return m_momentOfInertia;
	}

	float getMomentOfInertiaInverse() const
	{
		return m_invMomentOfInertia;
	}

	CollisionShape* getCollisionShape() const
	{
		return m_shape;
	}

	void setUserPointer( void* usrptr )
	{
		m_userdata = usrptr;
	}
	void* getUserPointer() const
	{
		return m_userdata;
	}

	void applyForce( const Vec2& force )
    {
		m_linearAcceleration += force / m_mass;
    }

    void applyImpulse( const Vec2& impulse )
    {
		m_linearVelocity += impulse / m_mass;
    }

	void setMotionType( MotionType type )
	{
		m_motionType = type;
	}

	MotionType getMotionType() const
	{
		return m_motionType;
	}

	void setFriction( float friction )
	{
		m_friction = friction;
	}

	float getFriction() const
	{
		return m_friction;
	}

	void setRestitution( float restitution )
	{
		m_restitution = restitution;
	}

	float getRestitution() const
	{
		return m_restitution;
	}

private:

	//
	CollisionShape* m_shape;

	//
	int m_worldArrayIndex = -1;

	//
	bool m_isActive;

	// позиция тела
	Vec2 m_position;

	// ориентация тела (угол поворота)
	float m_orientation;

	Vec2 m_linearAcceleration;

	// скорость тела в направлении
	Vec2 m_linearVelocity;
	
	// угловая скорость тела
	float m_angularVelocity;

	// масса тела
	float m_mass;
	float m_invMass;

	// момент инерции тела
	float m_momentOfInertia;
	float m_invMomentOfInertia;

	// коэффициент трения
	float m_friction;

	// коэффициент упругости
	float m_restitution;

	// сила, действующая на тело
	// Vec2 m_force;

	// std::vector<Vec2> m_forces;
	// std::vector<Vec2> m_impulses;

	// момент силы, действующей на тело
	float m_torque;

	// коэффициент гравитации
	float m_gravityScale;

	// пользовательский объект
	void* m_userdata;

	MotionType m_motionType = MotionType::stationary;
};

