// Oleg Kotov

#include "clock.h"

#include "physicsworld.h"
#include "rigidbody.h"

#include "player_circle.h"
#include "ground_circle.h"

#include "player.h"
#include "ground.h"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Dyna Physics" );

    sf::View view;
    view.setCenter( 0.0f, 0.0f );
    view.setSize( sf::Vector2f( window.getSize().x, window.getSize().y ) );
    view.zoom( 0.05f );
    window.setView( view );

    // ---

    Clock clock;

	const float fixedTimeStep = 1.0f / 60.0f;
	float accumulatedTime = 0.0f;

    PhysicsWorld* physicsWorld = PhysicsWorld::instance();
    std::vector<Entity*> entities;

    //PlayerCircle* player = new PlayerCircle();
    //player->setPosition( Vec2( 0.0f, 0.0f ) );
    //entities.emplace_back( player );

    //GroundCircle* ground = new GroundCircle();
    //ground->setPosition( Vec2( 0.0f, -10.0f ) );
    //entities.emplace_back( ground );

    Player* player_2 = new Player();
    player_2->setPosition( Vec2( 0.0f, 0.0f ) );
    entities.emplace_back( player_2 );

    Ground* ground_2 = new Ground();
    ground_2->setPosition( Vec2( 0.0f, -10.0f ) );
    entities.emplace_back( ground_2 );

    // ---

    while ( window.isOpen() )
    {
        // timer
        clock.calculateTimes();

        float deltaTime = clock.getDeltaTime();
        accumulatedTime += deltaTime;

        // events
        sf::Event event;
        while ( window.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed ) window.close();

            if ( event.type == sf::Event::KeyPressed )
            {
                if ( event.key.code == sf::Keyboard::Space )
                {
                    // player->jump();
                    player_2->jump();
                }
            }
        }

        // physics
        
		if ( accumulatedTime > 0.2f ) accumulatedTime = 0.2f;

		while ( accumulatedTime >= fixedTimeStep )
		{
            physicsWorld->simulationStep( fixedTimeStep );

            for ( const auto& entity : entities )
            {
                entity->onPhysics( fixedTimeStep );
            }

			accumulatedTime -= fixedTimeStep;
		}

        // gameplay
        for ( const auto& entity : entities )
        {
            entity->onTick( deltaTime );
        }

        // render
        window.clear( sf::Color( 18, 18, 18 ) );

        for ( const auto& entity : entities )
        {
            auto drawable = entity->getDrawable();
            if ( !drawable ) continue;

            sf::Transformable* transformable = dynamic_cast<sf::Transformable*>( drawable );

            if ( transformable )
            {
                Vec2 position = entity->getPosition();
                float rotation = entity->getRotation();

                transformable->setPosition( position.x, -position.y );
                transformable->setRotation( -rotation );
            }
            
            window.draw( *drawable );

        }

        window.display();
    }

	return 0;
}

