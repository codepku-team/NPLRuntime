#include "ParaTimer.h"
#include <ctime>
ParaEngine::ParaTimer::ParaTimer()
	:m_bTimerInitialized(false)
	,m_bTimerStopped(false)
	,m_fBaseTime(0.0f)
	,m_fStopTime(0.0f)
	,m_fLastElapsedTime(0.0f)
{

}

ParaEngine::ParaTimer::~ParaTimer()
{
}

void ParaEngine::ParaTimer::Reset()
{
	float fTime = 0;
	if (m_bTimerStopped){
		fTime = m_fStopTime;
	}else{
		fTime = GetAbsoluteTime();
	}

	m_fBaseTime = fTime;
	m_fLastElapsedTime = fTime;
	m_fStopTime = 0;
	m_bTimerStopped = false;
}

void ParaEngine::ParaTimer::Start()
{
	auto fTime = GetAbsoluteTime();
	if (m_bTimerStopped)
		m_fBaseTime += fTime - m_fStopTime;
	m_fStopTime = 0.0f;
	m_fLastElapsedTime = fTime;
	m_bTimerStopped = false;
}

void ParaEngine::ParaTimer::Stop()
{
	if (m_bTimerStopped)return;
	m_fStopTime = GetAbsoluteTime();
	m_bTimerStopped = true;
}

void ParaEngine::ParaTimer::Advance()
{
	m_fStopTime += 0.1f;
}

double ParaEngine::ParaTimer::GetAbsoluteTime() const
{
	std::clock_t t = std::clock();
	double fTime = (double)t / CLOCKS_PER_SEC;
	return fTime;
}

double ParaEngine::ParaTimer::GetAppTime() const
{
	float fTime = 0;
	if (m_bTimerStopped) {
		fTime = m_fStopTime;
	}
	else {
		fTime = GetAbsoluteTime();
	}

	return fTime - m_fBaseTime;
}

double ParaEngine::ParaTimer::GetElapsedTime() const
{
	float fTime = 0;
	if (m_bTimerStopped) {
		fTime = m_fStopTime;
	}
	else {
		fTime = GetAbsoluteTime();
	}
	double fElapsedTime = (double)(fTime - m_fLastElapsedTime);
	m_fLastElapsedTime = fTime;
	return fElapsedTime;
}