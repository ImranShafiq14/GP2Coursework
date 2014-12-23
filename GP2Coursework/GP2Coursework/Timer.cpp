#include "Timer.h"
#include <SDL.h>

//Constructor for Timer - RT
Timer::Timer()
{
	m_Paused = false;
	m_Started = false;
	m_CurrentTime = 0;
	m_LastTime = 0;
	m_DeltaTime = 0.0f;
	m_CurrentFrameCount = 0;
}

//Deconstructor for Timer - RT
Timer::~Timer()
{
}

//resets timer - RT
void Timer::reset()
{
	m_Paused = false;
	m_Started = false;
	m_CurrentTime = 0;
	m_LastTime = 0;
	m_DeltaTime = 0.0f;
	m_CurrentFrameCount = 0;
}

//Starts the timer - RT
void Timer::start()
{
	m_Started = true;
	m_CurrentTime = SDL_GetTicks();
	m_LastTime = SDL_GetTicks();
}

//Toggles the pause function - RT
void Timer::togglePause()
{
	m_Paused = !m_Paused;
}

//Stops the timer - RT
void Timer::stop()
{
	m_Started = false;
}

//Called by the program every "frame" - RT
void Timer::update()
{
	if (m_Started && !m_Paused)
	{
		m_CurrentFrameCount++;
		m_CurrentTime = SDL_GetTicks();
		m_DeltaTime = (float)(m_CurrentTime - m_LastTime) / 1000.0f;
		m_LastTime = m_CurrentTime;
	}
}