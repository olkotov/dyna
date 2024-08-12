// Oleg Kotov

#pragma once

#include "entity.h"
#include "physicsworld.h"
#include "rigidbody.h"
#include "boxshape.h"

#include <SFML/Graphics.hpp>

class GroundCircle : public Entity
{
public:

	GroundCircle()
	{
		m_name = "ground";

		m_radius = 2.5f;

		// visual
		m_drawable = new sf::CircleShape( m_radius );
		
		sf::CircleShape* shape = static_cast<sf::CircleShape*>( m_drawable );
		
		if ( shape )
		{
			shape->setOrigin( m_radius, m_radius );
			shape->setFillColor( sf::Color::Transparent );
			shape->setOutlineColor( sf::Color( 217, 217, 217 ) );
			shape->setOutlineThickness( 0.05f );
		}

		// physics
		m_collisionShape = new CircleShape( m_radius );
		
		m_rigidbody = new RigidBody( m_collisionShape );
		m_rigidbody->setGravityScale( 0.0f );
		m_rigidbody->setUserPointer( this );
		m_rigidbody->setMass( 50.0f );
		m_rigidbody->setMotionType( RigidBody::MotionType::stationary );

		PhysicsWorld::instance()->addRigidBody( m_rigidbody );
	}

	~GroundCircle()
	{
		PhysicsWorld::instance()->removeRigidBody( m_rigidbody );

		delete m_collisionShape;
		delete m_rigidbody;
		delete m_drawable;
	}

private:

	float m_radius;
};

