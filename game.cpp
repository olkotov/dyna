// Oleg Kotov

#include "game.h"

void Game::start()
{
	m_isRunning = true;

	while ( m_isRunning )
	{
		update( 0.016f );
	}
}

void Game::update( float deltaTime )
{

}

