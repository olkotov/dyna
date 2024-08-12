// Oleg Kotov

#pragma once

class RigidBody;
class CollisionShape;

namespace sf
{
	class Sprite;
	class Drawable;
}

class Entity
{
public:

	virtual ~Entity() {}

	virtual void onBeginPlay() {}
	virtual void onEndPlay() {}

	virtual void onTick( float deltaTime ) {}
	virtual void onPhysics( float timeStep ) {}

	virtual void onCollisionBegin( Entity* other ) {}
	virtual void onCollisionStay( Entity* other ) {}
	virtual void onCollisionEnd( Entity* other ) {}

	virtual void onOverlapBegin( Entity* other ) {}
	virtual void onOverlapStay( Entity* other ) {}
	virtual void onOverlapEnd( Entity* other ) {}

	void setName( const std::string& name )
	{
		m_name = name;
	}

	const std::string& getName() const
	{
		return m_name;
	}

	void setPosition( const Vec2& pos )
	{
		if ( !m_rigidbody ) return;
		m_rigidbody->setPosition( pos );
	}

	Vec2 getPosition() const
	{
		if ( !m_rigidbody ) return Vec2();
		return m_rigidbody->getPosition();
	}

	float getRotation() const
	{
		if ( !m_rigidbody ) return 0.0f;
		return m_rigidbody->getOrientationDeg();
	}

	sf::Drawable* getDrawable() const
	{
		return m_drawable;
	}

	sf::Sprite* getSprite() const
	{
		return m_sprite;
	}

	RigidBody* getRigidbody() const
	{
		return m_rigidbody;
	}

	CollisionShape* getCollisionShape() const
	{
		return m_collisionShape;
	}

protected:

	std::string m_name;

	// visual
	sf::Drawable* m_drawable = nullptr;
	sf::Sprite* m_sprite = nullptr;

	// physics
	RigidBody* m_rigidbody = nullptr;
	CollisionShape* m_collisionShape = nullptr;
};

