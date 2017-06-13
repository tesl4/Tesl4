#include <ctime>
#pragma once
class CTimeMgr
{
	clock_t		m_deltaMS;			//이전 업데이트와 현제 업데이트사이의 시간(millisec)
	clock_t		m_totalRuntimeMS;	//현재 어플리케이션의 실행 시간(ms)

	UINT m_minDeltaMS;	//최소 틱 간격(최대 FPS 제한에 필요한 델다 값, 1000/capfps)

	float m_deltaNor;
	float m_timer;
	float m_minDeltaNor;			//이전 업데이트와 현제 업데이트사이의 시간(millisec)

	int m_fps;

public:
	CTimeMgr();
	~CTimeMgr();
	
	UINT TimeUpdate();
	void CapFPS(int _capVal);
};

