// Oleg Kotov

#pragma once

#include "boxshape.h"
#include "circleshape.h"
#include "manifold.h"
#include "rigidbody.h"

class CollisionDetector
{
public:
	
	static bool checkCollision( CollisionShape* shapeA, CollisionShape* shapeB, Manifold& manifold )
    {
        CollisionShape::Type typeA = shapeA->getType();
        CollisionShape::Type typeB = shapeB->getType();

        if ( typeA == CollisionShape::Type::circle && typeB == CollisionShape::Type::circle )
        {
            return checkCircleCircleCollision( static_cast<CircleShape*>( shapeA ), static_cast<CircleShape*>( shapeB ), manifold );
        }
        else if ( typeA == CollisionShape::Type::box && typeB == CollisionShape::Type::box )
        {
            return checkOBBOBBCollision( static_cast<BoxShape*>( shapeA ), static_cast<BoxShape*>( shapeB ), manifold );
        }
        else if ( ( typeA == CollisionShape::Type::circle && typeB == CollisionShape::Type::box ) || ( typeA == CollisionShape::Type::box && typeB == CollisionShape::Type::circle ) )
        {
            return checkCircleBoxCollision( static_cast<CircleShape*>( ( typeA == CollisionShape::Type::circle ) ? shapeA : shapeB ),
                static_cast<BoxShape*>( ( typeA == CollisionShape::Type::box ) ? shapeA : shapeB ) );
        }

        return false;
    }

private:
    
    static bool checkCircleCircleCollision( CircleShape* circleA, CircleShape* circleB, Manifold& manifold )
    {
		Vec2 positionA = circleA->getRigidBody()->getPosition();
		Vec2 positionB = circleB->getRigidBody()->getPosition();
		float distanceSqr = ( positionA - positionB ).lengthSquared();
		float radiusSum = circleA->getRadius() + circleB->getRadius();

		if ( distanceSqr <= radiusSum * radiusSum )
		{
			float distance = sqrtf( distanceSqr );
			float penetration = radiusSum - distance;
			Vec2 normal = ( positionB - positionA ).normalize();

			manifold.body0 = circleA;
			manifold.body1 = circleB;
			manifold.penetration = penetration;
			manifold.normal = normal;

			return true;
		}

		return false;
    }

    static bool checkBoxBoxCollision( BoxShape* boxA, BoxShape* boxB )
    {
        Vec2 distance = boxA->getRigidBody()->getPosition() - boxB->getRigidBody()->getPosition();
        Vec2 halfSizeA = boxA->getHalfExtents();
        Vec2 halfSizeB = boxB->getHalfExtents();

        if ( fabsf( distance.x ) > halfSizeA.x + halfSizeB.x || fabsf( distance.y ) > halfSizeA.y + halfSizeB.y )
        {
            return false; // No intersection
        }

        return true; // Intersection
    }

    static bool checkCircleBoxCollision( CircleShape* circle, BoxShape* box )
    {
        Vec2 distance = circle->getRigidBody()->getPosition() - box->getRigidBody()->getPosition();
        Vec2 halfSize = box->getHalfExtents();

        float xDistance = fabsf( distance.x );
        float yDistance = fabsf( distance.y );

        if ( xDistance > halfSize.x + circle->getRadius() || yDistance > halfSize.y + circle->getRadius() )
        {
            return false; // No intersection
        }

        if ( xDistance <= halfSize.x || yDistance <= halfSize.y )
        {
            return true; // Intersection
        }

        float cornerDistanceSqr = ( xDistance - halfSize.x ) * ( xDistance - halfSize.x ) + ( yDistance - halfSize.y ) * ( yDistance - halfSize.y );

        return cornerDistanceSqr <= circle->getRadius() * circle->getRadius();
    }

    static bool checkOBBOBBCollision( BoxShape* boxA, BoxShape* boxB, Manifold& manifold )
    {
        RigidBody* body1 = boxA->getRigidBody();
        RigidBody* body2 = boxB->getRigidBody();

		// axes vector
		Vec2 a1(  cos( body1->getOrientationRad() ), sin( body1->getOrientationRad() ) );
		Vec2 a2( -sin( body1->getOrientationRad() ), cos( body1->getOrientationRad() ) );
		Vec2 a3(  cos( body2->getOrientationRad() ), sin( body2->getOrientationRad() ) );
		Vec2 a4( -sin( body2->getOrientationRad() ), cos( body2->getOrientationRad() ) );

		// edge length
		Vec2 l1 = boxA->getHalfExtents();
		Vec2 l2 = boxB->getHalfExtents();

		// vector between pivots
		Vec2 l = body1->getPosition() - body2->getPosition();

		float r1, r2, r3, r4;

		// project to a1
		r1 = l1.x * fabs( a1.dot( a1 ) );
		r2 = l1.y * fabs( a2.dot( a1 ) );
		r3 = l2.x * fabs( a3.dot( a1 ) );
		r4 = l2.y * fabs( a4.dot( a1 ) );

		if ( r1 + r2 + r3 + r4 <= fabs( l.dot( a1 ) ) )
		{
			return false;
		}

		// project to a2
		r1 = l1.x * fabs( a1.dot( a2 ) );
		r2 = l1.y * fabs( a2.dot( a2 ) );
		r3 = l2.x * fabs( a3.dot( a2 ) );
		r4 = l2.y * fabs( a4.dot( a2 ) );

		if ( r1 + r2 + r3 + r4 <= fabs( l.dot( a2 ) ) )
		{
			return false;
		}

		// project to a3
		r1 = l1.x * fabs( a1.dot( a3 ) );
		r2 = l1.y * fabs( a2.dot( a3 ) );
		r3 = l2.x * fabs( a3.dot( a3 ) );
		r4 = l2.y * fabs( a4.dot( a3 ) );

		if ( r1 + r2 + r3 + r4 <= fabs( l.dot( a3 ) ) )
		{
			return false;
		}

		// project to a4
		r1 = l1.x * fabs( a1.dot( a4 ) );
		r2 = l1.y * fabs( a2.dot( a4 ) );
		r3 = l2.x * fabs( a3.dot( a4 ) );
		r4 = l2.y * fabs( a4.dot( a4 ) );

		if ( r1 + r2 + r3 + r4 <= fabs( l.dot( a4 ) ) )
		{
			return false;
		}

		manifold.body0 = boxA;
		manifold.body1 = boxB;

		if ( l.dot( a4 ) < 0 )
		{
			manifold.normal = a4;
		}
		else
		{
			manifold.normal = -a4;
		}

		// manifold.normal = -manifold.normal;

		manifold.penetration = r1 + r2 + r3 + r4 - fabs( l.dot( a4 ) );

		return true;
    }
};

