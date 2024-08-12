// Oleg Kotov

#pragma once

#include "entity.h"
#include "physicsworld.h"
#include "rigidbody.h"
#include "boxshape.h"

#include <SFML/Graphics.hpp>

class Ground : public Entity
{
public:

	Ground()
	{
		m_name = "ground";

		m_width = 10.0f;
		m_height = 0.5f;

		// visual
		m_drawable = new sf::RectangleShape( sf::Vector2f( m_width, m_height ) );
		
		sf::RectangleShape* shape = static_cast<sf::RectangleShape*>( m_drawable );
		
		if ( shape )
		{
			shape->setFillColor( sf::Color( 211, 211, 211 ) );
			shape->setOrigin( m_width * 0.5f, m_height * 0.5f );
		}

		// physics
		m_collisionShape = new BoxShape( Vec2( m_width * 0.5f, m_height * 0.5f ) );
		
		m_rigidbody = new RigidBody( m_collisionShape );
		m_rigidbody->setGravityScale( 0.0f );
		m_rigidbody->setUserPointer( this );
		m_rigidbody->setOrientation( -45.0f );

		PhysicsWorld::instance()->addRigidBody( m_rigidbody );
	}

	~Ground()
	{
		PhysicsWorld::instance()->removeRigidBody( m_rigidbody );

		delete m_collisionShape;
		delete m_rigidbody;
		delete m_drawable;
	}

private:

	float m_width;
	float m_height;
};

