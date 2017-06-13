#include "stdafx.h"
#include "TimeMgr.h"


CTimeMgr::CTimeMgr() : m_deltaMS(0), m_totalRuntimeMS(0), m_minDeltaMS(33)
{
	m_timer = 0;
	m_fps = 0;
}


CTimeMgr::~CTimeMgr()
{
}

UINT CTimeMgr::TimeUpdate()
{
	clock_t currentTimeMS = m_totalRuntimeMS;
	m_totalRuntimeMS = timeGetTime();
	m_deltaMS = m_totalRuntimeMS - currentTimeMS;
	m_deltaNor = 0.001f * m_deltaMS;
	if (m_minDeltaMS > m_deltaMS)
	{
		int sleep = m_minDeltaMS - m_deltaMS;
		Sleep(sleep);
		m_deltaMS += sleep;
	}
	
	m_fps++;
	//std::cout << m_totalRuntimeMS << " - " << currentTimeMS << " = " << m_deltaMS <<std::endl;
	
	m_timer += m_deltaMS;
	if (m_timer > 1000)
	{
		std::cout <<"1sec ticks - "<<m_fps<< std::endl;
		m_fps = 0;
		m_timer = 0;
	}

	return 0;
}

void CTimeMgr::CapFPS(int _capVal)
{
	m_minDeltaMS = 1000 / _capVal;
	m_minDeltaNor = 0.001 * m_minDeltaMS;
}
