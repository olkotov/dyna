// Oleg Kotov

#pragma once

#include "entity.h"
#include "physicsworld.h"
#include "rigidbody.h"
#include "boxshape.h"

#include <SFML/Graphics.hpp>

class Player : public Entity
{
public:

	Player()
	{
		m_name = "player";

		m_width = 1.0f;
		m_height = 1.75f; // 1 m, 75 cm

		// visual
		m_drawable = new sf::RectangleShape( sf::Vector2f( m_width, m_height ) );
		
		sf::RectangleShape* shape = static_cast<sf::RectangleShape*>( m_drawable );
		
		if ( shape )
		{
			shape->setFillColor( sf::Color( 243, 184, 81 ) );
			shape->setOrigin( m_width * 0.5f, m_height * 0.5f );
		}

		// physics
		m_collisionShape = new BoxShape( Vec2( m_width * 0.5f, m_height * 0.5f ) );

		m_rigidbody = new RigidBody( m_collisionShape );
		m_rigidbody->setMotionType( RigidBody::MotionType::dynamic );
		// m_rigidbody->setGravityScale( 0.01f );
		m_rigidbody->setUserPointer( this );

		PhysicsWorld::instance()->addRigidBody( m_rigidbody );
	}

	~Player()
	{
		PhysicsWorld::instance()->removeRigidBody( m_rigidbody );

		delete m_collisionShape;
		delete m_rigidbody;
		delete m_drawable;
	}

	void jump()
	{
		m_rigidbody->setLinearVelocity( Vec2( 0.0f, 0.0f ) );
		m_rigidbody->applyImpulse( Vec2( 0.0f, 10.0f ) );
	}

private:

	float m_width;
	float m_height;
};

