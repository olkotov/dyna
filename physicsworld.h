// Oleg Kotov

#pragma once

#include "rigidbody.h"
#include "vec2.h"
#include "utils.h"
#include "clock.h"
#include "collisiondetector.h"

#include <vector>
#include <memory>

class CollisionShape;

class PhysicsWorld
{
public:

	void addRigidBody( RigidBody* rigidbody )
	{
		if ( !rigidbody || rigidbody->isInWorld() ) return;

		rigidbody->setWorldArrayIndex( (int)m_bodies.size() );
		m_bodies.push_back( rigidbody );
	}

	void removeRigidBody( RigidBody* rigidbody )
	{
		int bodyIndex = rigidbody->getWorldArrayIndex();

		std::swap( m_bodies[bodyIndex], m_bodies.back() );
		m_bodies.pop_back();

		m_bodies[bodyIndex]->setWorldArrayIndex( bodyIndex );
		rigidbody->setWorldArrayIndex( -1 );
	}

	void setGravity( const Vec2& gravity )
	{
		m_gravity = gravity;
	}

	const Vec2& getGravity() const
	{
		return m_gravity;
	}

	void update()
	{
		simulationStep( m_fixedTimeStep );
	}

	void simulationStep( float timeStep )
	{
		for ( const auto& body : m_bodies )
		{
			if ( body->getMotionType() != RigidBody::MotionType::dynamic ) continue;

			Vec2 linearAcceleration = body->getLinearAcceleration();
			linearAcceleration += m_gravity * body->getGravityScale();

			body->setLinearVelocity( body->getLinearVelocity() + linearAcceleration * timeStep );
			body->setPosition( body->getPosition() + body->getLinearVelocity() * timeStep );

			// float angularAcceleration = body->getTorque() / body->getMomentOfInertia();

			// body->setAngularVelocity( body->getAngularVelocity() + angularAcceleration * timeStep );
			// body->setOrientation( body->getOrientation() + body->getAngularVelocity() * timeStep );

			body->setLinearAcceleration( Vec2( 0.0f, 0.0f ) );
		}
		
		for ( int i = 0; i < m_bodies.size(); ++i )
		{
			for ( int j = i + 1; j < m_bodies.size(); ++j )
			{
				Manifold manifold = {};

				if ( CollisionDetector::checkCollision( m_bodies[i]->getCollisionShape(), m_bodies[j]->getCollisionShape(), manifold ) )
				{
					resolveCollision( m_bodies[i]->getCollisionShape(), m_bodies[j]->getCollisionShape(), manifold );
				}
			}
		}
	}

	static PhysicsWorld* instance()
	{
		if ( !m_instance )
		{
			m_instance = new PhysicsWorld();
		}

		return m_instance;
	}

	void resolveCollision( CollisionShape* shape1, CollisionShape* shape2, const Manifold& manifold )
	{
		RigidBody* body1 = shape1->getRigidBody();
		RigidBody* body2 = shape2->getRigidBody();

		if ( body1->getMotionType() == RigidBody::MotionType::stationary &&
			 body2->getMotionType() == RigidBody::MotionType::stationary )
		{
			return;
		}

		// Calculate relative velocity 
		Vec2 relativeVelocity = body2->getLinearVelocity() - body1->getLinearVelocity();

		// Calculate relative velocity in terms of the normal direction 
		float velocityAlongNormal = relativeVelocity.dot( manifold.normal );

		// Do not resolve if velocities are separating 
		if ( velocityAlongNormal > 0 ) return;

		// Calculate restitution 
		float restitution = std::min( body1->getRestitution(), body2->getRestitution() );

		// Calculate impulse scalar
		float jn = -( 1.0f + restitution ) * velocityAlongNormal;
		jn /= body1->getInvMass() + body2->getInvMass();

		// Apply impulse 
		Vec2 impulse = manifold.normal * jn;

		if ( body1->getMotionType() == RigidBody::MotionType::dynamic )
		{
			body1->applyImpulse( -impulse );
		}

		if ( body2->getMotionType() == RigidBody::MotionType::dynamic )
		{
			body2->applyImpulse( impulse );
		}

		//

		float friction = std::min( body1->getFriction(), body2->getFriction() );

		Vec2 tangent = relativeVelocity - manifold.normal * relativeVelocity.dot( manifold.normal );
		tangent = -tangent.normalize();

		float jt = -( 1.0f + restitution ) * relativeVelocity.dot( tangent ) * friction;
		jt /= body1->getInvMass() + body2->getInvMass();

		if ( jt > jn ) jt = jn;
		impulse = tangent * jn;

		if ( body1->getMotionType() == RigidBody::MotionType::dynamic )
		{
			body1->applyImpulse( -impulse );
		}

		if ( body2->getMotionType() == RigidBody::MotionType::dynamic )
		{
			body2->applyImpulse( impulse );
		}

		// positional correction

		float percent = 0.2f; // usually 20% to 80% 
		float slop = 0.01f; // usually 0.01 to 0.1 
		
		float num = std::max( manifold.penetration - slop, 0.0f ) / ( body1->getInvMass() + body2->getInvMass() ) * percent;
		Vec2 correctionAmount = manifold.normal * num;
		
		if ( body1->getMotionType() == RigidBody::MotionType::dynamic )
		{
			body1->setPosition( body1->getPosition() + ( correctionAmount * -body1->getInvMass() ) );
		}

		if ( body2->getMotionType() == RigidBody::MotionType::dynamic )
		{
			body2->setPosition( body2->getPosition() + ( correctionAmount * body2->getInvMass() ) );
		}
	}

private:

	static PhysicsWorld* m_instance;

	Clock m_clock;
	const float m_fixedTimeStep = 1.0f / 60.0f;
	float m_accumulatedTime = 0.0f;

	Vec2 m_gravity = Vec2( 0.0f, -10.0f );

	std::vector<RigidBody*> m_bodies;
};

PhysicsWorld* PhysicsWorld::m_instance = nullptr;

