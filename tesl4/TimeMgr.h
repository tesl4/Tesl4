#include "stdafx.h"
#pragma once
class CTimeMgr
{
	unsigned int m_currentRuntime;	//현재 어플리케이션의 실행 시간(ms)
	
	float m_delta;
	float m_deltaNor;
	float m_minDelta;	//최소 틱 간격(최대 FPS 제한에 필요한 델다 값, 1000/capfps)
	float m_timer;

	int m_fps;

	unsigned int m_PerformanceCntr;

public:
	CTimeMgr();
	~CTimeMgr();
	
	UINT TimeUpdate();
	void CapFPS(int _capVal);

	float GetDelta();
	float GetDeltaMS();

};

