#include "Timer.h"
#include <SDL.h>

Timer::Timer()
{
	m_Paused = false;
	m_Started = false;
	m_CurrentTime = 0;
	m_LastTime = 0;
	m_DeltaTime = 0.0f;
	m_CurrentFrameCount = 0;
}


Timer::~Timer()
{
}

//resets timer
void Timer::reset()
{
	m_Paused = false;
	m_Started = false;
	m_CurrentTime = 0;
	m_LastTime = 0;
	m_DeltaTime = 0.0f;
	m_CurrentFrameCount = 0;
}

void Timer::start()
{
	m_Started = true;
	m_CurrentTime = SDL_GetTicks();
	m_LastTime = SDL_GetTicks();
}

void Timer::togglePause()
{
	m_Paused = !m_Paused;
}

void Timer::stop()
{
	m_Started = false;
}

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