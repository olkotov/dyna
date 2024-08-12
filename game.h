// Oleg Kotov

#pragma once

class Game
{
public:

	void start();
	void update( float deltaTime );

private:

	bool m_isRunning = false;
};

