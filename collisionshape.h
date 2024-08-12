// Oleg Kotov

#pragma once

#include <stdint.h>

class RigidBody;

class CollisionShape
{
public:

	enum class Type : uint8_t
	{
		circle,
		box
	};

public:

    virtual ~CollisionShape() {}

    virtual Type getType() const = 0;

    void setRigidBody( RigidBody* rigidbody )
    {
        m_rigidbody = rigidbody;
    }

    RigidBody* getRigidBody() const
    {
        return m_rigidbody;
    }
   
private:

    RigidBody* m_rigidbody = nullptr;
};

