// Oleg Kotov

#pragma once

#include "entity.h"
#include "physicsworld.h"
#include "rigidbody.h"
#include "boxshape.h"

#include <SFML/Graphics.hpp>

class PlayerCircle : public Entity
{
public:

	PlayerCircle()
	{
		m_name = "player";

		m_radius = 0.5f;

		// visual
		m_drawable = new sf::CircleShape( m_radius );
		
		sf::RectangleShape* shape = static_cast<sf::RectangleShape*>( m_drawable );
		
		if ( shape )
		{
			shape->setOrigin( m_radius, m_radius );
		}

		// physics
		m_collisionShape = new CircleShape( m_radius );

		m_rigidbody = new RigidBody( m_collisionShape );
		m_rigidbody->setGravityScale( 0.0f );
		m_rigidbody->setUserPointer( this );
		m_rigidbody->setMotionType( RigidBody::MotionType::dynamic );

		PhysicsWorld::instance()->addRigidBody( m_rigidbody );
	}

	~PlayerCircle()
	{
		PhysicsWorld::instance()->removeRigidBody( m_rigidbody );

		delete m_collisionShape;
		delete m_rigidbody;
		delete m_drawable;
	}

	void applyGravityToPoint( const Vec2& gravityCenter, float gravityStrength )
	{
		float distance = ( gravityCenter - getPosition() ).lengthSquared();

		if ( distance < 0.01f )
		{
			m_rigidbody->setLinearVelocity( Vec2() );
			return;
		}

		Vec2 gravityDirection = ( gravityCenter - getPosition() ).normalize();
		Vec2 gravityForce = gravityDirection * gravityStrength;
		m_rigidbody->applyForce( gravityForce );
	}

	void jump()
	{
		m_rigidbody->setLinearVelocity( Vec2( 0.0f, 0.0f ) );
		m_rigidbody->applyImpulse( Vec2( 0.0f, 10.0f ) );
	}

	void onPhysics( float timeStep ) override
	{
		Vec2 gravity = Vec2( 0.0f, -10.0f );
		float gravityScale = 3.0f;
		m_rigidbody->applyForce( gravity * gravityScale * m_rigidbody->getMass() );

		// applyGravityToPoint( Vec2(), 10.0f );
	}

	void onTick( float deltaTime ) override
	{

	}

private:

	float m_radius;
};

