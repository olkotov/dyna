// Oleg Kotov

#pragma once

#include <chrono>

class Clock
{
public:

	Clock()
	{
		m_startTime = std::chrono::high_resolution_clock::now();
		m_lastTime = m_startTime;
	}

	// Calculate the delta time and the time since startup.
	void calculateTimes()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();

		m_deltaTime = std::chrono::duration<float, std::chrono::seconds::period>( currentTime - m_lastTime ).count();
		m_lastTime = currentTime;

		m_timeSinceStartup = std::chrono::duration<float, std::chrono::seconds::period>( currentTime - m_startTime ).count();
	}

	// Gets the elapsed time between the start of the previous and current frames, in seconds.
	float getDeltaTime() const
	{
		return m_deltaTime;
	}

	// Gets the current time since the start of the game, in seconds.
	float getTimeSinceStartup() const
	{
		return m_timeSinceStartup;
	}

private:

	std::chrono::steady_clock::time_point m_lastTime;
	float m_deltaTime = 0.0f;

	std::chrono::steady_clock::time_point m_startTime;
	float m_timeSinceStartup = 0.0f;
};

