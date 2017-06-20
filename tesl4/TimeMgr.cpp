#include "stdafx.h"
#include "TimeMgr.h"


CTimeMgr::CTimeMgr() : m_delta(0), m_currentRuntime(0), m_minDelta(33)
{
	m_timer = 0;
	m_fps = 0;
}


CTimeMgr::~CTimeMgr()
{
}

UINT CTimeMgr::TimeUpdate()
{
	clock_t prevTime = m_currentRuntime;
	m_currentRuntime = GetTickCount();
	m_delta = ((float)m_currentRuntime - (float)prevTime) * 0.001f;
	//std::cout << m_currentRuntime << " + " << prevTime <<std::endl;

	float fsleep = 0;
	if (m_minDelta > m_delta)
	{
		fsleep = (float)m_minDelta - (float)m_delta;
		Sleep(fsleep);
		m_delta += fsleep;
	}
	m_deltaNor = m_delta * 0.001;
	m_timer += m_deltaNor;
	/*std::cout << m_deltaNor << " + " << m_timer;
	if (fsleep > 0) std::cout << "   slept " << fsleep << "ms    "<<std::endl;
	else std::cout << std::endl;*/

	m_fps++;
	
	if (m_timer > 1.0f)
	{
		//std::cout <<"1sec ticks -----------------------------------------------"<<m_fps<< std::endl;
		m_fps = 0;
		m_timer = 0;
	}

	return 0;
}

void CTimeMgr::CapFPS(int _capVal)
{
	m_minDelta = 1000 / _capVal;
}

float CTimeMgr::GetDelta()
{
	return m_deltaNor;
}

float CTimeMgr::GetDeltaMS()
{
	return m_delta;
}


